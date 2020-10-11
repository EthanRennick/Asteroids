//Player class
#include "Player.h"   // include Player header file


//Definition of member functions of the Player class
PlayerShip::PlayerShip() //Default constructor
{
	loadImage(); //load player image
	setPosition(); //set player position
	shipShields = 100; //starting shield
	bodySprite.setOrigin(32,32); //origin of sprite
	numOfBullets = 20;
	playerHealth = 400;
	playerShield = 400;
	playerPosition={ 500,400,0 };
	credits = 0;
	fuel = 500;
	asteroidsDestroyed = 0;
	

	playerHealthBar.setSize(sf::Vector2f(playerHealth, 5));
	playerHealthBar.setPosition(50, 750);
	playerHealthBar.setFillColor(sf::Color::Green);
	playerHealthBar.setOutlineThickness(3);
	playerHealthBar.setOutlineColor(sf::Color::White);
	
	playerShieldBar.setSize(sf::Vector2f(playerShield, 5));
	playerShieldBar.setPosition(550, 750);
	playerShieldBar.setFillColor(sf::Color::Blue);
	playerShieldBar.setOutlineThickness(3);
	playerShieldBar.setOutlineColor(sf::Color::White);

	fuelMeter.setSize(sf::Vector2f(fuel, 10));
	fuelMeter.setPosition(400, 20);
	fuelMeter.setFillColor(sf::Color::Yellow);
	fuelMeter.setOutlineThickness(2);
	fuelMeter.setOutlineColor(sf::Color::White);

}

//load images to player
void PlayerShip::loadImage()
{
	if (!spaceShipTexture.loadFromFile("ASSETS/IMAGES/XwingProper.png")) //load
	{
		std::cout << "error with x wing image file"; //error
	}
	if (!falconTexture.loadFromFile("ASSETS/IMAGES/falcon.png")) //load
	{
		std::cout << "error with falcon image file"; //error
	}
	if (!frigateTexture.loadFromFile("ASSETS/IMAGES/frigate.png")) //load
	{
		std::cout << "error with frigate image file"; //error
	}
	if (!cruiserTexture.loadFromFile("ASSETS/IMAGES/cruiser.png")) //load
	{
		std::cout << "error with cruiser image file"; //error
	}
	bodySprite.setTexture(spaceShipTexture); //set texture to sprite
}

//return player sprite 
sf::Sprite PlayerShip::getBody()
{
	return bodySprite;
}

//set player's position to bottom of screen
void PlayerShip::setPosition()
{
	bodySprite.setPosition(460,400);
}

//get the player's position on screen
MyVector3 PlayerShip::getPosition()
{
	playerPosition = bodySprite.getPosition(); //position is the position of sprite
	return playerPosition;
}

//what direction is the player looking?
sf::Vector2f PlayerShip::getPlayerLookDirection()
{
	return playerLookDirection;
}

//player collisions with asteroids
void PlayerShip::collisionWithAsteroids(Asteroid t_asteroid[])
{
	MyVector3 distance; //distance between player and asteroid
	float length; //length of distance vector
	const int ORIGIN_TO_ORIGIN_LENGTH = 64; //64 is the distance between the two sprites
	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		distance = playerPosition - t_asteroid[i].getBody().getPosition();
		length = distance.length();
		if (length < ORIGIN_TO_ORIGIN_LENGTH) //if the distance is less than 64, a collision has occured
		{
			asteroidCollision = true;
			playerParticle.Initialise(playerPosition);
			asteroidsDestroyed++;
			if (playerShield > 0)
			{
				lowerShield();
				playerShieldBar.setSize(sf::Vector2f(playerShield, 5));
				t_asteroid[i].destroyAsteroid();
				
			}
			else
			{
				lowerHealth();
				playerHealthBar.setSize(sf::Vector2f(playerHealth, 5));
				
				t_asteroid[i].destroyAsteroid();
				
			}

		}
	}
}

