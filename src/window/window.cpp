//----LOCAL----
#include "window.h"
#include "common/io.h"

namespace Vast
{
	namespace Window
	{
		Window::Window()
		{
			IO::output("Creating window");
		}

		void Window::initiate()
		{
			this->settings.majorVersion = 3;
			this->settings.minorVersion = 3;
			this->settings.attributeFlags = sf::ContextSettings::Attribute::Core;

			this->internal_window.create(sf::VideoMode(640, 480), "Window", sf::Style::Default, this->settings);

			this->internal_window.setVerticalSyncEnabled(true);
			this->internal_window.setFramerateLimit(60);

			IO::output("Initiated window");
		}

		void Window::setTitle(std::string title)
		{
			this->title = title;
			this->internal_window.setTitle(title);
		}

		std::string Window::getTitle()
		{
			return this->title;
		}

		void Window::setFPS(uint16 fps)
		{
			this->internal_window.setFramerateLimit(fps);
		}

		void Window::setSize(uint16 width, uint16 height)
		{
			this->internal_window.setSize(sf::Vector2u(width, height));
		}

		sf::Vector2u Window::getSize()
		{
			return this->internal_window.getSize();
		}

		bool Window::activate(bool active)
		{
			return this->internal_window.setActive(active);
		}

		bool Window::tick()
		{
			bool closed = false;

			sf::Event event;
			while (this->internal_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					closed = true;
					IO::output("Closed window");
				}
				else if (event.type == sf::Event::Resized)
				{
					IO::output("Resized or moved window");
				}
			}

			this->internal_window.display();

			return closed;
		}

		void Window::close()
		{
			this->internal_window.close();
		}
	}
}
