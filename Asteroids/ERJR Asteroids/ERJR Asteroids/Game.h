#pragma once
#include "Globals.h"
#include "Bullet.h"
#include "Player.h"
#include "MyVector3.h"
#include "Asteroid.h"
#include "MoneyDrop.h"
#include "LargeAsteroid.h"
#include "Particles.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

// authors Ethan Rennick - Jack Regan

#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>

//maybe use later once game functions
enum GameState
{
	Licence, Splash, Menu, Help, Gameplay
};

enum WaveLevel
{
	Wave1, Wave2, Wave3, Wave4, Wave5, Wave6, Wave7, Boss
};

class Game
{
public:
	Game();
	~Game();
	void run();

	//object declaration
	PlayerShip myPlayer;
	Asteroid asteroid[MAX_ASTEROIDS];
	LargeAsteroid largeAsteroid[MAX_ASTEROIDS];
	Bullet bullets[MAX_BULLETS];
	MoneyDrop money[MAX_DROPS];


	GameState currentState = Licence;

	//bool central
	bool licenseBool = true;
	int licenseCount = 600;
	bool splashBool = false;
	int splashCount = 450;
	bool menuBool = false;
	bool gameplayBool = false;
	bool helpScreenBool = false;
	bool gameOver = false;
	bool pause = false;
	bool upgrading = false;

	//bullets appear on sprite
	bool leftSide;
	bool rightSide;

	//levels?
	bool levelOne = true;
	bool levelTwo = false;
	bool levelThree = false;
	bool levelFour = false;
	bool gameWin = false;

	//sprites and textures for screens
	sf::Sprite licenseSprite; //background texture + sprite
	sf::Texture licenseTexture;
	sf::Texture splashTexture;
	sf::Sprite splashSprite;
	sf::Texture menuTexture;
	sf::Sprite menuSprite;
	sf::Texture helpScreenTexture;
	sf::Sprite  helpScreenSprite;
	sf::Sprite spaceSprite;
	sf::Texture spaceTexture;
	sf::Sprite gameOverSprite;
	sf::Texture gameOvertexture;
	sf::Sprite warningSprite;
	sf::Texture warningTexture;
	int warningDisplayCounter = 16;
	sf::Sprite upgradeSprite; //upgrade screen stuff
	sf::Texture upgradeTexture;
	sf::Sprite winSprite; //win screen stuff
	sf::Texture winTexture;


	//text stuff
	sf::Text text;
	sf::Font font;
	sf::Text displayPlayerStats;
	

	//sound
	//licence splash
	sf::SoundBuffer licenseSoundBuffer;
	sf::Sound licenseSound;
	bool licenseSoundPlayed = false;
	//sound for when changin screens
	sf::SoundBuffer beepSoundBuffer;
	sf::Sound beepSound;
	//upgrade whirring sound
	sf::SoundBuffer upgradeSoundBuffer;
	sf::Sound upgradeSound;
	//laser firing sound
	sf::SoundBuffer laserSoundBuffer;
	sf::Sound laserSound;
	//red alert sound
	sf::SoundBuffer alertSoundBuffer;
	sf::Sound alertSound;
	//scream sound
	sf::SoundBuffer screamSoundBuffer;
	sf::Sound screamSound;


	//control number of asteroids
	int numLargeAsteroids;
	int numLittleAsteroids;

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	void loadContent();
	void bulletFiring();

	void manageMenusUpdate();
	void manageMenusDraw();
	void drawGameplay();
	void gameplayLoop();

	sf::RenderWindow m_window; // main SFML window

	bool m_exitGame; // control exiting game

};

#endif // !GAME

