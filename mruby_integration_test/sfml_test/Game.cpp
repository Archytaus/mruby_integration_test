#include "Game.h"

#include <SFML/OpenGL.hpp>

Game::Game(void)
{
	window = new sf::Window(sf::VideoMode(800, 600), "mruby Integration Test", sf::Style::Default, sf::ContextSettings(32));
	window->setVerticalSyncEnabled(true);

	clock = new sf::Clock();
	
	// load resources, initialize the OpenGL states, ...
}


Game::~Game(void)
{
}

void Game::run()
{
	// run the main loop
	running = true;

	while (running)
	{
		// handle events
		sf::Event event;
		while (window->pollEvent(event))
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

		
		sf::Time elapsed = clock->restart();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			running = false;
		}
		// update every component

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw...

		// end the current frame (internally swaps the front and back buffers)
		window->display();
	}
}