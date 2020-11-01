#include "Crossroad.h"

Crossroad::Crossroad()
{
}

Crossroad::~Crossroad()
{
}

void Crossroad::draw(sf::RenderWindow* window)
{
	window->draw(*sprite);
}

void Crossroad::incrementBusyState(int state)
{
	busy += state;
}

bool Crossroad::isBusy()
{
	return busy>0;
}

void Crossroad::addToQueue(Car* c)
{
	sf::Vector2f cV = c->getVelocity();
	normalize(cV);
	if ((int)std::round(cV.y) == 1)
	{
		queue[0] = c;
	}
	else if ((int)std::round(cV.x) == -1)
	{
		queue[1] = c;
	}
	else if ((int)std::round(cV.y) == -1)
	{
		queue[2] = c;
	}
	else
	{
		queue[3] = c;
	}
}

void Crossroad::resumeCar()
{
	for (int i = 0; i < 4; i++)
	{
		if (queue[i])
		{
			if (i >= 2)
			{
				queue[i]->resume();
				queue[i] = nullptr;
			}
			else if (i == 1)
			{
				if (queue[3])
				{
					if (queue[1]->nextTurn == Car::Turn::left)
					{
						queue[3]->resume();
						queue[3] = nullptr;
					}
					else
					{
						queue[1]->resume();
						queue[1] = nullptr;
					}
				}
				else
				{
					queue[1]->resume();
					queue[1] = nullptr;
				}
			}
			else
			{
				if (!queue[3])
				{
					if (queue[2])
					{
						if (queue[0]->nextTurn == Car::Turn::left)
						{
							queue[2]->resume();
							queue[2] = nullptr;
						}
						else
						{
							queue[0]->resume();
							queue[0] = nullptr;
						}
					}
					else
					{
						queue[0]->resume();
						queue[0] = nullptr;
					}
				}
				else
				{
					if (queue[2] && queue[1])
					{
						queue[3]->resume();
						queue[3] = nullptr;
					}
					else
					{
						continue;
					}				
				}
			}
			busy += 1;
			break;
		}
	}
}
