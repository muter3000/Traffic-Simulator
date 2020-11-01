#pragma once
#include "ObiektGraficzny.h"
#include <ctime>
class TextControll :
	public ObiektGraficzny
{
protected:
	sf::Font font;
	sf::Text text;
	sf::RectangleShape box;
	bool centered = false;
public:
	TextControll();
	TextControll(sf::Vector2f _pos, std::string _text, sf::Vector2f _size);
	TextControll(sf::Vector2f _pos, std::string _text, sf::Vector2f _size,sf::Color _color);
	void setText(sf::String nText);
	void setTextSize(int nSize);
	virtual void draw(sf::RenderWindow* window);
	void centerText();
	bool isInBounds(sf::Vector2i checked) const;
};

