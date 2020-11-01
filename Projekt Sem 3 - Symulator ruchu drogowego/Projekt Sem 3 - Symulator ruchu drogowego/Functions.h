#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

void normalize(sf::Vector2f& v);
void rotateVector(sf::Vector2f &v, float angle);
float vMagnitude(sf::Vector2f v);
float vAngle(sf::Vector2f v);
void setMagnitude(sf::Vector2f& v, float newMagnitude);
float scalarProduct(const sf::Vector2f& v1, const sf::Vector2f& v2);
float determinant(const sf::Vector2f& v1, const sf::Vector2f& v2);
float vDistance(const sf::Vector2f& v1, const sf::Vector2f& v2);