#include "LargeAsteroid.h"
#include <random>
#include <functional>
#include <chrono>

//large asteroid class

LargeAsteroid::LargeAsteroid()
{
	asteroidSetPosition();
	asteroidHealth = 30;
	asteroidAlive = true;
	inFlight = false;
	loadImage();
	asteroidSprite.setPosition(asteroidPosition);
	asteroidSprite.setOrigin(50, 50);

	healthBar.setSize(sf::Vector2f(asteroidHealth, 5));
	healthBar.setFillColor(sf::Color::Green);
	healthBar.setOutlineThickness(3);
	healthBar.setOutlineColor(sf::Color::White);
}

//complicated thing to get position
//explained fully in small asteroid (asteroid.cpp)
void LargeAsteroid::asteroidSetPosition()
{
	std::default_random_engine generator;
	generator.seed(static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
	std::uniform_int_distribution<int> distribution(-100, 100);
	auto outerBoundary = std::bind(distribution, generator);
	int tempRoll = outerBoundary();

	float xPosition;
	float xPosTemp = outerBoundary();
	if (xPosTemp >= 0)
	{
		xPosition = SCREEN_WIDTH + xPosTemp;
	}
	else
	{
		xPosition = xPosTemp;
	}
	float yPosition;
	float yPosTemp = outerBoundary();
	if (yPosTemp >= 0)
	{
		yPosition = SCREEN_HEIGHT + yPosTemp;
	}
	else
	{
		yPosition = yPosTemp;
	}
	asteroidPosition = { xPosition, yPosition, 0.0 };
	asteroidSprite.setPosition(asteroidPosition);
}

//destroy asteroid
void LargeAsteroid::destroyAsteroid()
{
	asteroidAlive = false;
	inFlight = false;
	asteroidDirection = { 0,0,0 };
	asteroidSprite.setPosition(2000, 2000);
}

void LargeAsteroid::resetAsteroid()
{
	asteroidAlive = true;
	asteroidSetPosition();
	inFlight = false;
}

bool LargeAsteroid::getAlive()
{
	return asteroidAlive;
}

void LargeAsteroid::setAlive(bool t_alive)
{
	
	asteroidHealth = t_alive;

}

bool LargeAsteroid::getFlightStatus()
{
	return inFlight;
}

void LargeAsteroid::loadImage()
{
	if (!asteroidTexture.loadFromFile("ASSETS/IMAGES/largeAsteroid.png")) //load
	{
		std::cout << "error with large asteroid sprite file"; //error
	}
	asteroidSprite.setTexture(asteroidTexture); //set texture to sprite
}

sf::Sprite LargeAsteroid::getBody()
{
	return asteroidSprite;
}


void LargeAsteroid::asteroidMovement()
{
	//create a random direction
	if (inFlight == false)
	{
		asteroidDirection = createRandomDirection();
		inFlight = true;
	}
	//move position along vector
	//asteroidPosition = asteroidPosition + asteroidDirection;
	asteroidSprite.move(asteroidDirection);
	asteroidPosition = asteroidSprite.getPosition();
	//if off-screen -> another random position
	if (asteroidPosition.x > SCREEN_WIDTH + 200 /*&& asteroidAlive == false*/)
	{
		asteroidSetPosition();
		asteroidAlive = true;
	}
	else if (asteroidPosition.x < -200  /*&& asteroidAlive == false*/)
	{
		asteroidSetPosition();
		asteroidAlive = true;
	}
	else if (asteroidPosition.y > SCREEN_HEIGHT + 200  /*&& asteroidAlive == false*/)
	{
		asteroidSetPosition();
		asteroidAlive = true;
	}
	else if (asteroidPosition.y < -200  /*&& asteroidAlive == false*/)
	{
		asteroidSetPosition();
		asteroidAlive = true;
	}
	else
	{
		//if nothing has happened, then do nothing
		//essentially a break;
	}
	//repeat
}

//creates a direction for the asteroid to travel
//explained in asteroid.h
//inside stuff says stuff about direction but in reality it is speed
//bad variable names
//smelly code
MyVector3 LargeAsteroid::createRandomDirection()
{
	std::default_random_engine generator;
	generator.seed(static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
	std::uniform_int_distribution<int> distribution(-3, 3);
	auto direction = std::bind(distribution, generator);
	int tempRoll = direction();

	float xDirection = direction();
	while (xDirection == 0.0)
	{
		xDirection = direction();
	}
	float yDirection = direction();
	while (yDirection == 0.0)
	{
		yDirection = direction();
	}
	asteroidDirection = { xDirection, yDirection, 0.0 };

	asteroidAlive = true;
	return asteroidDirection;
}
