#include "Infrastructure.h"

Infrastructure::Infrastructure():type(Infrastructure::IType::road)
{
	orientation = Orientation::North;
	roadWidth = 10;
	sprite = nullptr;
}

Infrastructure::~Infrastructure()
{
	delete sprite;
}

bool Infrastructure::isCrossroad()
{
	return IsCrossroad;
}
