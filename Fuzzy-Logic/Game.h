#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Fuzzy.h"
#include "Entity.h"
#include "Global.h"

class Game
{
public:

	Game();
	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	void setupGame();

	sf::RenderWindow m_window;
	bool m_exitGame;
	Fuzzy m_fuzzyLogic;

	double m_troops = 0.0;
	double m_range = 0.0;
	double m_deploy = 0.0;


	std::vector<Entity> m_enemySlots;
	std::vector<Entity> m_friendlySlots;
	sf::Texture m_enemyTexture;
	sf::Texture m_friendlyTexture;

	sf::Sprite m_mapSprite;
	sf::Texture m_mapTexture;

};

#endif // !GAME