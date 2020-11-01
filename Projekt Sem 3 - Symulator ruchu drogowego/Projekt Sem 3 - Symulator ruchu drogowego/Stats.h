#pragma once
#include "Canvas.h"
#include "TextControll.h"
class Stats :
	public Canvas
{
private:
	TextControll* title;
	TextControll* maxVelocity;
	TextControll* _maxVelocity;
	TextControll* currentVelocity;
	TextControll* _currentVelocity;
	TextControll* acceleration;
	TextControll* _acceleration;
public:
	Stats(sf::Vector2f _pos, sf::Color _color, sf::Vector2f _size);
	~Stats();
	void update();
	virtual void draw(sf::RenderWindow* window);
};

