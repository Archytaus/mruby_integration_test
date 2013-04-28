#include "Game.h"

#include <glew.h>
#include <SFML/OpenGL.hpp>
#include <ctime>

#include "Entity.h"

Game::Game(void)
	: _hasFocus(true)
{
	window = new sf::Window(sf::VideoMode(800, 600), "mruby Integration Test", sf::Style::Default, sf::ContextSettings(32));
	window->setVerticalSyncEnabled(true);

	auto load_start = std::clock();

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

	renderManager = new RenderManager(this);
	screenManager = new ScreenManager(this);
	scriptManager = new ScriptManager(this);

	int i = 0;
	for(int x = 0; x < 3; x++)
	{
		for(int y = 0; y < 3; y++)
		{
			auto entity = new Entity(i);
			auto positionComponent = transformComponents.components[i] = new TransformComponent(i);
			positionComponent->position.x = x * 4;
			positionComponent->position.z = y * 4;

			positionComponent->scale.y = 1 + (i % 2);

			entity->addComponent(transformComponents.components[i]);
			entity->addComponent(scriptManager->createScriptComponent(i, "Test")->withTransformComponent(positionComponent));

			auto renderComponent = renderManager->createRenderComponent(i, positionComponent);
			entity->addComponent(renderComponent);
			renderComponent->load();

			i++;
		}
	}

	auto cameraEntity = new Entity(i + 1);
	cameraEntity->addComponent(scriptManager->createScriptComponent(i + 1, "MyCamera")->withCameraComponent(renderManager->camera));

	auto load_end = std::clock();
	auto elapsed = double(load_end - load_start);
	printf_s("Load Time: %.2f ms\n", elapsed);
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
			switch (event.type)
			{
			case sf::Event::Closed:
				shutdown();
			case sf::Event::Resized:
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			case sf::Event::GainedFocus:
				_hasFocus = true;
				break;
			case sf::Event::LostFocus:
				_hasFocus = false;
				break;
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

bool Game::hasFocus()
{
	return _hasFocus;
}

void Game::shutdown()
{
	running = false;
}