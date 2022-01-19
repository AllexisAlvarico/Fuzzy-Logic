#include "Game.h"

Game::Game() : m_window(sf::VideoMode(800u, 600u), "Fuzzy Logic")
{
	m_exitGame = false;
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	while (m_window.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_exitGame = true;
		}

		if (event.type == sf::Keyboard::Escape)
		{
			m_exitGame = true;
		}

		if (m_exitGame)
			m_window.close();
	}
}

void Game::update(sf::Time t_deltaTime)
{
}

void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.display();
}
