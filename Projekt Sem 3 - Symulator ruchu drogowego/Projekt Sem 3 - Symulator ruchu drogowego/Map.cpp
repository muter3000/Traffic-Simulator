#include "Map.h"

Map::Map(int RDistance, sf::Vector2i simSize,sf::Vector2f pos)
{
	rDistance = RDistance;
	if (RDistance+150 > simSize.y)
		RDistance = simSize.y-150;
	y = 2*((simSize.y-76) / (70 + RDistance))+1;
	x = 2*((simSize.x-76) / (70 + RDistance))+1;
	roadMap = new Infrastructure ** [y];
	for (int i = 0; i < y; i++)
	{
		roadMap[i] = new Infrastructure*[x];
	}
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
				roadMap[i][j]=nullptr;
		}
	}
	roadMap[0][0] = new TwoWayCrossroad(pos, Infrastructure::Orientation::North);
	roadMap[0][x-1] = new TwoWayCrossroad(pos+sf::Vector2f((x - 1) / 2 * (70 + RDistance),0), Infrastructure::Orientation::East);
	roadMap[y-1][0] = new TwoWayCrossroad(pos + sf::Vector2f(0, (y - 1) / 2 * (70 + RDistance)), Infrastructure::Orientation::West);
	roadMap[y-1][x - 1] = new TwoWayCrossroad(pos + sf::Vector2f((x - 1) / 2 * (70 + RDistance), (y - 1)/2 * (70 + RDistance)),  Infrastructure::Orientation::South);
	for (int j = 2; j < x-1; j += 2)
	{
		roadMap[0][j] = new ThreeWayCrossroad(pos + sf::Vector2f(j/2 * (70 + RDistance),0), Infrastructure::Orientation::North);
		roadMap[y-1][j] = new ThreeWayCrossroad(pos + sf::Vector2f(j/2 * (70 + RDistance),(y - 1) / 2 * (70 + RDistance)), Infrastructure::Orientation::South);
	}
	for (int i = 2; i < y - 1; i += 2)
	{
		roadMap[i][0] = new ThreeWayCrossroad(pos + sf::Vector2f(0, i / 2 * (70 + RDistance)), Infrastructure::Orientation::West);
		roadMap[i][x-1] = new ThreeWayCrossroad(pos + sf::Vector2f( (x - 1) / 2 * (70 + RDistance),i / 2 * (70 + RDistance)), Infrastructure::Orientation::East);
	}
	for (int i = 2; i < y - 2; i+=2)
	{
		for (int j = 2; j < x - 2; j+=2)
		{
			roadMap[i][j] = new FourWayCrossroad(pos + sf::Vector2f(j / 2 * (70 + RDistance), i / 2 * (70 + RDistance)));
		}
	}
	for (int i = 0; i < y; i += 2)
	{
		for (int j = 1; j < x - 1; j += 2)
		{
			roadMap[i][j] = new Road(pos + sf::Vector2f((j / 2) * (70 + RDistance)+70, (i / 2) * (70 + RDistance)),Infrastructure::Orientation::East,RDistance);
		}
	}
	for (int i = 1; i < y-1; i += 2)
	{
		for (int j = 0; j < x; j += 2)
		{
			roadMap[i][j] = new Road(pos + sf::Vector2f((j / 2) * (70 + RDistance), (i / 2) * (70 + RDistance)+70), Infrastructure::Orientation::North, RDistance);
		}
	}

}

Map::~Map()
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			delete roadMap[i][j];
		}
		delete[] roadMap[i];
	}
	delete[] roadMap;
}

void Map::draw(sf::RenderWindow* window)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			
			if (roadMap[i][j])
			{
				roadMap[i][j]->draw(window);
			}
		}
	}
}

Infrastructure::IType Map::checkType(int xPos, int yPos)
{
	int a = -1;
	int b = -1;
	for (bool i =true; xPos > 0; i = !i)
	{
		if (i)
		{
			xPos -= 70;
			a++;
		}
		else
		{
			xPos -= rDistance;
			a++;
		}
	}
	for (bool i = true; yPos > 0; i = !i)
	{
		if (i)
		{
			yPos -= 70;
			b++;
		}
		else
		{
			yPos -= rDistance;
			b++;
		}
	}
	if(x>a&&a>=0&&y>b&&b>=0&&roadMap[b][a])
		return roadMap[b][a]->type;
	return Infrastructure::IType::road;
}

Infrastructure* Map::getInfrastructure(int xPos, int yPos)
{
	int a = -1;
	int b = -1;
	for (bool i = true; xPos > 0; i = !i)
	{
		if (i)
		{
			xPos -= 70;
			a++;
		}
		else
		{
			xPos -= rDistance;
			a++;
		}
	}
	for (bool i = true; yPos > 0; i = !i)
	{
		if (i)
		{
			yPos -= 70;
			b++;
		}
		else
		{
			yPos -= rDistance;
			b++;
		}
	}
	if (x > a&& a >= 0 && y > b&& b >= 0 && roadMap[b][a])
		return roadMap[b][a];
	return nullptr;
}
