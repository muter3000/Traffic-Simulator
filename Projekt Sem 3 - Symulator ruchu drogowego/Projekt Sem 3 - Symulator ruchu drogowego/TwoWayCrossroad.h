#pragma once
#include "Crossroad.h"
class TwoWayCrossroad :
	public Crossroad
{
public:
	TwoWayCrossroad(sf::Vector2f _pos,Orientation _orientation);
	virtual Car::Turn getTurn(sf::Vector2f cPos);
};

