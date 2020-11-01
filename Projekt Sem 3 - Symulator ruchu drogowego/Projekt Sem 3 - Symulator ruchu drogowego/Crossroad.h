#pragma once
#include "Infrastructure.h"
#include "Car.h"
class Crossroad :
	public Infrastructure
{
protected:
	int busy;
	Car* queue[4];
public:
	Crossroad();
	~Crossroad();
	virtual void draw(sf::RenderWindow* window);
	void incrementBusyState(int state);
	bool isBusy();
	void addToQueue(Car* c);
	void resumeCar();
};

