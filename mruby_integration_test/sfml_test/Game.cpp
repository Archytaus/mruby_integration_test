#include "Game.h"

#include <SFML/OpenGL.hpp>
#include <glew.h>

Game::Game(void)
{
	window = new sf::Window(sf::VideoMode(800, 600), "mruby Integration Test", sf::Style::Default, sf::ContextSettings(32));
	window->setVerticalSyncEnabled(true);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		auto error = glewGetErrorString(err);
		fprintf(stderr, "Error: %s\n", error);
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	clock = new sf::Clock();

	renderManager = new RenderManager();
	auto model = renderManager->loadModel("Assets/Models/test.dae");

	EntityId newEntity = 1;
	wpSys.components[newEntity] = new WorldPositionComponent(newEntity);
	rSys.components[newEntity] = new RenderComponent(newEntity, renderManager, model);

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
				shutdown();
			}
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		sf::Time elapsed = clock->restart();

		// update every component
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			shutdown();
		}

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw...
		for(auto keyValue : rSys.components)
		{
			keyValue.second->render();
		}
		renderManager->finalise();

		// end the current frame (internally swaps the front and back buffers)
		window->display();
	}
}

void Game::shutdown()
{
	running = false;
}