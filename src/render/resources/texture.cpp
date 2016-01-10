//----STANDARD----
#include "string.h"

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "texture.h"
#include "common/io.h"
#include "shader.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			Texture::Texture()
			{
				//Constructor
			}
			
			Texture::~Texture()
			{
				//Destructor
			}

			//Construct a texture with a given width and height, optionally from pixel data.
			Texture::Texture(uint16 width, uint16 height, const uint8* pixels)
			{
				this->create(width, height, pixels);
			}

			//Create a texture with a given width and height, optionally from pixel data.
			void Texture::create(uint16 width, uint16 height, const uint8* pixels)
			{
				if (pixels == nullptr) //Override the default SFML behaviour. Make null pixels create a white texture, not an empty one
					this->internal_image.create(width, height, sf::Color::White);
				else
					this->internal_image.create(width, height, pixels);
			}

			//Construct a texture from the data contained within a given file
			Texture::Texture(std::string filename, unsigned char flip_flags)
			{
				this->loadFromFile(filename, flip_flags);
			}

			//Create a texture from the data contained within a given file
			bool Texture::loadFromFile(std::string filename, unsigned char flip_flags)
			{
				bool success = this->internal_image.loadFromFile(filename);
				if (flip_flags & 0b00000001)
					this->internal_image.flipHorizontally();
				if (flip_flags & 0b00000010)
					this->internal_image.flipVertically();
				IO::test(success, "Loading texture from file '" + filename + "'");

				return success;
			}

			//Find the size of the texture
			sf::Vector2u Texture::getSize()
			{
				return this->internal_image.getSize();
			}
			
			//Set the size of the texture [WARNING: OVERWRITES THE TEXTURE]
			void Texture::setSize(sf::Vector2u size)
			{
				IO::output("Changed texture size to (" + std::to_string(size.x) + ", " + std::to_string(size.y) + ")");
				this->create(size.x, size.y, nullptr);
				
				//Rebuffer it if it needs it
				if (this->buffered)
					this->buffer();
			}

			//Find a pointer to the pixel data contained within the texture
			const uint8* Texture::getPixelData()
			{
				return this->internal_image.getPixelsPtr();
			}

			//Find a pixel value within the texture
			Pixel Texture::getPixel(uint16 x, uint16 y)
			{
				return Pixel(this->internal_image.getPixel(x, y));
			}

			//Set a pixel value within the texture
			void Texture::setPixel(uint16 x, uint16 y, Pixel pixel)
			{
				return this->internal_image.setPixel(x, y, sf::Color(pixel.r, pixel.g, pixel.b, pixel.a));
			}

			//Buffer the texture into GPU memory
			void Texture::buffer(bool force)
			{
				if (force || !this->buffered)
				{
					//Generate the texture
					if (!this->buffered)
						gl::glGenTextures(1, &this->gl_id);

					//Bind the texture ready to write data
					gl::glBindTexture(gl::GL_TEXTURE_2D, this->gl_id);
					
					gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, (gl::GLuint)gl::GL_RGBA16F, this->getSize().x, this->getSize().y, 0, gl::GL_RGBA, gl::GL_UNSIGNED_BYTE, this->getPixelData());

					gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, (gl::GLuint)gl::GL_LINEAR);
					gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, (gl::GLuint)gl::GL_LINEAR);
					
					IO::output("Generating texture mipmap...");
					
					//gl::glGenerateMipmap(gl::GL_TEXTURE_2D);
					
					this->buffered = true;

					IO::output("Buffered texture with size " + std::to_string(this->getSize().x) + "x" + std::to_string(this->getSize().y) + ".");
				}
			}
			
			void Texture::bindTo(uint16 texture_slot)
			{
				gl::glActiveTexture(gl::GL_TEXTURE0 + texture_slot);
				gl::glBindTexture(gl::GL_TEXTURE_2D, this->getGLID());
			}
			
			void Texture::bindToWithUniform(uint16 texture_slot, std::string uniform_name, Shader& shader)
			{
				gl::glUniform1i(gl::glGetUniformLocation(shader.getGLID(), uniform_name.c_str()), texture_slot);
				this->bindTo(texture_slot);
			}
		}
	}
}
