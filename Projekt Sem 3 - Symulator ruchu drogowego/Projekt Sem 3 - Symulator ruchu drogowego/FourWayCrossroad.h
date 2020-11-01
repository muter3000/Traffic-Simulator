#pragma once
#include "Crossroad.h"
class FourWayCrossroad :
	public Crossroad
{
public:
	FourWayCrossroad(sf::Vector2f _pos);
	virtual Car::Turn getTurn(sf::Vector2f pos);
};

