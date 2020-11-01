#include "ObiektGraficzny.h"

ObiektGraficzny::ObiektGraficzny()
{
}

ObiektGraficzny::~ObiektGraficzny()
{
}

void ObiektGraficzny::setPos(sf::Vector2f nPos)
{
	pos = nPos;
}

sf::Vector2f ObiektGraficzny::getPos()
{
	return pos;
}
