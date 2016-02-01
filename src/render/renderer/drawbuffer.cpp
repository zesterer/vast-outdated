//----LOCAL----
#include "drawbuffer.h"
#include "common/io.h"

namespace Vast
{
	namespace Render
	{
		namespace Renderer
		{
			DrawBuffer::DrawBuffer(Resources::Texture* in_texture)
			{
				this->target_texture = in_texture;
			}
			
			DrawBuffer::~DrawBuffer()
			{
				gl::glDeleteFramebuffers(1, &this->gl_id);
				
				if (this->target_texture == nullptr)
				{
					gl::glDeleteTextures(1, &this->gl_texture_id);
					gl::glDeleteRenderbuffers(1, &this->gl_depthbuffer_id);
				}
			}
			
			void DrawBuffer::initialise()
			{
				//Create the framebuffer
				gl::glGenFramebuffers(1, &this->gl_id);
				gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, this->gl_id);
				
				//Create the colour texture
				if (this->target_texture == nullptr)
				{
					gl::glGenTextures(1, &this->gl_texture_id);
					gl::glBindTexture(gl::GL_TEXTURE_2D, this->gl_texture_id);
					gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, (gl::GLint)gl::GL_RGBA16F, this->dimensions.x, this->dimensions.y, 0, gl::GL_RGBA, gl::GL_FLOAT, 0);
					gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, (gl::GLint)gl::GL_LINEAR);
					gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, (gl::GLint)gl::GL_LINEAR);
					gl::glFramebufferTexture2D(gl::GL_FRAMEBUFFER, gl::GL_COLOR_ATTACHMENT0, gl::GL_TEXTURE_2D, this->gl_texture_id, 0);
					
					//Create a depth buffer
					gl::glGenRenderbuffers(1, &this->gl_depthbuffer_id);
					gl::glBindRenderbuffer(gl::GL_RENDERBUFFER, this->gl_depthbuffer_id);
					gl::glRenderbufferStorage(gl::GL_RENDERBUFFER, gl::GL_DEPTH_COMPONENT, this->dimensions.x, this->dimensions.y);
					gl::glFramebufferRenderbuffer(gl::GL_FRAMEBUFFER, gl::GL_DEPTH_ATTACHMENT, gl::GL_RENDERBUFFER, this->gl_depthbuffer_id);
				}
				else
				{
					//Buffer the existing texture
					this->target_texture->buffer();
					gl::glBindTexture(gl::GL_TEXTURE_2D, this->target_texture->getGLID());
					//gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, (gl::GLint)gl::GL_RGBA16F, this->target_texture->getSize().x, this->target_texture->getSize().y, 0, gl::GL_RGBA, gl::GL_FLOAT, 0);
					gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, (gl::GLint)gl::GL_LINEAR);
					gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, (gl::GLint)gl::GL_LINEAR);
					gl::glFramebufferTexture2D(gl::GL_FRAMEBUFFER, gl::GL_COLOR_ATTACHMENT0, gl::GL_TEXTURE_2D, this->target_texture->getGLID(), 0);
					
					//Create a depth buffer
					gl::glGenRenderbuffers(1, &this->gl_depthbuffer_id);
					gl::glBindRenderbuffer(gl::GL_RENDERBUFFER, this->gl_depthbuffer_id);
					gl::glRenderbufferStorage(gl::GL_RENDERBUFFER, gl::GL_DEPTH_COMPONENT, this->target_texture->getSize().x, this->target_texture->getSize().y);
					gl::glFramebufferRenderbuffer(gl::GL_FRAMEBUFFER, gl::GL_DEPTH_ATTACHMENT, gl::GL_RENDERBUFFER, this->gl_depthbuffer_id);
				}
				
				gl::GLenum attachments[1] = {gl::GL_COLOR_ATTACHMENT0};
				gl::glDrawBuffers(1, attachments);
				
				IO::test(gl::glCheckFramebufferStatus(gl::GL_FRAMEBUFFER) == gl::GL_FRAMEBUFFER_COMPLETE, "Framebuffer initiation", true);
				
				//Unbind the framebuffer just incase it interferes with anything else later on
				gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, 0); 
			}
			
			void DrawBuffer::setSize(glm::ivec2 dimensions)
			{
				dimensions = glm::max(glm::ivec2(1, 1), dimensions);
				
				if (this->dimensions != dimensions && this->target_texture == nullptr)
				{
					this->dimensions = dimensions;
					
					//Bind the framebuffer
					gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, this->gl_id);
					
					gl::glBindTexture(gl::GL_TEXTURE_2D, this->gl_texture_id);
					gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, (gl::GLint)gl::GL_RGBA32F, this->dimensions.x, this->dimensions.y, 0, gl::GL_RGBA, gl::GL_UNSIGNED_BYTE, 0);
					
					gl::glBindRenderbuffer(gl::GL_RENDERBUFFER, this->gl_depthbuffer_id);
					gl::glRenderbufferStorage(gl::GL_RENDERBUFFER, gl::GL_DEPTH_COMPONENT, this->dimensions.x, this->dimensions.y);
					
					gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, 0);
					
					IO::output("Changed draw buffer size to " + std::to_string(this->dimensions.x) + "x" + std::to_string(this->dimensions.y));
				}
				else
				{
					//No size change, no need to reallocate framebuffer data
				}
			}
			
			glid DrawBuffer::getGLID()
			{
				return this->gl_id;
			}
			
			glid DrawBuffer::getTextureGLID()
			{
				if (this->target_texture == nullptr)
					return this->gl_texture_id;
				else
					return this->target_texture->getGLID();
			}
			
			glid DrawBuffer::getDepthBufferGLID()
			{
				return this->gl_depthbuffer_id;
			}
		}
	}
}
