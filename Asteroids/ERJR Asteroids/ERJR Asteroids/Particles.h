#pragma once
#include "SFML/Graphics.hpp" 
#include "Globals.h"

//These are the particles used in game

class Particle
{
public:
	sf::RectangleShape shape;
	sf::Vector2f velocity;
	int framesToLive;
};


class Smoke
{
public:
	sf::CircleShape shape;
	sf::Vector2f velocity;
	int framesToLive;
};

//when asteroids break, make particles
class ParticleSystemAsteroids
{
public:
	static const int numParticles = 18;
	Smoke particles[numParticles];
	float maxSpeed = 5;
	sf::Vector2f center;

	ParticleSystemAsteroids()
	{

	}
	void Initialise(sf::Vector2f position)
	{
		center = position;
		//for loop to initialise all the particles

		for (int i = 0; i < numParticles; i++)
		{
			particles[i].shape.setRadius({ 6.0f });
			particles[i].shape.setPosition(center);
			particles[i].shape.setFillColor(sf::Color(static_cast<unsigned int>(128), static_cast<unsigned int>(128), static_cast<unsigned int>(128)));
			particles[i].velocity.x = rand() / double(RAND_MAX) * maxSpeed * 2 - maxSpeed;
			particles[i].velocity.y = rand() / double(RAND_MAX) * maxSpeed * 2 - maxSpeed;
			particles[i].framesToLive = 120;
		}
	}
	void Update()
	{
		//for loop to move all the particles
		for (int i = 0; i < numParticles; i++)
		{
			if (particles[i].framesToLive > 0)
			{
				particles[i].shape.move(particles[i].velocity);
			}
		}
	}
	void Draw(sf::RenderWindow &window)
	{
		//for loop to draw all the particles
		for (int i = 0; i < numParticles; i++)
		{
			if (particles[i].framesToLive > 0)
			{
				window.draw(particles[i].shape);
				particles[i].framesToLive--;
			}
		}
	}
};


//when large asteroid breaks, crack apart
class ParticleSystemAsteroidsBreak
{
public:
	static const int numParticles = 7;
	Smoke particles[numParticles];
	float maxSpeed = 3.5;
	sf::Vector2f center;

	ParticleSystemAsteroidsBreak()
	{

	}
	void Initialise(sf::Vector2f position)
	{
		center = position;
		//for loop to initialise all the particles

		for (int i = 0; i < numParticles; i++)
		{
			particles[i].framesToLive = 255;
			particles[i].shape.setRadius({ 14.0f });
			particles[i].shape.setPosition(center);
			particles[i].shape.setFillColor(sf::Color(static_cast<unsigned int>(210), static_cast<unsigned int>( 180), static_cast<unsigned int>( 140)));
			particles[i].velocity.x = rand() / double(RAND_MAX) * maxSpeed * 2 - maxSpeed;
			particles[i].velocity.y = rand() / double(RAND_MAX) * maxSpeed * 2 - maxSpeed;
			
		}
	}
	void Update()
	{
		//for loop to move all the particles
		for (int i = 0; i < numParticles; i++)
		{
			if (particles[i].framesToLive > 0)
			{
				particles[i].shape.move(particles[i].velocity);
				particles[i].shape.setFillColor(sf::Color(static_cast<unsigned int>(210), static_cast<unsigned int>(180), static_cast<unsigned int>(140)));
			}

		}
	}
	void Draw(sf::RenderWindow &window)
	{
		//for loop to draw all the particles
		for (int i = 0; i < numParticles; i++)
		{
			if (particles[i].framesToLive > 0)
			{
				window.draw(particles[i].shape);
				particles[i].framesToLive--;
			}

		}
	}
};


//when ship hits something, make white bits fall off
class ParticleSystemPlayerCollision
{
public:
	static const int numParticles = 8;
	Smoke particles[numParticles];
	float maxSpeed = 5;
	sf::Vector2f center;

	ParticleSystemPlayerCollision()
	{

	}
	void Initialise(sf::Vector2f position)
	{
		center = position;
		//for loop to initialise all the particles

		for (int i = 0; i < numParticles; i++)
		{
			particles[i].shape.setRadius({ 2.50f });
			particles[i].shape.setPosition(center);
			particles[i].shape.setFillColor(sf::Color(static_cast<unsigned int>(248), static_cast<unsigned int>(248), static_cast<unsigned int>(255))); //white(ish)
			particles[i].velocity.x = rand() / double(RAND_MAX) * maxSpeed * 2 - maxSpeed;
			particles[i].velocity.y = rand() / double(RAND_MAX) * maxSpeed * 2 - maxSpeed;
			particles[i].framesToLive = 70;
		}
	}
	void Update()
	{
		//for loop to move all the particles
		for (int i = 0; i < numParticles; i++)
		{
			if (particles[i].framesToLive > 0)
			{
				particles[i].shape.move(particles[i].velocity);
			}

		}
	}
	void Draw(sf::RenderWindow &window)
	{
		//for loop to draw all the particles
		for (int i = 0; i < numParticles; i++)
		{
			if (particles[i].framesToLive > 0)
			{
				window.draw(particles[i].shape);
				particles[i].framesToLive--;
			}

		}
	}
};
