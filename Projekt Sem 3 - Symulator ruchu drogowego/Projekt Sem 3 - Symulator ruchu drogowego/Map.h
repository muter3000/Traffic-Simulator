#pragma once
#include "Infrastructure.h"
#include "ThreeWayCrossroad.h"
#include "TwoWayCrossroad.h"
#include "FourWayCrossroad.h"
#include "Road.h"
class Map
	:public ObiektGraficzny
{
private:
	int x, y;
	int rDistance;
	Infrastructure*** roadMap;
public:
	Map(int RDistance,sf::Vector2i simSize,sf::Vector2f pos);
	~Map();
	virtual void draw(sf::RenderWindow* window);
	Infrastructure::IType checkType(int xPos, int yPos);
	Infrastructure* getInfrastructure(int xPos, int yPos);
};

