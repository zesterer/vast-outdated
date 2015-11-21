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
				gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, (gl::GLint)gl::GL_RGBA32F, this->dimensions.x, this->dimensions.y, 0, gl::GL_RGBA, gl::GL_UNSIGNED_BYTE, 0);
				gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, (gl::GLint)gl::GL_LINEAR);
				gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, (gl::GLint)gl::GL_LINEAR);
				gl::glFramebufferTexture2D(gl::GL_FRAMEBUFFER, gl::GL_COLOR_ATTACHMENT0, gl::GL_TEXTURE_2D, this->gl_texture_id, 0);
				
				//Create a depth buffer
				gl::glGenRenderbuffers(1, &this->gl_depthbuffer_id);
				gl::glBindRenderbuffer(gl::GL_RENDERBUFFER, this->gl_depthbuffer_id);
				gl::glRenderbufferStorage(gl::GL_RENDERBUFFER, gl::GL_DEPTH_COMPONENT, this->dimensions.x, this->dimensions.y);
				gl::glFramebufferRenderbuffer(gl::GL_FRAMEBUFFER, gl::GL_DEPTH_ATTACHMENT, gl::GL_RENDERBUFFER, this->gl_depthbuffer_id);
				
				gl::GLenum attachments[1] = {gl::GL_COLOR_ATTACHMENT0};
				gl::glDrawBuffers(1, attachments);
				
				IO::test(gl::glCheckFramebufferStatus(gl::GL_FRAMEBUFFER) == gl::GL_FRAMEBUFFER_COMPLETE, "Framebuffer initiation", true);
				
				gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, 0);
			}
			
			void DrawBuffer::setSize(glm::ivec2 dimensions)
			{
				if (this->dimensions != dimensions)
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
				return this->gl_texture_id;
			}
			
			glid DrawBuffer::getDepthBufferGLID()
			{
				return this->gl_depthbuffer_id;
			}
		}
	}
}
