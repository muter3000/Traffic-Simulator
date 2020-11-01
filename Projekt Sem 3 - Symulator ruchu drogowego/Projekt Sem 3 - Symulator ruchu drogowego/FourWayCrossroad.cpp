#include "FourWayCrossroad.h"

FourWayCrossroad::FourWayCrossroad(sf::Vector2f _pos)
{
	queue[0] = nullptr;
	queue[1] = nullptr;
	queue[2] = nullptr;
	queue[3] = nullptr;
	IsCrossroad = true;
	busy = false;
	type = Infrastructure::IType::fourWay;
	static sf::Texture texture;
	roadWidth = 18;
	pos = _pos;
	static bool initialized;
	if (!initialized) {
		initialized = true;
		texture.loadFromFile("Sprites/Roads/junctionC2.png");
	}
	sprite = new sf::Sprite(texture, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(706, 706)));
	sprite->setTexture(texture);
	sprite->setScale(0.1f, 0.1f);
	sprite->setPosition(pos);
}

Car::Turn FourWayCrossroad::getTurn(sf::Vector2f pos)
{
	return Car::Turn::straight;
}