void PlayerShip::collisionWithLargeAsteroids(LargeAsteroid t_asteroid[], Asteroid t_asteroidSmall[])
{
	MyVector3 distance; //distance between player and large asteroid
	float length; //length of distance vector
	const int ORIGIN_TO_ORIGIN_LENGTH = 96; //96 is the distance between the two sprites
	
	for (int i = 0; i < MAX_LARGEASTEROIDS; i++) //look at all big asteroids
	{
		distance = playerPosition - t_asteroid[i].getBody().getPosition();
		length = distance.length();
		if (length < ORIGIN_TO_ORIGIN_LENGTH) //if the distance is less than 64, a collision has occured
		{
			asteroidCollision = true;
			playerParticle.Initialise(playerPosition);
			for (int j = 0; j < MAX_ASTEROIDS; j++) //look at mini steroids
			{
				if (t_asteroidSmall[j].getFlightStatus() == false && t_asteroidSmall[j + 1].getFlightStatus() == false) //if two asteroids are not in flight
				{
					//spawn them at big asteroid
					t_asteroidSmall[j].spawnAsteroid(sf::Vector2f(t_asteroid[i].getBody().getPosition()));
					t_asteroidSmall[j + 1].spawnAsteroid(sf::Vector2f(t_asteroid[i].getBody().getPosition()));
					break; //get out of loop
				}
			}

			//health 
			if (playerShield > 0)
			{
				lowerShield();
				playerShieldBar.setSize(sf::Vector2f(playerShield, 5));
				t_asteroid[i].destroyAsteroid();
			}
			else
			{
				lowerHealth();
				playerHealthBar.setSize(sf::Vector2f(playerHealth, 5));
				t_asteroid[i].destroyAsteroid();
			}
		}
	}
}

bool PlayerShip::getAsteroidCollisionStatus()
{
	return asteroidCollision;
}

void PlayerShip::changeAsteroidCollisionStatus(bool t_bool)
{
	asteroidCollision = t_bool;
}

//reset player if he dies
void PlayerShip::resetPlayer()
{
	//reset all
	numOfBullets = 5;
	credits = 0;
	playerHealth = 400;
	playerShield = 400;
	killCount = 0;

	asteroidsDestroyed = 0;
	fuel = 500;
	playerHealthBar.setSize(sf::Vector2f(playerHealth, 5));
	playerShieldBar.setSize(sf::Vector2f(playerShield, 5));
	bodySprite.setTexture(spaceShipTexture);

}

void PlayerShip::nextLevel()
{
	asteroidsDestroyed = 0;
	fuel = 500;
	fuelMeter.setSize(sf::Vector2f(fuel, 10));
	playerShield = 400;
	playerHealth = 400;
	playerHealthBar.setSize(sf::Vector2f(playerHealth, 5));
	playerShieldBar.setSize(sf::Vector2f(playerShield, 5));
}

//movement for player
void PlayerShip::movement()
{
	bodySprite.setPosition(playerPosition);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		angle -= .1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		angle += .1;
	}
	if (fuel > 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			fuel -= .3;
			fuelMeter.setSize(sf::Vector2f(fuel, 10));
			playerVelocity = playerLookDirection * 2.5f;
			playerPosition = playerPosition + playerVelocity;
			forwards = true;
			if (backwards == true)
			{
				backwards = false;
			}
		

		}

		//backwards movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			fuel -= .1;
			fuelMeter.setSize(sf::Vector2f(fuel, 10));

			playerVelocity = playerLookDirection * 1.4f;
			playerPosition = playerPosition + -playerVelocity;
			backwards = true;
			if (forwards == true)
			{
				forwards = false;
			}
			
		}
	}
	//calculate drift after movement
	calculateMomentum();

	//player look direction calculating
	playerLookDirection.x = cos(angle);
	playerLookDirection.y = sin(angle);
	bodySprite.setRotation(angle * (180 / 3.14159));

	playerOffScreenCheck();
}

