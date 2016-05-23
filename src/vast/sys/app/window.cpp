#include "vast/sys/app/window.h"

#include "vast/com/io/output.h"

namespace Vast
{
	namespace Sys
	{
		namespace App
		{
			i32 Window::build()
			{
				this->_intern_settings.depthBits =			24;
				this->_intern_settings.stencilBits =		8;
				this->_intern_settings.antialiasingLevel =	4;
				this->_intern_settings.majorVersion = 		3;
				this->_intern_settings.minorVersion = 		3;
				this->_intern_settings.attributeFlags = sf::ContextSettings::Attribute::Default | sf::ContextSettings::Attribute::Core;

				this->_intern_window.create(sf::VideoMode(640, 480), this->_title, sf::Style::Default, this->_intern_settings);
				this->_intern_window.setFramerateLimit(this->_framelimit);
				this->_intern_window.setVerticalSyncEnabled(this->_vsync);

				return 0; // No error
			}

			i32 Window::activate(bool activate)
			{
				this->_intern_window.setActive(activate);

				return 0; // No error
			}

			bool Window::is_open()
			{
				return this->_intern_window.isOpen();
			}

			i32 Window::handle_events()
			{
				sf::Event event;
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

				}

				return 0; // No error
			}

			i32 Window::tick()
			{
				this->handle_events();

				this->_intern_window.display();

				return 0; // No error
			}
		}
	}
}
