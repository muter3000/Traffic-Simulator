#pragma once
#include "Canvas.h"
#include "TextControll.h"
#include "InputBox.h"
#include "Button.h"
#include <string>

class StatsChange 
	:public Canvas
{

private:
	TextControll* title;
	TextControll* _nMaxVelocity;
	InputBox* nMaxVelocity;
	TextControll* _nAcceleration;
	InputBox* nAcceleration;
	Button* apply;

public:
	StatsChange(sf::Vector2f _pos, sf::Color _color, sf::Vector2f _size);
	~StatsChange();
	InputBox* getVPointer();
	InputBox* getAPointer();
	virtual void draw(sf::RenderWindow* window);
	void checkButtonClick(sf::Vector2i checked);
};

