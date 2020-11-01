#pragma once

#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string>
#include "Canvas.h"
#include "Simulation.h"
#include "Stats.h"
#include "StatsChange.h"
#include "StartSettings.h"

class Program
{
private:
	//Flags
	bool mousePressed;
	//Variables
	sf::Vector2f statsPos, statsChangePos,startSettingsPos,simPos;
	sf::Vector2f statsSize, statsChangeSize, startSettingsSize, simSize;

	std::vector<Canvas*> canvasVector;

	Stats* stats;
	StatsChange* statsChange;
	StartSettings* startSettings;
	Simulation* sim;

	sf::Image* icon;

	InputBox*  activeBox;
	Car*	   activeCar;
	//Window
	sf::VideoMode vMode;
	sf::Event event;
	sf::RenderWindow* window;
	std::string wTitle;
	void initWindow();
	void initVariables();
	void pollEvents();
public:
	//Constructors & Destructors
	Program(std::string Title, int _wWidth, int _wHeight);
	~Program();
	//Funtions
	void update();
	void render();
	//Accesors
	const bool isRunning() const;
};

