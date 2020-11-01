#include "Button.h"

Button::Button(sf::Vector2f _pos, std::string _text, sf::Vector2f _size)
{
	font.loadFromFile("arial.ttf");
	pos = _pos;
	text.setFont(font);
	text.setString(_text);
	text.setCharacterSize(14);
	text.setFillColor(sf::Color::Black);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	box.setFillColor(sf::Color(250, 250, 250));
	box.setSize(_size);
	clicked = false;
	clickTime = std::clock();
}

Button::Button(sf::Vector2f _pos, std::string _text, sf::Vector2f _size, sf::Color _Color)
{
	font.loadFromFile("arial.ttf");
	pos = _pos;
	text.setFont(font);
	text.setString(_text);
	text.setCharacterSize(14);
	text.setFillColor(sf::Color::Black);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	box.setFillColor(_Color);
	box.setSize(_size);
	clicked = false;
	clickTime = std::clock();
}

void Button::draw(sf::RenderWindow* window)
{
	box.setPosition(pos);
	text.setPosition(pos + sf::Vector2f(box.getSize().x/2, box.getSize().y / 2));
	if (clicked)
	{
		box.setFillColor(sf::Color(150, 150, 150));
	}
	if ((std::clock() - clickTime) / (double)CLOCKS_PER_SEC > 0.5 && clicked)
	{
		box.setFillColor(sf::Color(250, 250, 250));
		clicked = false;
	}
	window->draw(box);
	window->draw(text);
}

void Button::click()
{
	clickTime = std::clock();
	clicked = true;
}

