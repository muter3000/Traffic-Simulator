#pragma once
#include "Canvas.h"
#include "TextControll.h"
#include "InputBox.h"
#include "Button.h"
class StartSettings :
	public Canvas
{
private:
	TextControll*  title;
	TextControll*  cCarCount;
	TextControll*  cRDistance;
	InputBox* carCount;
	InputBox* rDistance;
	Button*	  generate;
public:
	StartSettings(sf::Vector2f _pos, sf::Color _color, sf::Vector2f _size);
	~StartSettings();
	virtual void draw(sf::RenderWindow* window);
	bool checkButtonClick(sf::Vector2i checked);
	int getCarCount() const;
	int getRDistance() const;
};


