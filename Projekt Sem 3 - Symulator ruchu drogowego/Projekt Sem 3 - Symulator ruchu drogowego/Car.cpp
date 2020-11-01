#include "Car.h"
#include "Functions.h"
#include "Crossroad.h"
#include <chrono>
void Car::turn(float deltaTime)
{
	float radius=0;
	std::default_random_engine generator;
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> dis(0, 2);
	switch (nextTurn)
	{
	case Car::Turn::left:
		radius = -0.8;
		break;
	case Car::Turn::straight:
		angleTurned = 90;
		nextTurn = static_cast <Turn>(dis(generator));
		turned = true;
		break;
	case Car::Turn::right:
		radius = 0.43;
		break;
	}
	if (turning)
	{
		if (angleTurned < 90)
		{
			angleTurned += abs(vMagnitude(velocity) / radius * deltaTime);
			rotate(vMagnitude(velocity) / radius * deltaTime);
		}
		else
		{
			float angle;
			if (std::abs(std::fmod(vAngle(velocity), 90)) > 45)
			{
				if (std::fmod(vAngle(velocity), 90) > 0)
				{
					angle = -(std::abs(std::fmod(vAngle(velocity), 90)) - 90);
				}
				else
				{
					angle = std::abs(std::fmod(vAngle(velocity), 90)) - 90;
				}
			}
			else
			{
				if (std::fmod(vAngle(velocity), 90) > 0)
				{
					angle = -(std::abs(std::fmod(vAngle(velocity), 90)));
				}
				else
				{
					angle = std::abs(std::fmod(vAngle(velocity), 90));
				}
			}
			rotate(angle);
			angleTurned = 0;
			turning = false;
			turned = true;
			nextTurn = static_cast <Turn>(dis(generator));
		}
	}
}

Car::operator float() const
{
	return vMagnitude(velocity);
}


Car::Car(sf::Vector2f _pos, sf::Vector2f headingN = sf::Vector2f(0,1), float _maxV =10, float _a=1)
{
	//Turning variables
	static std::default_random_engine generator = []() {std::default_random_engine generator; generator.seed(std::chrono::system_clock::now().time_since_epoch().count()); return generator; }();
	static std::uniform_int_distribution<int> dis(0, 2);

	stopped = false;
	prevInf = nullptr;
	nextTurn = static_cast <Turn>(dis(generator));
	angleTurned = 0;
	turning = false;
	turned = true;
	emergency = false;

	currentInf = nullptr;

	//Position and speed
	pos = _pos;
	maxVelocity = _maxV;
	sAcceleration = _a;
	deceleration = 1;
	velocity = headingN*_maxV;
	acceleration = headingN * sAcceleration;
	//Texture and sprite
	static sf::Texture textureAudi = [](){sf::Texture t; t.loadFromFile("Sprites/Vehicles/Audi.png"); return t; }();
	static sf::Texture textureTaxi = []() {sf::Texture t; t.loadFromFile("Sprites/Vehicles/Taxi.png"); return t; }();
	static sf::Texture textureOrangeCar = []() {sf::Texture t; t.loadFromFile("Sprites/Vehicles/Car.png"); return t; }();
	static sf::Texture textureBViper = []() {sf::Texture t; t.loadFromFile("Sprites/Vehicles/Black_viper.png"); return t; }();
	static sf::Texture textureJeep = []() {sf::Texture t; t.loadFromFile("Sprites/Vehicles/Mini_truck.png"); return t; }();
	static sf::Texture textureVan = []() {sf::Texture t; t.loadFromFile("Sprites/Vehicles/Mini_van.png"); return t; }();
	static sf::Texture textureTruck = []() {sf::Texture t; t.loadFromFile("Sprites/Vehicles/Truck.png"); return t; }();
	size = sf::Vector2f(118, 224);
	static std::uniform_int_distribution<int> disT(0, 6);
	switch (disT(generator))
	{
	case 0:
		sprite = new sf::Sprite(textureTaxi, sf::IntRect(sf::Vector2i(64, 12), (sf::Vector2i)size));
		break;
	case 1:
		sprite = new sf::Sprite(textureAudi, sf::IntRect(sf::Vector2i(64, 12), (sf::Vector2i)size));
		break;
	case 2:
		sprite = new sf::Sprite(textureOrangeCar, sf::IntRect(sf::Vector2i(64, 12), (sf::Vector2i)size));
		break;
	case 3:
		sprite = new sf::Sprite(textureJeep, sf::IntRect(sf::Vector2i(64, 12), (sf::Vector2i)size));
		break;
	case 4:
		sprite = new sf::Sprite(textureVan, sf::IntRect(sf::Vector2i(64, 12), (sf::Vector2i)size));
		break;
	case 5:
		sprite = new sf::Sprite(textureTruck, sf::IntRect(sf::Vector2i(64, 12), (sf::Vector2i)size));
		break;
	default:
		sprite = new sf::Sprite(textureBViper, sf::IntRect(sf::Vector2i(64, 12), (sf::Vector2i)size));
		break;
	}
	sf::FloatRect sBounds = sprite->getLocalBounds();
	sprite->setOrigin(sBounds.left + sBounds.width / 2, sBounds.top + sBounds.height / 2);
	sprite->setRotation(vAngle(headingN)+90);
	sprite->setScale(0.1, 0.1);
	size *= 0.1f;
	xBorder = sf::Vector2f(size.x, 0);
	yBorder = sf::Vector2f(0, size.y);
	rotateVector(size, vAngle(headingN) + 90);
	rotateVector(xBorder, vAngle(headingN) + 90);
	rotateVector(yBorder, vAngle(headingN) + 90);
	borders.setPosition(pos- sf::Vector2f(size.x / 2, size.y / 2));
	borders.setSize(size);
	borders.setFillColor(sf::Color::Transparent);
	borders.setOutlineColor(sf::Color::White);
	borders.setOutlineThickness(1);

	sprite->setPosition(pos);
}

