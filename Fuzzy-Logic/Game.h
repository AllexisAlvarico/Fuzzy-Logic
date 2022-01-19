#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>

class Game
{
public:

	Game();
	~Game();

	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	sf::RenderWindow m_window;
	bool m_exitGame;

};

#endif // !GAME