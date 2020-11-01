#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Functions.h"

class ObiektGraficzny
{
protected:
	sf::Vector2f pos;
public:
	ObiektGraficzny();
	~ObiektGraficzny();
	void setPos(sf::Vector2f nPos);
	sf::Vector2f getPos();
	virtual void draw(sf::RenderWindow* window) = 0;
};