Car::Car()
{
}

Car::~Car()
{
	delete sprite;
}

//Update function
void Car::update(float deltaTime)
{
	if (!stopped)
	{
		if (turning&& vMagnitude(velocity) > 3)
		{
			turn(deltaTime);
		}
		//if(!((Infrastructure*)currentInf)->isCrossroad())
		checkSlow();
		if(vMagnitude(velocity)>3)
		pos += (velocity * deltaTime + acceleration * ((pow(deltaTime, 2)) / 2));
		if (vMagnitude(velocity) < maxVelocity)
			velocity += (acceleration * deltaTime);
		if (vMagnitude(velocity) >= maxVelocity)
			setMagnitude(velocity, maxVelocity);

	}
	sprite->setPosition(pos);
	borders.setPosition(pos-sf::Vector2f(size.x / 2, size.y / 2));
}

void Car::draw(sf::RenderWindow* window)
{
	window->draw(*sprite);
}

void Car::rotate(float angle)
{
	rotateVector(velocity, angle);
	rotateVector(acceleration, angle);
	rotateVector(size, angle);
	rotateVector(xBorder, angle);
	rotateVector(yBorder, angle);
	setMagnitude(acceleration, sAcceleration);
	borders.rotate(angle);
	sprite->rotate(angle);
}

void Car::slow(float targetSpeed)
{
	setMagnitude(velocity, targetSpeed);
}

void Car::stop()
{
	stopped = true;
	setMagnitude(velocity, 0.0000000001);
}

void Car::resume()
{
	stopped = false;
}

sf::Vector2f Car::getVelocity()
{
	return velocity;
}

sf::Vector2f Car::getAccelaration()
{
	return acceleration;
}

void Car::setCurrentInf(void* nInf)
{
	if (nInf&&nInf!=currentInf) 
	{
		if (((Infrastructure*)nInf)->isCrossroad())
		{
			if (((Crossroad*)nInf)->isBusy()&&!emergency)
			{
					((Crossroad*)nInf)->addToQueue(this);
					stop();
			}
			else
			{
					((Crossroad*)nInf)->incrementBusyState(1);
			}
		}
		else
		{
			if (currentInf&&((Infrastructure*)currentInf)->isCrossroad())
			{
				((Crossroad*)currentInf)->incrementBusyState(-1);
				if(!((Crossroad*)currentInf)->isBusy())
					((Crossroad*)currentInf)->resumeCar();
			}
		}
		if (prevInf)
			((Infrastructure*)prevInf)->carsHere.remove_if([this](Car* c) {return c == this; });
		prevInf = currentInf;
		currentInf = nInf;
		if (currentInf)
			((Infrastructure*)currentInf)->carsHere.push_back(this);
	}
}

void* Car::getCurrentInf()
{
	return currentInf;
}

void Car::setMaxVelocity(float newMaxVelocity)
{
	maxVelocity = newMaxVelocity;
}

void Car::setAccelaration(float newAcceleration)
{
	sAcceleration = newAcceleration;
	normalize(acceleration);
	acceleration *= sAcceleration;
}

bool Car::isInBounds(sf::Vector2i checked)
{
	sf::Vector2f aPoint = borders.getPosition();
	sf::Vector2f am = (sf::Vector2f)checked - aPoint;
	return (0<scalarProduct(am,xBorder)&& scalarProduct(am, xBorder) < scalarProduct(xBorder, xBorder)&& 0 < scalarProduct(am, xBorder) && scalarProduct(am, xBorder) < scalarProduct(xBorder, xBorder));
}

float Car::getMaxVelocity()
{
	return maxVelocity;
}

void Car::startTurn()
{
	turning = true;
	turned = false;
}

void Car::setTurnedFalse()
{
	turned = false;
}

bool Car::canTurn()
{
	return !(turned||turning);
}

void Car::checkSlow()
{
	if(currentInf)
	for (Car* c : ((Infrastructure*)currentInf)->carsHere)
	{
		if (c)
		{
			sf::Vector2f nV = velocity;
			sf::Vector2f nC2 = c->getVelocity();
			sf::Vector2f posD = c->getPos()-pos;
			normalize(nC2);
			normalize(posD);
			normalize(nV);

			if (vDistance(c->getPos(),pos)<25 && *c<*this && scalarProduct(posD,nV)>0.85)
			{
				slow((float)(*c-1));
			}
		}
	}
}

bool operator<(const Car& c1, const Car& c2)
{
	return (float)c1<(float)c2;
}
