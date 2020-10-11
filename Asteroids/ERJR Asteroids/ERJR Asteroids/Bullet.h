#pragma once

#include "SFML/Graphics.hpp" 
#include "Globals.h"   // include Global header file
#include <iostream>
#include "MyVector3.h"
#include "Player.h"
#include "Asteroid.h"
#include "MoneyDrop.h"
#include "LargeAsteroid.h"

class Bullet
{
public:
	sf::Texture bulletTexture;
	sf::Sprite bulletsScreen;
	sf::Vector2f bulletVelocity;
	int waitToFireCounter;
	bool readyToFire;
	bool asteroidKilled = false;
public:
	Bullet(); //default constructor
	void loadImage();
	sf::Sprite getBulletBody();
	int getWaitToFire();
	sf::Vector2f getBulletVelocity();
	bool getReadyToFire();
	void setBulletVelocity(float t_val1, float t_val2);
	void setReadyToFire(bool t_bool);
	void setWaitToFire(int t_waitCounter);
	void lowerWaitToFire(int t_lower);
	sf::Vector2f storageVector = { -500,-500 };
	void setPos(sf::Vector2f t_position);
	void bulletMovement(); //move bullet if fired
	void collisionsWithAsteroids(Asteroid t_asteroid[], LargeAsteroid t_largeAsteroid[], MoneyDrop t_moneyDrop[], PlayerShip &t_player);
	void collisionWithLargerAsteroids(LargeAsteroid t_largeAsteroid[], Asteroid t_asteroid[]);

};