//when key movement stops being a thing, calculate momentum, or drift
void PlayerShip::calculateMomentum()
{
	//calculating momentum algorithm
	if (forwards == true)
	{
		playerPosition = playerPosition + playerVelocity;
		if (playerVelocity.length() < 0.10) //stop the ship if it's movement is pain stakingly slow
		{
			playerVelocity = { 0.0f, 0.0f,0.0f }; //no movement
			forwards = false;
		}
		playerVelocity = playerVelocity * MOMENTUM; //call friction method
	}
	else if (backwards == true)
	{
		playerPosition = playerPosition - playerVelocity;
		if (playerVelocity.length() < 0.5) //stop the ship if it's movement is pain stakingly slow
		{
			playerVelocity = { 0.0f, 0.0f,0.0f }; //no movement
			backwards = false;
		}
		playerVelocity = playerVelocity * MOMENTUM; //call friction method
	}
}

//check if player has gone off screen
void PlayerShip::playerOffScreenCheck()
{
	if (playerPosition.x > SCREEN_WIDTH)
	{
		playerPosition.x = 0;
	}
	if (playerPosition.x < 0)
	{
		playerPosition.x = SCREEN_WIDTH;
	}
	if (playerPosition.y > SCREEN_HEIGHT)
	{
		playerPosition.y = 0;
	}
	if (playerPosition.y < 0)
	{
		playerPosition.y = SCREEN_HEIGHT;
	}
}

sf::RectangleShape PlayerShip::getPlayerHealth()
{
	return playerHealthBar;
}
sf::RectangleShape PlayerShip::getPlayerShield()
{
	return playerShieldBar;
}

void PlayerShip::lowerHealth()
{
	playerHealth -= 80;

}
void PlayerShip::lowerShield()
{
	playerShield -= 80;

}
int PlayerShip::currentHealth()
{
	return playerHealth;
}

int PlayerShip::getCredits()
{
	return credits;
}

sf::RectangleShape PlayerShip::getFuelMeter()
{
	return fuelMeter;
}

void PlayerShip::addCredits()
{
	credits += 20;
}

void PlayerShip::currencyColission(MoneyDrop t_moneyDrop[])
{
	MyVector3 distance; //distance between player and the currency
	float length; //length of distance vector
	const int ORIGIN_TO_ORIGIN_LENGTH = 64; //64 is the distance between the two sprites
	for (int i = 0; i < MAX_DROPS; i++)
	{
		distance = playerPosition - t_moneyDrop[i].getImage().getPosition();
		length = distance.length();
		if (length < ORIGIN_TO_ORIGIN_LENGTH) //if the distance is less than 64, a collision has occured
		{
		
			currencyCollision = true;
			if (currencyCollision == true)
			{
				if (credits < maxCredits)
				{
					t_moneyDrop[i].destroyCredits();
					credits += 10;
				}
				else
				{
					t_moneyDrop[i].destroyCredits();
					credits = 2000;
				}
			}
		}
	}
}

int PlayerShip::getAsteroidsDestroyed()
{
	return asteroidsDestroyed;
}

void PlayerShip::killCountIncrease()
{
	asteroidsDestroyed+=1;
}

void PlayerShip::skinChangeOne()
{
	bodySprite.setTexture(falconTexture);
}

void PlayerShip::skinChangeTwo()
{
	bodySprite.setTexture(frigateTexture);
}

void PlayerShip::skinChangeThree()
{
	bodySprite.setTexture(cruiserTexture);
}





int PlayerShip::resetShield()
{
	playerShield = 400;
	playerShieldBar.setSize(sf::Vector2f(playerShield, 5));
	return playerShield;
}

int PlayerShip::resetHealth()
{
	playerHealth = 400;
	playerHealthBar.setSize(sf::Vector2f(playerHealth, 5));
	return playerHealth;
}
int PlayerShip::removeCredits(int t_int)
{
	credits = credits - t_int;
	return credits;
}
int PlayerShip::killCounter(int t_int)
{
	killCount += t_int;
	return killCount;
}
int PlayerShip::getkillCounter()
{
	return killCount;
}



