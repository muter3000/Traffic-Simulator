#include "Road.h"

Road::Road(sf::Vector2f _pos, Orientation _orientation, int length)
{
	IsCrossroad = false;
	type = Infrastructure::IType::road;
	static sf::Texture texture;
	roadWidth = 18;
	pos = _pos;
	orientation = _orientation;
	length *= 10;
	static bool initialized;
	if (!initialized) {
		initialized = true;
		texture.loadFromFile("Sprites/Roads/road.png");
	}

	sprite = new sf::Sprite(texture, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(706, length)));
	sprite->setTexture(texture);
	sprite->setScale(0.1,0.1);
	sprite->rotate(90 * static_cast<int>(orientation));
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


void Road::draw(sf::RenderWindow* window)
{
	window->draw(*sprite);
}

Car::Turn Road::getTurn(sf::Vector2f cPos)
{
	return Car::Turn::straight;
}
