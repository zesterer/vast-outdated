#include "vast/sys/app/window.h"

#include "vast/com/io/output.h"

namespace Vast
{
	namespace Sys
	{
		namespace App
		{
			i32 window_build(Window& window)
			{
				window._intern_settings.depthBits =			24;
				window._intern_settings.stencilBits =		8;
				window._intern_settings.antialiasingLevel =	4;
				window._intern_settings.majorVersion = 		3;
				window._intern_settings.minorVersion = 		3;
				window._intern_settings.attributeFlags = sf::ContextSettings::Attribute::Default | sf::ContextSettings::Attribute::Core;

				window._intern_window.create(sf::VideoMode(640, 480), window._title, sf::Style::Default, window._intern_settings);
				window._intern_window.setFramerateLimit(window._framelimit);
				window._intern_window.setVerticalSyncEnabled(window._vsync);

				return 0; // No error
			}

			i32 window_activate(Window& window, bool activate)
			{
				window._intern_window.setActive(activate);

				return 0; // No error
			}

			bool Window::is_open()
			{
				return this->_intern_window.isOpen();
			}

			i32 window_handle_events(Window& window)
			{
				sf::Event event;
				while (window._intern_window.pollEvent(event))
				{
					switch (event.type)
					{
					case sf::Event::Closed:
						window._intern_window.close();
						Com::IO::output("Closed window");
						break;

					case sf::Event::Resized:
						Com::IO::output("Resized window");
						break;

					default:
						break;
					}

				}

				return 0; // No error
			}

			i32 window_tick(Window& window)
			{
				window_handle_events(window);

				window._intern_window.display();

				return 0; // No error
			}
		}
	}
}
