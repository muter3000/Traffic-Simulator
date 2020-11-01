#pragma once
#include "Infrastructure.h"
class Road :
	public Infrastructure
{
public:
	Road(sf::Vector2f _pos, Orientation _orientation,int length);
	virtual void draw(sf::RenderWindow* window);
	virtual Car::Turn getTurn(sf::Vector2f cPos);
};

