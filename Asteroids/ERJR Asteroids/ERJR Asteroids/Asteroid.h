//asteroid class declaration header file
#pragma once

//include shtuff
#include "SFML/Graphics.hpp" 
#include "Globals.h"
#include <iostream>
#include "MyVector3.h"
#include "Particles.h"

//asteroid class
class Asteroid
{
	sf::Texture asteroidTexture; //asteroid textures
	sf::Sprite asteroidSprite; //the asteroid body / sprite that appears on the screen
	MyVector3 asteroidDirection; //this will be randomly generated
	MyVector3 asteroidPosition; //the position the asteroid is on the screen
	int asteroidHealth; //the health of the asteroid
	bool asteroidAlive;
	bool inFlight;

public:
	Asteroid();
	ParticleSystemAsteroids explosion;
	void loadImage();
	sf::Sprite getBody();
	void asteroidMovement();
	MyVector3 createRandomDirection();
	void asteroidSetPosition();
	void destroyAsteroid();
	void resetAsteroid();
	bool getAlive();
	void setAlive(bool t_alive);
	void spawnAsteroid(sf::Vector2f t_position);
	bool getFlightStatus();
	sf::Vector2f currentPosition();
};