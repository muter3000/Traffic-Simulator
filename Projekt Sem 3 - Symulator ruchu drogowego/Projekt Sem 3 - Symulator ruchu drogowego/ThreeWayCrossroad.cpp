#include "ThreeWayCrossroad.h"
#include <chrono>
ThreeWayCrossroad::ThreeWayCrossroad(sf::Vector2f _pos, Orientation _orientation)
{
	queue[0] = nullptr;
	queue[1] = nullptr;
	queue[2] = nullptr;
	queue[3] = nullptr;
	IsCrossroad = true;
	busy = false;
	type = Infrastructure::IType::threeWay;
	static sf::Texture texture;
	roadWidth = 18;
	pos = _pos;
	orientation = _orientation;
	static bool initialized;
	if (!initialized) {
		initialized = true;
		texture.loadFromFile("Sprites/Roads/junctionT1.png");
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

Car::Turn ThreeWayCrossroad::getTurn(sf::Vector2f cPos)
{
	cPos -= pos;
	static std::default_random_engine generator = []() {std::default_random_engine generator; generator.seed(std::chrono::system_clock::now().time_since_epoch().count()); return generator; }();
	static std::uniform_int_distribution<int> dis(0, 1);
	int choice = dis(generator);
	switch (orientation)
	{
	case Infrastructure::Orientation::North:
		if(cPos.x>57)
			switch (choice)
			{
			case 0:
				return Car::Turn::left;
				break;
			default:
				return Car::Turn::straight;
				break;
			}
		else if(cPos.x<15)
			switch (choice)
			{
			case 0:
				return Car::Turn::right;
				break;
			default:
				return Car::Turn::straight;
				break;
			}
		else
			switch (choice)
			{
			case 0:
				return Car::Turn::right;
				break;
			default:
				return Car::Turn::left;
				break;
			}
		break;
	case Infrastructure::Orientation::East:
		if (cPos.y > 57)
			switch (choice)
			{
			case 0:
				return Car::Turn::left;
				break;
			default:
				return Car::Turn::straight;
				break;
			}
		else if (cPos.y < 15)
			switch (choice)
			{
			case 0:
				return Car::Turn::right;
				break;
			default:
				return Car::Turn::straight;
				break;
			}
		else
			switch (choice)
			{
			case 0:
				return Car::Turn::right;
				break;
			default:
				return Car::Turn::left;
				break;
			}
		break;
	case Infrastructure::Orientation::South:
		if (cPos.x > 57)
			switch (choice)
			{
			case 0:
				return Car::Turn::right;
				break;
			default:
				return Car::Turn::straight;
				break;
			}
		else if (cPos.x < 15)
			switch (choice)
			{
			case 0:
				return Car::Turn::left;
				break;
			default:
				return Car::Turn::straight;
				break;
			}
		else
			switch (choice)
			{
			case 0:
				return Car::Turn::right;
				break;
			default:
				return Car::Turn::left;
				break;
			}
		break;
	default:
		if (cPos.y > 57)
			switch (choice)
			{
			case 0:
				return Car::Turn::right;
				break;
			default:
				return Car::Turn::straight;
				break;
			}
		else if (cPos.y < 15)
			switch (choice)
			{
			case 0:
				return Car::Turn::left;
				break;
			default:
				return Car::Turn::straight;
				break;
			}
		else
			switch (choice)
			{
			case 0:
				return Car::Turn::right;
				break;
			default:
				return Car::Turn::left;
				break;
			}
		break;
	}
}

