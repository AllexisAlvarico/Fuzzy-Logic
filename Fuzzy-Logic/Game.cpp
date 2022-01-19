#include "Game.h"

Game::Game() : m_window(sf::VideoMode(m_width,m_height), "Fuzzy Logic") 
{
	if (!m_enemyTexture.loadFromFile("assets/enemySoldier.png"))
	{
		//error
		std::cout << "Cannot find enemy texture" << std::endl;
	}	
	if (!m_friendlyTexture.loadFromFile("assets/friendlySoldier.png"))
	{
		//error
		std::cout << "Cannot find friendly texture" << std::endl;
	}
	if (!m_mapTexture.loadFromFile("assets/map.png"))
	{
		//error
		std::cout << "Cannot find map texture" << std::endl;
	}

	m_mapSprite.setTexture(m_mapTexture);

	m_exitGame = false;
	setupGame();
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
	for (size_t i = 0; i < m_troops; i++)
	{
		if (m_enemySlots[i].body.getPosition().x <= m_width / 2 + m_range)
			m_enemySlots[i].body.move(1,0);
	}

	for (size_t i = 0; i < m_deploy; i++)
	{
		if(m_friendlySlots[i].body.getPosition().x >= 650)
			m_friendlySlots[i].body.move(-1,0);
	}
}

void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_mapSprite);
	for (int i = 0; i < m_enemySlots.size(); i++)
	{
		m_window.draw(m_enemySlots[i].body);
	}
	for (int i = 0; i < m_friendlySlots.size(); i++)
	{
		m_window.draw(m_friendlySlots[i].body);
	}
	m_window.display();
}

void Game::setupGame()
{
	std::cout << "Hostiles: ";
	std::cin >> m_troops;
	std::cout << "Range: ";
	std::cin >> m_range;

	double m_tinyForce = m_fuzzyLogic.FuzzyTriangle(m_troops, -10.0, 0.0, 10.0);
	double m_smallForce = m_fuzzyLogic.FuzzyTrapezoid(m_troops, 2.5, 10.0, 15.0, 20.0);
	double m_mediumForce = m_fuzzyLogic.FuzzyTrapezoid(m_troops, 15.0, 20.0, 25.0, 30.0);
	double m_largeForce = m_fuzzyLogic.FuzzyGrade(m_troops, 25.0, 30.0);

	double m_close = m_fuzzyLogic.FuzzyTriangle(m_range, -30.0, 0.0, 30.0);
	double m_medium = m_fuzzyLogic.FuzzyTrapezoid(m_range, 10.0, 30.0, 50.0, 70.0);
	double m_far = m_fuzzyLogic.FuzzyGrade(m_range, 50.0, 120.0);


	//( Medium AND Tiny ) OR ( Medium AND Small ) OR ( Far AND NOT(Large) )
	double m_lowThreat = m_fuzzyLogic.FuzzyOR(m_fuzzyLogic.FuzzyAND(m_medium, m_tinyForce), m_fuzzyLogic.FuzzyOR(
		m_fuzzyLogic.FuzzyAND(m_medium, m_smallForce),  m_fuzzyLogic.FuzzyAND(m_far,m_fuzzyLogic.FuzzyNOT(m_largeForce))));
	//(Close AND Tiny) OR(Medium AND Moderate) OR(Far AND Large)
	double m_mediumThreat = m_fuzzyLogic.FuzzyOR(m_fuzzyLogic.FuzzyAND(m_close, m_tinyForce), m_fuzzyLogic.FuzzyOR(
		m_fuzzyLogic.FuzzyAND(m_medium, m_mediumForce), m_fuzzyLogic.FuzzyAND(m_far,m_largeForce)));
	//(Close AND NOT(Medium)) OR(Medium AND Large)
	double m_highThreat = m_fuzzyLogic.FuzzyOR(m_fuzzyLogic.FuzzyAND(m_close, m_fuzzyLogic.FuzzyNOT(m_mediumForce)), m_fuzzyLogic.FuzzyAND(m_medium,m_largeForce));

	m_deploy = (m_lowThreat * 10.0 + m_mediumThreat * 30.0 + m_highThreat * 50.0) / (m_lowThreat + m_mediumThreat + m_highThreat);

	std::cout << m_troops << " Enemy troops, Spotted at the distances of " << m_range << std::endl;
	std::cout << "Deploying Reinforcement size of " << m_deploy << " Troops" << std::endl;


	for (size_t i = 0; i < m_troops; i++)
	{
		m_enemySlots.push_back(Entity(0 - rand() % 100, rand() % 550,m_enemyTexture));
	}

	for (size_t i = 0; i < m_deploy; i++)
	{
		m_friendlySlots.push_back(Entity(750 + rand() % 100, rand() % 550, m_friendlyTexture));
	}

}
