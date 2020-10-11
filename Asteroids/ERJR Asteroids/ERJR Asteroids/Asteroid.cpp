#include "Asteroid.h"

#include <random>
#include <functional>
#include <chrono>

Asteroid::Asteroid()
{
	asteroidSetPosition();
	asteroidHealth = 30;
	asteroidAlive = false;
	inFlight = false;
	
	loadImage();
	asteroidSprite.setPosition(asteroidPosition);
	asteroidSprite.setOrigin(50, 50);

}

//complicated mess of computer science to get a position
void Asteroid::asteroidSetPosition()
{
	//okay so im going to explain this once and only once
	//random number generator
	//was helped by a pal who does computer science
	std::default_random_engine generator; //creates a random number generator
	generator.seed(static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count())); //picks a seed
	std::uniform_int_distribution<int> distribution(-100, 100); //finds a number between this range
	auto outerBoundary = std::bind(distribution, generator); //declares that as the outer boundary
	int tempRoll = outerBoundary(); //picks rand number

	float xPosition;
	float xPosTemp = outerBoundary(); //the temporary position is the boundary of asteroid
	if (xPosTemp >= 0)
	{
		xPosition = SCREEN_WIDTH + xPosTemp; //if the screen width and position of asteroid is not greater off screen, do it again
	}
	else
	{
		xPosition = xPosTemp; //other wise the temporary position is good and we can declare this as the position
	}

	//we repeat this step for the y coord

	float yPosition;
	float yPosTemp = outerBoundary();
	if (yPosTemp >= 0) //if the y pos is on screen
	{
		yPosition = SCREEN_HEIGHT + yPosTemp; //go again
	}
	else
	{
		yPosition = yPosTemp; //otherwise all good
	}
	asteroidPosition = { xPosition, yPosition, 0.0 }; //position is the two variables we got above
	asteroidSprite.setPosition(asteroidPosition); //set position
}

//destroys asteroid
void Asteroid::destroyAsteroid()
{
	
	asteroidAlive = false;
	inFlight = false;
	asteroidDirection = { 0,0,0 };
	asteroidSetPosition();

}

void Asteroid::resetAsteroid()
{
	asteroidHealth = 30;
	asteroidAlive = true;
	asteroidSetPosition();
}

bool Asteroid::getAlive()
{
	return asteroidAlive;
}

void Asteroid::setAlive(bool t_alive)
{
	asteroidAlive = t_alive;
}

void Asteroid::spawnAsteroid(sf::Vector2f t_position)
{
	asteroidSprite.setPosition(t_position);
	asteroidDirection = createRandomDirection();
	inFlight = true;
	asteroidAlive = true;
}

bool Asteroid::getFlightStatus()
{
	return inFlight;
}

sf::Vector2f Asteroid::currentPosition()
{
	return asteroidSprite.getPosition();
}

void Asteroid::loadImage()
{
	if (!asteroidTexture.loadFromFile("ASSETS/IMAGES/asteroid.png")) //load
	{
		std::cout << "error with asteroid sprite file"; //error
	}
	asteroidSprite.setTexture(asteroidTexture); //set texture to sprite

}

sf::Sprite Asteroid::getBody()
{
	return asteroidSprite;
}

void Asteroid::asteroidMovement()
{
	//create a random direction
	if (inFlight == false)
	{
		asteroidDirection = createRandomDirection();
		inFlight = true;
	}
	//move position along vector
	asteroidSprite.move(asteroidDirection);
	asteroidPosition = asteroidSprite.getPosition(); //update position

	//if off-screen -> another random position
	if (asteroidPosition.x > SCREEN_WIDTH + 200)
	{
		asteroidSetPosition();
		asteroidAlive = true;
	}
	else if (asteroidPosition.x < -200 )
	{
		asteroidSetPosition();
		asteroidAlive = true;
	}
	else if (asteroidPosition.y > SCREEN_HEIGHT + 200 )
	{
		asteroidSetPosition();
		asteroidAlive = true;
	}
	else if (asteroidPosition.y < -200)
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
MyVector3 Asteroid::createRandomDirection()
{
	//a generator the same as the one in the asteroid position
	//see (asteroid.cpp) for more info
	std::default_random_engine generator;
	generator.seed(static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
	std::uniform_int_distribution<int> distribution(-3, 3); //instead picks a small number for speed, not used as location
	auto speed = std::bind(distribution, generator);
	int tempRoll = speed(); //temporary roll (speed) is equal to 

	//this bit below says that if the speed is 0, go again and find another
	float xSpeed = speed(); //it's speed xward
	while (xSpeed == 0.0)
	{
		xSpeed = speed();
	}
	float ySpeed = speed(); //its speed yward
	while (ySpeed == 0.0)
	{
		ySpeed = speed();
	}

	//then the asteroid gets this speed
	asteroidDirection = { xSpeed, ySpeed, 0.0 };

	asteroidAlive = true; //asteroid is alive
	return asteroidDirection;
}
