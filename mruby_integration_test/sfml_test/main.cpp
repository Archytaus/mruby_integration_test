#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

int main()
{
	// create the window
	sf::Window window(sf::VideoMode(800, 600), "mruby Integration Test", sf::Style::Default, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);

	// load resources, initialize the OpenGL states, ...
	sf::Clock clock;

	// run the main loop
	bool running = true;
	while (running)
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// end the program
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		
		sf::Time elapsed = clock.restart();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			running = false;
		}
		// update every component

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw...

		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}


	return 0;
}