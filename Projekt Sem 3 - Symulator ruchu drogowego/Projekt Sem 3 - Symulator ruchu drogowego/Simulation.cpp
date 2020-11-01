#include "Simulation.h"

void Simulation::addNewCar()
{
	static std::default_random_engine generator;
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	static std::uniform_real_distribution<float> dis(20, 100);
	if (!cars)
	{
		cars = new CarList{ nullptr,nullptr };
		cars->element = new Car(pos + sf::Vector2f(25, 80), sf::Vector2f(0, 1), std::ceil(dis(generator) * 100.0) / 100.0, 10);
	}
	else
	{
		CarList* iterator = cars;
		while (iterator->pNext)
		{
			iterator = iterator->pNext;
		}
		iterator->pNext = new CarList{ nullptr,nullptr };
		if(dis(generator)-20>8)
			iterator->pNext->element = new Car(pos + sf::Vector2f(25, 80), sf::Vector2f(0, 1), std::ceil(dis(generator) * 100.0) / 100.0, 10);
		else if(dis(generator)-20 > 40)
			iterator->pNext->element = new Police(pos + sf::Vector2f(25, 80), sf::Vector2f(0, 1), std::ceil(dis(generator) * 100.0) / 100.0, 10);
		else
			iterator->pNext->element = new Ambulance(pos + sf::Vector2f(25, 80), sf::Vector2f(0, 1), std::ceil(dis(generator) * 100.0) / 100.0, 10);
	}
}

Simulation::Simulation(sf::Vector2f _pos, sf::Color _color, sf::Vector2f _size)
{
	color = _color;
	pos = _pos;
	size = _size;
	rect.setSize(size);
	rect.setPosition(pos);
	rect.setFillColor(color);
	int h = 29;

	lastSpawn = std::clock();
	lastClock = std::clock();

	cCarAmount = 0;
	maxCarAmount = 0;
	cars = nullptr;
	map = nullptr;
	activeCar = nullptr;

	spawnPoint = nullptr;

	paused = false;

	tAccelaration = 3;
}

Simulation::~Simulation()
{
	CarList* iterator = cars;
	while (iterator)
	{
		CarList* nPointer = iterator->pNext;
		delete iterator->element;
		delete iterator;
		iterator = nPointer;
	}
	delete map;
}

void Simulation::update()
{
	double deltaTime = ((double)std::clock() - (double)lastClock) / (double)CLOCKS_PER_SEC;
	if (cCarAmount < maxCarAmount && spawnPoint->carsHere.size() < std::ceil(roadDistance / 80.0f)&& (((double)std::clock() - (double)lastSpawn) / (double)CLOCKS_PER_SEC)*tAccelaration >1)
	{
		lastSpawn = std::clock();
		addNewCar();
		cCarAmount++;
	}
	if (!paused)
	{
		deltaTime *= tAccelaration;
		CarList* iterator = cars;
		while (iterator)
		{
			sf::Vector2f cPos = iterator->element->getPos();
			Infrastructure* cInf = map->getInfrastructure((int)(cPos.x - pos.x), (int)(cPos.y - pos.y));
			if (cInf)
			{
				iterator->element->setCurrentInf(cInf);
				Infrastructure::IType test = cInf->type;
				switch (test)
				{
				case Infrastructure::IType::threeWay:
					if (iterator->element->canTurn())
					{
						iterator->element->nextTurn = cInf->getTurn(iterator->element->getPos());
						iterator->element->startTurn();
					}
					break;
				case Infrastructure::IType::fourWay:
					if (iterator->element->canTurn())
						iterator->element->startTurn();
					break;
				case Infrastructure::IType::road:
					iterator->element->setTurnedFalse();
					break;
				case Infrastructure::IType::twoWay:
					if (iterator->element->canTurn())
					{
						iterator->element->nextTurn = cInf->getTurn(iterator->element->getPos());
						iterator->element->startTurn();
					}
					break;
				}
			}
			iterator->element->update((float)deltaTime);
			iterator = iterator->pNext;
		}
	}
	lastClock = std::clock();
}

Car* Simulation::getActiveCar(sf::Vector2i checked)
{
	CarList* iterator = cars;
	while (iterator)
	{
		if (iterator->element->isInBounds(checked))
		{
			activeCar = iterator->element;
			return activeCar;
		}
		iterator = iterator->pNext;
	}
	return activeCar;
}

void Simulation::draw(sf::RenderWindow* window)
{
	window->draw(rect);
	if (map)
		map->draw(window);
	CarList* iterator = cars;
	while (iterator)
	{
		iterator->element->draw(window);
		iterator = iterator->pNext;
	}
}

void Simulation::togglePause()
{
	if (paused)
		paused = false;
	else
		paused = true;
}

void Simulation::generate(int _maxCarAmount, int _roadDistance)
{
	if (cars)
	{
		CarList* iterator = cars;
		while (iterator)
		{
			CarList* nPointer = iterator->pNext;
			delete iterator->element;
			delete iterator;
			iterator = nPointer;
		}
		cars = nullptr;
	}
	delete map;
	roadDistance = _roadDistance;
	map = new Map(_roadDistance, sf::Vector2i(rect.getLocalBounds().width, rect.getLocalBounds().height), pos);
	spawnPoint = map->getInfrastructure(25, 80);
	cCarAmount = 0;
	maxCarAmount = _maxCarAmount;
}

