#ifndef Entity_H
#define Entity_H
#include "SFML/Graphics.hpp"

struct Entity
{
	Entity(float t_posX, float t_posY,sf::Color t_color){
		body.setPosition(t_posX, t_posY);
		body.setFillColor(t_color);
		body.setRadius(10);
		body.setOutlineThickness(2.0);
		body.setOutlineColor(sf::Color::Black);
	}
	sf::CircleShape body;
};
#endif