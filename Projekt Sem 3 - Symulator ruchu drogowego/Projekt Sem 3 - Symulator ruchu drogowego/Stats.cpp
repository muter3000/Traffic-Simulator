#include "Stats.h"

Stats::Stats(sf::Vector2f _pos, sf::Color _color, sf::Vector2f _size)
{
	color = _color;
	pos = _pos;
	size = _size;
	rect.setSize(size);
	rect.setPosition(pos);
	rect.setFillColor(color);
	int h = 29;
	int i = h + 5;
	title =				new TextControll(sf::Vector2f(5, 5)		+ pos, "Selected vehicle stats", sf::Vector2f(size.x - 10, h),sf::Color(190, 210, 190));
	_maxVelocity =		new TextControll(sf::Vector2f(5, 5+i)      + pos, "Maximum velocity",	 sf::Vector2f(size.x - 10, h));
	maxVelocity =		new TextControll(sf::Vector2f(5, 5+2*i)	+ pos, "-",						 sf::Vector2f(size.x - 10, h));
	_currentVelocity =	new TextControll(sf::Vector2f(5, 5+3*i)  + pos, "Current velocity",		 sf::Vector2f(size.x - 10, h));
	currentVelocity =	new TextControll(sf::Vector2f(5, 5+4*i)	+ pos, "-",						 sf::Vector2f(size.x - 10, h));
	_acceleration =		new TextControll(sf::Vector2f(5, 5+5*i)  + pos, "Maximum acceleration",	 sf::Vector2f(size.x - 10, h));
	acceleration =		new TextControll(sf::Vector2f(5, 5+6*i)  + pos, "-",						 sf::Vector2f(size.x - 10, h));
	activeCar = nullptr;
}

Stats::~Stats()
{
	delete title;
	delete _maxVelocity;
	delete maxVelocity;
	delete _currentVelocity;
	delete currentVelocity;
	delete _acceleration;
	delete acceleration;
}

void Stats::update()
{
	if (activeCar)
	{
		currentVelocity->setText(std::to_string(std::ceil(vMagnitude(activeCar->getVelocity()) * 100.0) / 100.0));
		maxVelocity->setText(std::to_string(std::ceil(activeCar->getMaxVelocity() * 100.0) / 100.0));
		acceleration->setText(std::to_string(std::ceil(vMagnitude(activeCar->getAccelaration()) * 100.0) / 100.0));
	}
}

void Stats::draw(sf::RenderWindow* window)
{
	window->draw(rect);
	title->draw(window);
	maxVelocity->draw(window);
	currentVelocity->draw(window);
	acceleration->draw(window);
	_maxVelocity->draw(window);
	_currentVelocity->draw(window);
	_acceleration->draw(window);
}
