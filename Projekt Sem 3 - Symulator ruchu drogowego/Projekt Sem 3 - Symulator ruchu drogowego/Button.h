#pragma once
#include "TextControll.h"
class Button :
	public TextControll
{
private:
	bool clicked;
	std::time_t clickTime;
public:
	Button(sf::Vector2f _pos, std::string _text, sf::Vector2f _size);
	Button(sf::Vector2f _pos, std::string _text, sf::Vector2f _size,sf::Color _Color);
	virtual void draw(sf::RenderWindow* window);
	void click();
};

