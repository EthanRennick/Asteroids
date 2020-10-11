// Player class declaration
#pragma once

#include "SFML/Graphics.hpp" 
#include "Globals.h"
#include <iostream>
#include "MyVector3.h"
#include "Asteroid.h"
#include "LargeAsteroid.h"
#include "MoneyDrop.h"
#include"Particles.h"

//player class -> you play as this
class PlayerShip
{
	sf::Sprite bodySprite; //player sprite
	sf::Texture spaceShipTexture; //player texture
	sf::Texture falconTexture;
	sf::Texture frigateTexture;
	sf::Texture cruiserTexture;


	int shipShields; 
	int credits; 
	int maxCredits = 2000;
	int shipSpeed; //speed you travel at
	int numOfBullets; //amount of bullets you have
	int hull; //strength of your hull - keep above 0 to survive
	int killCount = 0; //enemies you kill
	MyVector3 playerPosition; //your position
	float fuel;
	sf::RectangleShape fuelMeter;
	int asteroidsDestroyed;


	//look direction - used with regards to bullets
	MyVector3 playerVelocity;
	sf::Vector2f playerLookDirection{ 0,-1, };
	float angle = 0.0f;


	bool playerAlive = false; //is player alive?
	int playerHealth; //player's score - increase by killing / dodging ships
	int playerShield; //player's shields - damage this before hull
	bool reset = false; //has or hasnt reset game
	bool backwards = false;
	bool forwards = false;
	bool asteroidCollision = false;
	bool currencyCollision = false;
	sf::RectangleShape playerHealthBar;
	sf::RectangleShape playerShieldBar;

public:	  // declaration of member functions
	
	PlayerShip(); //constructor
	ParticleSystemPlayerCollision playerParticle;
	void loadImage(); //load images
	sf::Sprite getBody(); //get player sprite
	void setPosition(); //set position
	void resetPlayer(); //reset him if he dies
	void nextLevel();
	void movement(); //player movement
	void playerOffScreenCheck(); 
	void calculateMomentum();
	MyVector3 getPosition();
	sf::Vector2f getPlayerLookDirection();

	//asteroid collisions
	void collisionWithAsteroids(Asteroid t_asteroid[]);
	void collisionWithLargeAsteroids(LargeAsteroid t_asteroid[], Asteroid t_asteroidSmall[]);

	bool getAsteroidCollisionStatus();
	void changeAsteroidCollisionStatus(bool t_bool);
	sf::RectangleShape getPlayerHealth();
	sf::RectangleShape getPlayerShield();
	void lowerHealth();
	void lowerShield();
	int resetShield();
	int resetHealth();
	int currentHealth();
	int getCredits();

	sf::RectangleShape getFuelMeter();

	void addCredits();

	int getAsteroidsDestroyed();
	void killCountIncrease();
	void skinChangeOne();
	void skinChangeTwo();
	void skinChangeThree();
	
	void currencyColission(MoneyDrop moneyDrop[]);
	int removeCredits(int t_int);
	int killCounter(int t_int);
	int getkillCounter();
};
