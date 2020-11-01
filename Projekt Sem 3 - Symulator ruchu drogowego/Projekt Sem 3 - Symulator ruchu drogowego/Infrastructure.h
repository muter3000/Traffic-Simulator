#pragma once
#include "ObiektGraficzny.h"
#include "Car.h"
#include <list>
class Infrastructure :
	public ObiektGraficzny
{
protected:
	bool IsCrossroad;
	sf::Sprite* sprite;
	sf::FloatRect size;
	int roadWidth;
public:
	enum class Orientation { North = 0, East, South, West=3 };
	Orientation orientation;
	enum class IType { twoWay, threeWay, fourWay, road};
	IType type;
	std::list<Car*> carsHere;
	Infrastructure();
	~Infrastructure();
	bool isCrossroad();
	virtual void draw(sf::RenderWindow* window) = 0;
	virtual Car::Turn getTurn(sf::Vector2f pos) = 0;
};

