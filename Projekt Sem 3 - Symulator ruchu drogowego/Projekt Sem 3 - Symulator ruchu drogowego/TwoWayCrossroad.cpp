#include "TwoWayCrossroad.h"

TwoWayCrossroad::TwoWayCrossroad(sf::Vector2f _pos, Orientation _orientation)
{
	queue[0] = nullptr;
	queue[1] = nullptr;
	queue[2] = nullptr;
	queue[3] = nullptr;
	IsCrossroad = false;
	busy = false;
	type = Infrastructure::IType::twoWay;
	static sf::Texture texture;
	roadWidth = 18;
	pos = _pos;
	orientation = _orientation;
	static bool initialized;
	if (!initialized) {
		initialized = true;
		texture.loadFromFile("Sprites/Roads/corner1.png");
	}
	sprite = new sf::Sprite(texture, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(706, 706)));
	sprite->setTexture(texture);
	sprite->setScale(0.1f, 0.1f);
	sprite->rotate(90.0f * static_cast<int>(orientation));
	switch (orientation)
	{
	case Infrastructure::Orientation::North:
		break;
	case Infrastructure::Orientation::East:
		sprite->setOrigin(0, sprite->getLocalBounds().height);
		break;
	case Infrastructure::Orientation::South:
		sprite->setOrigin(sprite->getLocalBounds().width, sprite->getLocalBounds().height);
		break;
	case Infrastructure::Orientation::West:
		sprite->setOrigin(sprite->getLocalBounds().width, 0);
		break;
	}
	sprite->setPosition(pos);
}

Car::Turn TwoWayCrossroad::getTurn(sf::Vector2f cPos)
{
	cPos -= pos;
	switch (orientation)
	{
	case Infrastructure::Orientation::West:
		if (cPos.x > 60)
			return Car::Turn::right;
		else
			return Car::Turn::left;
		break;
	case Infrastructure::Orientation::North:
		if (cPos.x < 60)
			return Car::Turn::right;
		else
			return Car::Turn::left;
		break;
	case Infrastructure::Orientation::East:
		if (cPos.x < 10)
			return Car::Turn::right;
		else
			return Car::Turn::left;
		break;
	case Infrastructure::Orientation::South:
		if (cPos.x < 10)
			return Car::Turn::left;
		else
			return Car::Turn::right;
		break;
	}
}

