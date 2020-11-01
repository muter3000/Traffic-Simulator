#include "Canvas.h"


Canvas::Canvas()
{
	activeCar = nullptr;
}

Canvas::Canvas(sf::Vector2f _pos, sf::Color _color,sf::Vector2f _size)
{
	activeCar = nullptr;
	color = _color;
	pos = _pos;
	size = _size;
	rect.setSize(size);
	rect.setPosition(pos);
	rect.setFillColor(color);
}

Canvas::~Canvas()
{
}

bool Canvas::isInBound(sf::Vector2i checked) const
{
	checked -= (sf::Vector2i)pos;
	return(checked.x > 0 && checked.y > 0 && checked.x < rect.getSize().x && checked.y <rect.getSize().y);
}

InputBox* Canvas::getClickedInputBoxP(sf::Vector2i checked) const
{
	for (InputBox* iBox : iBoxVector)
	{
		if (iBox->isInBounds(checked))
			return(iBox);
	}
	return nullptr;
}
void Canvas::setActiveCar(Car* newActive)
{
	activeCar = newActive;
}

