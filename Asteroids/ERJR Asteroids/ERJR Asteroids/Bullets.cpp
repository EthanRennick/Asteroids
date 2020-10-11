#include "Bullet.h"

//default constructor
Bullet::Bullet()
{	
	loadImage();
	bulletsScreen.setPosition(-500.0f, -500.0f);
	bulletVelocity = { 0,0 };
	waitToFireCounter = 40;
	readyToFire = true;
	bool rightSide = true;
	bool leftSide = false;
}

void Bullet::loadImage()
{
	if (!bulletTexture.loadFromFile("ASSETS/IMAGES/laser.png")) //load
	{
		std::cout << "error with bullet laser file"; //error
	}
	bulletsScreen.setTexture(bulletTexture); //set texture to sprite
	bulletsScreen.setOrigin(15,15);
}

sf::Sprite Bullet::getBulletBody()
{
	return bulletsScreen;
}

int Bullet::getWaitToFire()
{
	return waitToFireCounter;
}

sf::Vector2f Bullet::getBulletVelocity()
{
	return bulletVelocity;
}

bool Bullet::getReadyToFire()
{
	return readyToFire;
}

void Bullet::setBulletVelocity(float t_val1, float t_val2)
{
	bulletVelocity = { t_val1,t_val2 };
}

void Bullet::setReadyToFire(bool t_bool)
{
	readyToFire = t_bool;
}

void Bullet::setWaitToFire(int t_waitCounter)
{
	waitToFireCounter = t_waitCounter;
}

void Bullet::lowerWaitToFire(int t_lower)
{
	waitToFireCounter = waitToFireCounter - t_lower;
}

void Bullet::setPos(sf::Vector2f t_position)
{
	bulletsScreen.setPosition(t_position);
}

//movement for bullet
void Bullet::bulletMovement()
{
	//if bullet is in use, move it
	if (bulletsScreen.getPosition().x != -500)
	{
		bulletsScreen.move(bulletVelocity);
		if (bulletsScreen.getPosition().x > SCREEN_WIDTH )
		{
			bulletsScreen.setPosition(storageVector);
			bulletVelocity={ 0.0, 0.0 };
			readyToFire = true;
		}
		if (bulletsScreen.getPosition().x < 0)
		{
			bulletsScreen.setPosition(storageVector);
			bulletVelocity = { 0.0, 0.0 };
			readyToFire = true;
		}
		if (bulletsScreen.getPosition().y > SCREEN_HEIGHT)
		{
			bulletsScreen.setPosition(storageVector);
			bulletVelocity = { 0.0, 0.0 };
			readyToFire = true;
		}
		if (bulletsScreen.getPosition().y < 0)
		{
			bulletsScreen.setPosition(storageVector);
			bulletVelocity = { 0.0, 0.0 };
			readyToFire = true;
		}
	}
}

//bullets hitting little asteroids
void Bullet::collisionsWithAsteroids(Asteroid t_asteroid[], LargeAsteroid t_largeAsteroid[], MoneyDrop t_moneyDrop[], PlayerShip &t_player)
{
	MyVector3 distanceVector; //distance between asteroid and bullet
	float length; //length of distance vector
	
	for (int j = 0; j < MAX_ASTEROIDS; j++)
	{
		distanceVector = bulletsScreen.getPosition() - t_asteroid[j].getBody().getPosition();
		length = distanceVector.length();

		if (length < BULLET_ORIGIN_TO_ASTEROID_ORIGIN) //if the distance of vector is less than contact number
		{
			readyToFire = false;
			bulletsScreen.setPosition(storageVector); //move bullet to storage
			t_asteroid[j].explosion.Initialise(t_asteroid[j].currentPosition()); //particles
			for (int k = 0; k < MAX_ASTEROIDS; k++)
			{
				if (t_moneyDrop[k].getDropped() == false)
				{
					t_asteroid[j].destroyAsteroid(); //destroy little asteroid
				
					t_moneyDrop[k].changeDrop(true);
					
					break;
				}
				if (t_moneyDrop[k].getDropped() == true)
				{
					for (int i = 0; i < MAX_DROPS; i++)
					{
						t_moneyDrop[i].spawnCredits(t_asteroid[j].getBody().getPosition());//spawns the money on the destroyed asteroids 
						if (i > 1)
						{
							t_moneyDrop[i - 1].destroyCredits();//destroys previous sprites (this broke the sprites if built up)
						}
						
					}

				}
				
				
			}
			t_player.killCountIncrease();
			t_asteroid[j].explosion.Initialise(sf::Vector2f(t_asteroid[j].getBody().getPosition()));
			t_asteroid[j].destroyAsteroid(); //destroy little asteroid
			readyToFire = true;

			for (int i = 0; i < MAX_LARGEASTEROIDS; i++)
			{
				if (t_largeAsteroid[i].getAlive() == false)
				{
					t_largeAsteroid[i].resetAsteroid();
				}
			}
		}
	}
}

void Bullet::collisionWithLargerAsteroids(LargeAsteroid t_largeAsteroid[], Asteroid t_asteroid[])
{
	MyVector3 distanceVector; //distance between asteroid and bullet
	float length; //length of distance vector

	for (int j = 0; j < MAX_LARGEASTEROIDS; j++)
	{
		distanceVector = bulletsScreen.getPosition() - t_largeAsteroid[j].getBody().getPosition();
		length = distanceVector.length();

		if (length < BULLET_ORIGIN_TO_LARGERASTEROID_ORIGIN)// if they touch
		{
			readyToFire = false;
			bulletsScreen.setPosition(storageVector); //reset bullet

			for (int i = 0; i < MAX_ASTEROIDS; i++) //look at mini steroids
			{
				if (t_asteroid[i].getFlightStatus() == false && t_asteroid[i+1].getFlightStatus() == false) //two asteroids are not in flight
				{
					//spawn them at big asteroid
					t_asteroid[i].spawnAsteroid(sf::Vector2f(t_largeAsteroid[j].getBody().getPosition()));
					t_asteroid[i+1].spawnAsteroid(sf::Vector2f(t_largeAsteroid[j].getBody().getPosition()));
					break; //get out of loop
				}
			}
			t_largeAsteroid[j].breakApart.Initialise(sf::Vector2f(t_largeAsteroid[j].getBody().getPosition()));
			t_largeAsteroid[j].destroyAsteroid(); //destroy big asteroid
			//we don't want to reset /respawn it because it will draw another large asteroid
			//and i wont have enough little asteroids to come out of it when it dies
		}
	}
}

