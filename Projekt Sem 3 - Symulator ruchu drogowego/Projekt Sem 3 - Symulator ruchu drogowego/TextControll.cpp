#include "TextControll.h"
#include <iostream>

TextControll::TextControll()
{
}

TextControll::TextControll(sf::Vector2f _pos, std::string _text, sf::Vector2f _size)
{
	font.loadFromFile("arial.ttf");
	pos = _pos;
	text.setFont(font);
	text.setString(_text);
	text.setCharacterSize(11);
	text.setFillColor(sf::Color::Black);
	text.setOrigin(0, text.getLocalBounds().top + text.getLocalBounds().height / 2);
	box.setFillColor(sf::Color(150,150,150));
	box.setSize(_size);
}

TextControll::TextControll(sf::Vector2f _pos, std::string _text, sf::Vector2f _size, sf::Color _color)
{
	font.loadFromFile("arial.ttf");
	pos = _pos;
	text.setFont(font);
	text.setString(_text);
	text.setCharacterSize(11);
	text.setFillColor(sf::Color::Black);
	text.setOrigin(0, text.getLocalBounds().top + text.getLocalBounds().height / 2);
	box.setFillColor(_color);
	box.setSize(_size);
}

void TextControll::setText(sf::String nText)
{
	text.setString(nText);
}

void TextControll::setTextSize(int nSize)
{
	text.setCharacterSize(nSize);
}

void TextControll::draw(sf::RenderWindow* window)
{
	box.setPosition(pos);
	if(!centered)
		text.setPosition(pos + sf::Vector2f(2, box.getLocalBounds().height/2));
	else
		text.setPosition(pos + sf::Vector2f(box.getLocalBounds().width/2, box.getLocalBounds().height / 2));
	window->draw(box);
	window->draw(text);
}

void TextControll::centerText()
{
	sf::FloatRect lBounds = text.getLocalBounds();
	text.setOrigin(lBounds.left + lBounds.width / 2, lBounds.top + lBounds.height / 2);
	centered = true;
}

bool TextControll::isInBounds(sf::Vector2i checked) const
{
	checked -= (sf::Vector2i)box.getPosition();
	return(checked.x > 0&& checked.y > 0&& checked.x <box.getLocalBounds().width && checked.y < box.getLocalBounds().height);
}

