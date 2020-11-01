#pragma once
#include "Crossroad.h"
class ThreeWayCrossroad :
	public Crossroad
{

public:
	ThreeWayCrossroad(sf::Vector2f _pos, Orientation _orientation);
	virtual Car::Turn getTurn(sf::Vector2f cPos);
};

