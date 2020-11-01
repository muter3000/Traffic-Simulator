#include "Ambulance.h"

#include "Functions.h"
#include "Crossroad.h"
#include <chrono>

Ambulance::Ambulance(sf::Vector2f _pos, sf::Vector2f headingN, float _maxV, float _a)
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
	emergency = true;

	currentInf = nullptr;

	//Position and speed
	pos = _pos;
	maxVelocity = _maxV + 40;
	sAcceleration = _a;
	deceleration = 1;
	velocity = headingN * _maxV;
	acceleration = headingN * sAcceleration;
	//Texture and sprite
	static sf::Texture textureAmbulance = []() {sf::Texture t; t.loadFromFile("Sprites/Vehicles/Ambulance.png"); return t; }();
	size = sf::Vector2f(118, 224);
	sprite = new sf::Sprite(textureAmbulance, sf::IntRect(sf::Vector2i(64, 12), (sf::Vector2i)size));
	sf::FloatRect sBounds = sprite->getLocalBounds();
	sprite->setOrigin(sBounds.left + sBounds.width / 2, sBounds.top + sBounds.height / 2);
	sprite->setRotation(vAngle(headingN) + 90);
	sprite->setScale(0.1, 0.1);
	size *= 0.1f;
	xBorder = sf::Vector2f(size.x, 0);
	yBorder = sf::Vector2f(0, size.y);
	rotateVector(size, vAngle(headingN) + 90);
	rotateVector(xBorder, vAngle(headingN) + 90);
	rotateVector(yBorder, vAngle(headingN) + 90);
	borders.setPosition(pos - sf::Vector2f(size.x / 2, size.y / 2));
	borders.setSize(size);
	borders.setFillColor(sf::Color::Transparent);
	borders.setOutlineColor(sf::Color::White);
	borders.setOutlineThickness(1);

	sprite->setPosition(pos);
}
