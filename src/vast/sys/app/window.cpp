#include "vast/sys/app/window.h"

#include "vast/com/io/output.h"

namespace Vast
{
	namespace Sys
	{
		namespace App
		{
			static bool glob_init_window_state = false;

			i32 init_windowing()
			{
				if (glob_init_window_state) // We've already initiated, so ignore
					return 0;

				i32 status = SDL_Init(SDL_INIT_VIDEO);

				switch (status)
				{
				case 0:
					Com::IO::output("Global windowing initiated");
					break;

				default:
					Com::IO::output("Global windowing initiation failed: " + std::to_string(status));
					break;
				}

				// We've already tried initiation
				glob_init_window_state = true;

				return status;
			}

			i32 Window::build(i32 width, i32 height)
			{
				if (this->_is_built) // The window is already built, so nothing to do
					return 0;

				this->_width = width;
				this->_height = height;

				// Initiate global windowing
				init_windowing();

				// Configure SDL with specific OpenGL attributes
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // Major version 3
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); // Minor version 3
				SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Enable double-buffering
				SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // Specify a 24-bit depth buffer

				// Attempt to create a window
				this->_intern_window = SDL_CreateWindow(this->_title.c_str(),
														SDL_WINDOWPOS_CENTERED,
														SDL_WINDOWPOS_CENTERED,
														this->_width,
														this->_height,
														SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

				if (this->_intern_window)
					Com::IO::output("Successfully created window");
				else // An error occured
				{
					Com::IO::error("Failed to create window", __LINE__);
					return 1;
				}

				// Attempt to create a context
				this->_intern_context = SDL_GL_CreateContext(this->_intern_window);

				if (this->_intern_window)
					Com::IO::output("Successfully created OpenGL context");
				else // An error occured
				{
					Com::IO::error("Failed to create OpenGL context", __LINE__);
					return 2;
				}

				// Enable vertical syncronisation (vsync)
				if (this->_vsync)
					SDL_GL_SetSwapInterval(1);

				this->finish_build("Window");

				return 0; // No error
			}

			bool Window::is_active()
			{
				return this->_is_built;
			}

			i32 Window::handle_events()
			{
				/*sf::Event event;
				while (this->_intern_window.pollEvent(event))
				{
					switch (event.type)
					{
					case sf::Event::Closed:
						this->_intern_window.close();
						Com::IO::output("Closed window");
						break;

					case sf::Event::Resized:
						Com::IO::output("Resized window");
						break;

					default:
						break;
					}

				}*/

				return 0; // No error
			}

			i32 Window::tick()
			{
				// Handle window events
				this->handle_events();

				// Swap window buffer
				SDL_GL_SwapWindow(this->_intern_window);

				return 0; // No error
			}

			i32 Window::close()
			{
				SDL_GL_DeleteContext(this->_intern_context);
				SDL_DestroyWindow(this->_intern_window);

				return 0;
			}
		}
	}
}
