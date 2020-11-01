#pragma once
#include "TextControll.h"
class InputBox :
	public TextControll
{
private:
	bool active;
	std::clock_t lastLetter;
public:
	void inputText(sf::Event event);
	void toggleActive();
	bool getActive();
	InputBox(sf::Vector2f _pos, std::string _text, sf::Vector2f _size);
	std::string getText();
	operator int() const;
	operator float() const;
};

