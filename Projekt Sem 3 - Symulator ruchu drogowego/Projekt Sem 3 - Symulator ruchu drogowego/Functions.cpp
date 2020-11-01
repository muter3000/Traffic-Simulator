#include "Functions.h"
#include <iostream>
#define PI 3.141592653589793238462643383279502884197

void normalize(sf::Vector2f& v)
{
	v = v/vMagnitude(v);
}

float vMagnitude(sf::Vector2f v)
{
	if (v == sf::Vector2f(0, 0))
		return 0;
	return sqrt(pow(v.x,2)+pow(v.y,2));
}
float vAngle(sf::Vector2f v)
{
	if (v.x == 0)
		return 90*v.y/abs(v.y);
	return atan(v.y/v.x)*180/PI;
}
void setMagnitude(sf::Vector2f& v, float newMagnitude)
{
	if (newMagnitude == 0)
	{
		v = sf::Vector2f(0, 0);
	}
	else
	{
		normalize(v);
		v *= newMagnitude;
	}
}
void rotateVector(sf::Vector2f &v, float angle)
{
	angle /= 180;
	angle *= PI;
	v = sf::Vector2f(v.x*cos(angle)-v.y*sin(angle), v.x * sin(angle) + v.y * cos(angle));
}

float scalarProduct(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return v1.x*v2.x+v1.y*v2.y;
}

float determinant(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return v1.x*v2.y-v1.x*v2.y;
}
float vDistance(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return std::sqrt(std::pow((v1.x - v2.x), 2) + std::pow((v1.y - v2.y), 2));
}
