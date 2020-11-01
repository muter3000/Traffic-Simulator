#pragma once
#include "Canvas.h"
#include "TextControll.h"
#include "Button.h"
#include "Car.h"
#include "Police.h"
#include "Ambulance.h"
#include "Map.h"
#include <ctime>
#include <chrono>

class Simulation:
	public Canvas
{
private:
	struct CarList
	{
		Car* element;
		CarList* pNext;
	};
	void addNewCar();
	Map* map;
	bool paused;

	int roadDistance;
	int cCarAmount;
	int maxCarAmount;
	float tAccelaration;

	Infrastructure* spawnPoint;

	CarList* cars;
	std::clock_t  lastClock;
	std::clock_t  lastSpawn;

public:
	Simulation(sf::Vector2f _pos, sf::Color _color, sf::Vector2f _size);
	~Simulation();
	void update();
	Car* getActiveCar(sf::Vector2i checked);
	virtual void draw(sf::RenderWindow* window);
	void togglePause();
	void generate(int _maxCarAmount, int roadDistance);
};

