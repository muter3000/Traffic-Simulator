#include "StartSettings.h"

StartSettings::StartSettings(sf::Vector2f _pos, sf::Color _color, sf::Vector2f _size)
{
	color = _color;
	pos = _pos;
	size = _size;
	rect.setSize(size);
	rect.setPosition(pos);
	rect.setFillColor(color);
	int h = 29;
	int i = h + 5;
	title =			 new TextControll (sf::Vector2f(5, 5)		 + pos,		"Simulation controls",			sf::Vector2f(size.x - 10, h), sf::Color(190, 210, 190));
	cCarCount =		 new TextControll (sf::Vector2f(5, 5 + i)	 + pos,		"New vehicle count",			sf::Vector2f(size.x - 10, h));
	carCount =		 new InputBox(sf::Vector2f(5, 5 + 2 * i) + pos,		"30",							sf::Vector2f(size.x - 10, h));
	iBoxVector.push_back(carCount);
	cRDistance =	 new TextControll (sf::Vector2f(5, 5 + 3 * i) + pos,		"New distance beetween roads",	sf::Vector2f(size.x - 10, h));
	rDistance =		 new InputBox(sf::Vector2f(5, 5 + 4 * i) + pos,		"70",							sf::Vector2f(size.x - 10, h));
	iBoxVector.push_back(rDistance);
	generate =		 new Button	 (sf::Vector2f(5, 5 + 5 * i) + pos,		"Generate new simulation",		sf::Vector2f(size.x - 10, 65));
	activeCar = nullptr;
}

StartSettings::~StartSettings()
{
	delete title;
	delete carCount;
	delete cCarCount;
	delete rDistance;
	delete cRDistance;
	delete generate;
}

void StartSettings::draw(sf::RenderWindow* window)
{
	window->draw(rect);
	title->draw(window);
	carCount->draw(window);
	cCarCount->draw(window);
	rDistance->draw(window);
	cRDistance->draw(window);
	generate->draw(window);
}

bool StartSettings::checkButtonClick(sf::Vector2i checked)
{
	if (generate->isInBounds(checked))
	{
		generate->click();
		return true;
	}
	return false;
}

int StartSettings::getCarCount() const
{
	return (int)(*carCount)>0? (int)(*carCount):1;
}

int StartSettings::getRDistance() const
{
	if ((int)(*rDistance) > 600)
		return 600;
	return (int)(*rDistance) >= 0? (int)(*rDistance):0;
}
