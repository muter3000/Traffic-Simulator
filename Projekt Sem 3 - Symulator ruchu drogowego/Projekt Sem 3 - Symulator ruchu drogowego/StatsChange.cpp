#include "StatsChange.h"
#include	"Car.h"
StatsChange::StatsChange(sf::Vector2f _pos, sf::Color _color, sf::Vector2f _size)
{
	color = _color;
	pos = _pos;
	size = _size;
	rect.setSize(size);
	rect.setPosition(pos);
	rect.setFillColor(color);
	int h = 29;
	int i = h + 5;
	title =				new TextControll(sf::Vector2f(5, 5) +pos,			"Change selected vehicle stats", sf::Vector2f(size.x - 10, h), sf::Color(190, 210, 190));
	_nMaxVelocity =		new TextControll(sf::Vector2f(5, 5 + i) + pos,		"New maximum velocity",			 sf::Vector2f(size.x - 10, h));
	nMaxVelocity =		new InputBox(sf::Vector2f(5, 5 + 2 * i) + pos,	"60",							 sf::Vector2f(size.x - 10, h));
	iBoxVector.push_back(nMaxVelocity);
	_nAcceleration =	new TextControll(sf::Vector2f(5, 5 + 3 * i) + pos,	"New maximum acceleration",		 sf::Vector2f(size.x - 10, h));
	nAcceleration =		new InputBox(sf::Vector2f(5, 5 + 4 * i) + pos,	"10",							 sf::Vector2f(size.x - 10, h));
	iBoxVector.push_back(nAcceleration);
	apply =				new Button(sf::Vector2f(5, 5 + 5 * i) + pos,	"Apply changes",				 sf::Vector2f(size.x - 10, 65));	
	activeCar = nullptr;
}

StatsChange::~StatsChange()
{
	delete title;
	delete _nMaxVelocity;
	delete nMaxVelocity;
	delete _nAcceleration;
	delete nAcceleration;
	delete apply;
}

InputBox* StatsChange::getVPointer()
{
	return nMaxVelocity;
}

InputBox* StatsChange::getAPointer()
{
	return nAcceleration;
}

void StatsChange::draw(sf::RenderWindow* window)
{
	window->draw(rect);
	title->draw(window);
	_nMaxVelocity->draw(window);
	nMaxVelocity->draw(window);
	_nAcceleration->draw(window);
	nAcceleration->draw(window);
	apply->draw(window);
}

void StatsChange::checkButtonClick(sf::Vector2i checked)
{
	if (apply->isInBounds(checked))
	{
		if (activeCar)
		{
			apply->click();
			float nA  = (float)(*nAcceleration)>0? (float)(*nAcceleration):10;
			float nMV = (float)(*nMaxVelocity)>0 ? (float)(*nMaxVelocity):60;
			activeCar->setAccelaration(nA);
			activeCar->setMaxVelocity(nMV);
		}
	}
}

