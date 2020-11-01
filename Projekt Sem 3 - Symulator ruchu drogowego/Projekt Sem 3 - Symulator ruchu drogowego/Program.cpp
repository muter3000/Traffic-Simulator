#include "Program.h"
#include "TextControll.h"
#include <thread>
#include <chrono>
//Initializers
void Program::initWindow()
{
	window = new sf::RenderWindow(vMode, wTitle, sf::Style::Titlebar);
	window->setIcon(icon->getSize().x, icon->getSize().y, icon->getPixelsPtr());
	window->setKeyRepeatEnabled(false);
}

void Program::initVariables()
{
	//Flags
	mousePressed = false;
	//Canvas pos vectors
	statsPos = sf::Vector2f(10, 10);
	statsChangePos = sf::Vector2f(10, vMode.height / 3 + 10);
	startSettingsPos = sf::Vector2f(10, vMode.height / 3 * 2 + 12);
	simPos = sf::Vector2f(vMode.width / 6 + 20, 10);
	//Canvas size vectors
	statsSize =			sf::Vector2f(vMode.width / 6, vMode.height / 3 - 23);
	statsChangeSize =	sf::Vector2f(vMode.width / 6, vMode.height / 3 - 20);
	startSettingsSize = sf::Vector2f(vMode.width / 6, vMode.height / 3 - 20);
	simSize =			sf::Vector2f(vMode.width - vMode.width / 6 - 30, vMode.height - 20);
	//Canvas init
	stats =			new Stats			(statsPos,			sf::Color(40, 40, 40), statsSize);
	canvasVector.push_back(stats);
	statsChange =   new StatsChange		(statsChangePos,	sf::Color(40, 40, 40), statsChangeSize);
	canvasVector.push_back(statsChange);
	startSettings = new StartSettings	(startSettingsPos,	sf::Color(40, 40, 40), startSettingsSize);
	canvasVector.push_back(startSettings);
	sim =			new Simulation		(simPos,			sf::Color(40, 40, 40), simSize);
	canvasVector.push_back(sim);

	icon =new sf::Image();
	icon->loadFromFile("Icon.png");

	activeCar = sim->getActiveCar(sf::Vector2i(0, 0));
}
//Private functions
void Program::pollEvents()
{
	sf::Vector2i mPos = sf::Mouse::getPosition(*window);
	window->pollEvent(event);
	switch (event.type)
	{
	case sf::Event::Closed:
		//window->close();
		break;
	case sf::Event::MouseButtonPressed:
		if (!mousePressed)
		{
			if (activeBox)
			{
				activeBox->toggleActive();
				activeBox = nullptr;
			}
				if (statsChange->isInBound(mPos))
				{
					activeBox = statsChange->getClickedInputBoxP(mPos);
					statsChange->checkButtonClick(mPos);
				}
				else if (startSettings->isInBound(mPos))
				{
					activeBox = startSettings->getClickedInputBoxP(mPos);
					if (startSettings->checkButtonClick(mPos))
					{
						activeCar = nullptr;
						sim->generate(startSettings->getCarCount(),startSettings->getRDistance());
					}
				}
				else if (sim->isInBound(mPos))
				{
					activeCar = sim->getActiveCar(mPos);
				}

			if (activeBox)
				activeBox->toggleActive();
			mousePressed = true;
		}
		break;
	case sf::Event::MouseButtonReleased:
		mousePressed = false;
		break;
	case sf::Event::KeyPressed:
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			window->close();
			break;
		case sf::Keyboard::BackSpace:
			if (activeBox) 
			{
				if (!activeBox->getActive())
					activeBox->toggleActive();
				activeBox->inputText(event);
			}
			break;
		case sf::Keyboard::P:
			if (!activeBox)
			{
				sim->togglePause();
			}
		}
		break;
	case sf::Event::TextEntered:
		if (activeBox)
		{
			if (!activeBox->getActive())
				activeBox->toggleActive();
			activeBox->inputText(event);
		}
		break;
	}
}
//Constructors & Destructors
Program::Program(std::string Title, int _wWidth, int _wHeight):wTitle(Title)
{
	vMode.width = _wWidth;
	vMode.height = _wHeight;
	initVariables();
	initWindow();
}

Program::~Program()
{
	delete window;
	delete statsChange;
	delete stats;
	delete startSettings;
	delete sim;
	delete icon;
}
//Rendering
void Program::update()
{
	pollEvents();
	sim->update();
	stats->setActiveCar(activeCar);
	statsChange->setActiveCar(activeCar);
	stats->update();
}

void Program::render()
{
	window->clear(sf::Color(55,55,55));
	//if(menu)
	if(stats)
		stats->draw(window);
	if (statsChange)
		statsChange->draw(window);
	if (startSettings)
		startSettings->draw(window);
	if (sim)
		sim->draw(window);

	window->display();
}

const bool Program::isRunning() const
{
	return window->isOpen();
}
