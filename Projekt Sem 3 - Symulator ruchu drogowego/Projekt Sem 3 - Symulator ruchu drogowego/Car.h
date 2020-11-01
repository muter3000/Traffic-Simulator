#pragma once
#include "ObiektGraficzny.h"
#include <random>
class Car :
	public ObiektGraficzny
{
protected:
	float angleTurned;
	bool turning;
	bool turned;
	bool emergency;

	sf::Sprite* sprite;
	sf::Vector2f size;
	sf::Vector2f xBorder, yBorder;
	sf::RectangleShape borders;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	void* currentInf;
	void* prevInf;

	float maxVelocity;
	float sAcceleration;
	float deceleration;
	void turn(float deltaTime);
public:
	bool stopped;
	operator float() const;
	friend bool operator <(const Car& c1,const Car& c2);
	enum class Turn { left, straight, right };
	Turn nextTurn;
	Car(sf::Vector2f _pos, sf::Vector2f headingN, float _maxV, float _a);
	Car();
	~Car();
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);
	void rotate(float angle);
	void slow(float targetSpeed);
	void stop();
	void resume();

	sf::Vector2f getVelocity();
	sf::Vector2f getAccelaration();
	void* getCurrentInf();
	float getMaxVelocity();

	void setCurrentInf(void* nInf);
	void setMaxVelocity(float newMaxVelocity);
	void setAccelaration(float newAcceleration);

	bool isInBounds(sf::Vector2i checked);

	void startTurn();
	void setTurnedFalse();
	bool canTurn();

	void checkSlow();
};

