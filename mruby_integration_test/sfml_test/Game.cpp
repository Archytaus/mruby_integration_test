#include "Game.h"

#include <glew.h>
#include <SFML/OpenGL.hpp>

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

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	clock = new sf::Clock();

	renderManager = new RenderManager();
	screenManager = new ScreenManager(this);
	scriptManager = new ScriptManager();

	worldPositionComponents.components[0] = new WorldPositionComponent(0);
	scriptManager->createScriptComponent(0, "Test");
	auto renderComponent = renderManager->createRenderComponent(0, worldPositionComponents.components[0]);
	renderComponent->load();
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
		screenManager->update(elapsed);
		scriptManager->update(elapsed);

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw...
		screenManager->render();
		renderManager->render();

		// end the current frame (internally swaps the front and back buffers)
		window->display();
	}
}

void Game::shutdown()
{
	running = false;
}