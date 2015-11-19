//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "texture.h"
#include "common/io.h"

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
				this->internal_image.create(width, height, pixels);
			}

			//Construct a texture from the data contained within a given file
			Texture::Texture(std::string filename)
			{
				this->loadFromFile(filename);
			}

			//Create a texture from the data contained within a given file
			bool Texture::loadFromFile(std::string filename)
			{
				bool success = this->internal_image.loadFromFile(filename);
				this->internal_image.flipVertically();
				IO::test(success, "Loading texture from file '" + filename + "'");

				return success;
			}

			//Find the size of the texture
			sf::Vector2u Texture::getSize()
			{
				return this->internal_image.getSize();
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
					
					/*for (int j = 0; j < this->getSize().y; j ++)
					{
						for (int i = 0; i < this->getSize().x; i ++)
						{
							printf((" " + std::to_string(this->getPixelData()[(i + j * this->getSize().y) * 3])).c_str());
						}
					}*/

					gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, (gl::GLuint)gl::GL_RGBA, this->getSize().x, this->getSize().y, 0, gl::GL_RGBA, gl::GL_UNSIGNED_BYTE, this->getPixelData());

					gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, (gl::GLuint)gl::GL_LINEAR);
					gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, (gl::GLuint)gl::GL_LINEAR);
					//gl::glGenerateMipmap(gl::GL_TEXTURE_2D);
					
					this->buffered = true;

					IO::output("Buffered texture with size " + std::to_string(this->getSize().x) + "x" + std::to_string(this->getSize().y) + ".");
				}
			}
		}
	}
}
