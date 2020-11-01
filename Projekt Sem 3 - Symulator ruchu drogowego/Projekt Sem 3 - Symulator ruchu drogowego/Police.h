#pragma once
#include "Car.h"
class Police :
	public Car
{
public:
	Police(sf::Vector2f _pos, sf::Vector2f headingN, float _maxV, float _a);
};

