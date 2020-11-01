#pragma once
#include "Car.h"
class Ambulance :
	public Car
{
public:
	Ambulance(sf::Vector2f _pos, sf::Vector2f headingN, float _maxV, float _a);
};

