#ifndef Entity_H
#define Entity_H
#include "SFML/Graphics.hpp"

struct Entity
{
	Entity(float t_posX, float t_posY,sf::Texture& t_texture){
		body.setPosition(t_posX, t_posY);
		body.setTexture(t_texture);
		body.setOrigin(10.0, 10.0);
	}
	sf::Sprite body;
};
#endif