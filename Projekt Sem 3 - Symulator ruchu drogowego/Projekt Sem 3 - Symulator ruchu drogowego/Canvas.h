#pragma once
#include "ObiektGraficzny.h"
#include "InputBox.h"
#include "Car.h"
#include <vector>
class Canvas : public ObiektGraficzny
{
protected:
	sf::Vector2f size;
	sf::Color color;
	sf::RectangleShape rect;
	std::vector<InputBox*> iBoxVector;
	Car* activeCar;
public:
	Canvas();
	Canvas(sf::Vector2f _pos, sf::Color _color, sf::Vector2f _size);
	~Canvas();
	virtual void draw(sf::RenderWindow* window) = 0;
	bool isInBound(sf::Vector2i checked) const;
	virtual InputBox* getClickedInputBoxP(sf::Vector2i checked) const;
	void setActiveCar(Car* newActive);
};

