//----LOCAL----
#include "drawbuffer.h"
#include "common/io.h"

namespace Vast
{
	namespace Render
	{
		namespace Renderer
		{
			DrawBuffer::DrawBuffer()
			{
				//Constructor
			}
			
			void DrawBuffer::initialise()
			{
				//Create the framebuffer
				gl::glGenFramebuffers(1, &this->gl_id);
				gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, this->gl_id);
				
				//Create the colour texture
				gl::glGenTextures(1, &this->gl_texture_id);
				gl::glBindTexture(gl::GL_TEXTURE_2D, this->gl_texture_id);
				gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, (gl::GLint)gl::GL_RGBA32F, this->width, this->height, 0, gl::GL_RGBA, gl::GL_UNSIGNED_BYTE, 0);
				gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, (gl::GLint)gl::GL_LINEAR);
				gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, (gl::GLint)gl::GL_LINEAR);
				
				//Create a depth buffer
				gl::glGenRenderbuffers(1, &this->gl_depth_id);
				gl::glBindRenderbuffer(gl::GL_RENDERBUFFER, this->gl_depth_id);
				gl::glRenderbufferStorage(gl::GL_RENDERBUFFER, gl::GL_DEPTH_COMPONENT, this->width, this->height);
				gl::glFramebufferRenderbuffer(gl::GL_FRAMEBUFFER, gl::GL_DEPTH_ATTACHMENT, gl::GL_RENDERBUFFER, this->gl_depth_id);
				
				//Attach the texture(s) to the framebuffer
				gl::glFramebufferTexture(gl::GL_FRAMEBUFFER, gl::GL_COLOR_ATTACHMENT0, this->gl_texture_id, 0);
				
				gl::GLenum attachments[1] = {gl::GL_COLOR_ATTACHMENT0};
				gl::glDrawBuffers(1, attachments);
				
				IO::test(gl::glCheckFramebufferStatus(gl::GL_FRAMEBUFFER) == gl::GL_FRAMEBUFFER_COMPLETE, "Checking Framebuffer status", true);
				
				gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, 0);
			}
			
			void DrawBuffer::setSize(uint32 width, uint32 height)
			{
				if (width != this->width || height != this->height)
				{
					this->width = width;
					this->height = height;
					
					//Bind the framebuffer
					gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, this->gl_id);
					
					gl::glBindTexture(gl::GL_TEXTURE_2D, this->gl_texture_id);
					gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, (gl::GLint)gl::GL_RGBA32F, this->width, this->height, 0, gl::GL_RGBA, gl::GL_UNSIGNED_BYTE, 0);
					
					gl::glBindRenderbuffer(gl::GL_RENDERBUFFER, this->gl_depth_id);
					gl::glRenderbufferStorage(gl::GL_RENDERBUFFER, gl::GL_DEPTH_COMPONENT, this->width, this->height);
					
					gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, 0);
					
					IO::output("Changed draw buffer size to " + std::to_string(width) + "x" + std::to_string(height));
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
				return this->gl_texture_id;
			}
			
			glid DrawBuffer::getDepthGLID()
			{
				return this->gl_depth_id;
			}
		}
	}
}
