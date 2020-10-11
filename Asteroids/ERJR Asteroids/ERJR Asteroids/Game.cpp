


#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT), 32 }, "Asteroids Game" },
	m_exitGame{ false } //when true game will exit
{
	loadContent();
}

void Game::loadContent()
{
	//load all of the game screens!
	if (!licenseTexture.loadFromFile("ASSETS/IMAGES/EdgeLicense.png")) //load menu
	{
		std::cout << "error with license texture file"; //error
	}
	licenseSprite.setTexture(licenseTexture); //set sprite to texture
	licenseSprite.setPosition(0, 0); //set position

	if (!splashTexture.loadFromFile("ASSETS/IMAGES/splash.png")) //load menu
	{
		std::cout << "error with splash texture file"; //error
	}
	splashSprite.setTexture(splashTexture); //set sprite to texture
	splashSprite.setScale(.5, .5);
	splashSprite.setPosition(250, 0); //set position

	//background textures used in gameplay
	if (!spaceTexture.loadFromFile("ASSETS/IMAGES/gamePlayBackground.png")) //load menu
	{
		std::cout << "error with gameplay background texture file"; //error
	}
	spaceSprite.setTexture(spaceTexture); //set sprite to texture
	spaceSprite.scale(.42, .42);

	//the main manu sprite 
	if (!menuTexture.loadFromFile("ASSETS/IMAGES/menu.png")) //load menu
	{
		std::cout << "error with smenu texture file"; //error
	}

	menuSprite.setTexture(menuTexture); //set sprite to texture
	menuSprite.setScale(.5, .5);
	menuSprite.setPosition(250, 0); //set position

	//the help screen sprite
	if (!helpScreenTexture.loadFromFile("ASSETS/IMAGES/helpScreen.png")) //load menu
	{
		std::cout << "error with help screen texture file"; //error
	}
	helpScreenSprite.setTexture(helpScreenTexture); //set sprite to texture
	helpScreenSprite.setPosition(0, 0); //set position
	helpScreenSprite.setScale(.6, .8);

	//a little asteroid warnign system loading
	if (!warningTexture.loadFromFile("ASSETS/IMAGES/asteroidWarning.png")) //load menu
	{
		std::cout << "error with asteroid warning texture file"; //error
	}
	warningSprite.setTexture(warningTexture); //set sprite to texture
	warningSprite.setScale(.4, .4);

	//loads the end/game over screen 
	if (!gameOvertexture.loadFromFile("ASSETS/IMAGES/gameOver.jpg")) //load sprite
	{
		std::cout << "error with license texture file"; //error
	}
	gameOverSprite.setTexture(gameOvertexture); //set sprite to texture
	gameOverSprite.setPosition(250, 0); //set position
	gameOverSprite.setScale(.5, .5); //scale correctly

	if (!upgradeTexture.loadFromFile("ASSETS/IMAGES/upgradeScreen.png")) //load sprite
	{
		std::cout << "error with upgrade screen file"; //error
	}
	upgradeSprite.setTexture(upgradeTexture); //set sprite to texture

	if (!winTexture.loadFromFile("ASSETS/IMAGES/win.png")) //load sprite
	{
		std::cout << "error with win screen file"; //error
	}
	winSprite.setTexture(winTexture); //set sprite to texture

	//load text and stuff
	if (!font.loadFromFile("ASSETS/TEXT/DISTGRG_.ttf"))
	{
		std::cout << "error with font file file";
	}

	// set up the message string 
	text.setFont(font);  // set the font for the text
	text.setCharacterSize(24); // set the text size
	text.setFillColor(sf::Color::White); // set the text colour
	text.setPosition(10, 10);  // its position on the screen

	displayPlayerStats.setFont(font);  // set the font for the text
	displayPlayerStats.setCharacterSize(24); // set the text size
	displayPlayerStats.setFillColor(sf::Color::White); // set the text colour
	displayPlayerStats.setPosition(10, 10);  // its position on the screen

	
	//LOAD SOUNDS
	licenseSoundBuffer.loadFromFile("ASSETS/AUDIO/edge_studios.wav");
	licenseSound.setBuffer(licenseSoundBuffer);

	//SOUND FILE FOR R2 BEEP
	beepSoundBuffer.loadFromFile("ASSETS/AUDIO/boop.wav");
	beepSound.setBuffer(beepSoundBuffer);

	//SOUND FILE FOR ALERT 
	alertSoundBuffer.loadFromFile("ASSETS/AUDIO/alert.wav");
	alertSound.setBuffer(alertSoundBuffer);

	//SOUND FOR UPGRADE MENU 
	upgradeSoundBuffer.loadFromFile("ASSETS/AUDIO/upgrade.wav");
	upgradeSound.setBuffer(upgradeSoundBuffer);

	//SOUND FOR LASERS
	laserSoundBuffer.loadFromFile("ASSETS/AUDIO/laserFire.wav");
	laserSound.setBuffer(laserSoundBuffer);


	//SOUND FOR SCREAM
	screamSoundBuffer.loadFromFile("ASSETS/AUDIO/scream.wav");
	screamSound.setBuffer(screamSoundBuffer);

}




/// <summary>
/// default destructor for game, nothing to release
/// </summary>
Game::~Game()
{

}

/// <summary>
/// game loop running at 60fps
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event nextEvent;
	while (m_window.pollEvent(nextEvent))
	{
		if (sf::Event::Closed == nextEvent.type) // window message
		{
			m_window.close();
		}
		if (gameplayBool == true)
		{
			if (sf::Event::KeyReleased == nextEvent.type) //If the space key is pressed and released
			{
				if (nextEvent.key.code == sf::Keyboard::Space)
				{
					bulletFiring(); //fire a bullet
				}

				if (nextEvent.key.code == sf::Keyboard::Escape)
				{
					if (pause == false) //if not paused
					{
						beepSound.play();
						pause = true; //pause game

					}
					else //otherwise
					{
						beepSound.play();

						pause = false; //game isnt paused
					}
				}

				if (nextEvent.key.code == sf::Keyboard::Tab)//adds button input for the crafting menu
				{
					if (upgrading == false)
					{
						upgradeSound.play();//load sound
						upgrading = true;//sets to true
					}
					else
					{
						beepSound.play();//load sound

						upgrading = false;//sets to false
					}
				}

			}
		}
	}
}


void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame) //if exited game
	{
		m_window.close(); //close window
	}
	if (gameplayBool == false)
	{
		manageMenusUpdate(); //look for menu management
	}
	if (gameplayBool == true) //only look for gameplay loop if game is being played
	{
		gameplayLoop(); //go through gameplay stuff - > player, asteroids, bullets, shop etc	
	}	
}

//draw stuff to screen
void Game::render()
{
	m_window.clear(); //clear screen
	
	if (gameplayBool == true) //if the game is being played, draw all this stuff
	{
		drawGameplay(); //draw stuff relevant to game
	}
	else
	{
		manageMenusDraw(); //organise menus
	}

	//the following code draws the different aspects of the code
	m_window.display();
}

//function for bullet firing
void Game::bulletFiring()
{
	//loop to look at all the bullets
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bullets[i].readyToFire == true && bullets[i + 1].readyToFire == true) //if the current bullet and the next one are good to go
		{
			if (bullets[i].bulletsScreen.getPosition() == bullets[i].storageVector && bullets[i + 1].bulletsScreen.getPosition() == bullets[i + 1].storageVector) //AND if they're in storage
			{
				//then setup the two bullets like so
				bullets[i].bulletsScreen.setPosition(myPlayer.getBody().getPosition() + sf::Vector2f(25, 25)); //first bullet should go to the right side of the sprite
				bullets[i + 1].bulletsScreen.setPosition(myPlayer.getBody().getPosition() + sf::Vector2f(-25, -25)); //another bullet goes to the left side

				bullets[i].bulletVelocity = (myPlayer.getPlayerLookDirection()); //the velocity is enlarged
				bullets[i].bulletVelocity.x = bullets[i].bulletVelocity.x * 8;
				bullets[i].bulletVelocity.y = bullets[i].bulletVelocity.y * 8;
				bullets[i].readyToFire = false; //the bullet is not ready to fire again until the counter is at 0 
				bullets[i].waitToFireCounter = 10;

				//repeat steps above for below
				bullets[i + 1].bulletVelocity = (myPlayer.getPlayerLookDirection());
				bullets[i + 1].bulletVelocity.x = bullets[i + 1].bulletVelocity.x * 8;
				bullets[i + 1].bulletVelocity.y = bullets[i + 1].bulletVelocity.y * 8;
				bullets[i + 1].readyToFire = false;
				bullets[i + 1].waitToFireCounter = 10;

				i += 2; //increase the i in the loop to ignore the next bullet
				laserSound.play();

				break; //also get out of the loop
			}
		}
		else //if the bullets aren't ready
		{
			//lower both of their counters, and if it gets to 0, set them ready to fire
			bullets[i + 1].waitToFireCounter--;
			if (bullets[i + 1].waitToFireCounter <= 0)
			{
				bullets[i + 1].readyToFire = true;
			}
			bullets[i].waitToFireCounter--;
			if (bullets[i].waitToFireCounter <= 0)
			{
				bullets[i].readyToFire = true;
			}
		}
	}
}

//draw the appropriate menu to screen 
void Game::manageMenusDraw()
{
	if (licenseBool == true) //if the licence screen is on, decrease counter and only display for a short time
	{
		m_window.draw(licenseSprite);
		licenseCount--;
		if (licenseCount == 0) //when counter is 0, load splash bool
		{
			splashBool = true;
			licenseBool = false;
		}
		if (licenseSoundPlayed == false) //if not played the licence screen sound, then play it
		{
			licenseSound.play();
			licenseSoundPlayed = true;
		}
	}
	if (splashBool == true) //then the splash screen
	{
		m_window.draw(splashSprite); //draw it
		splashCount--; //lower counter
		if (splashCount == 0) //if it gets to 0, go to menu
		{
			splashBool = false;
			menuBool = true;
		}
	}
	if (gameOver == true)
	{
		gameplayBool = false;
		m_window.draw(gameOverSprite);
		text.setString("Unlucky Fighter, Press [Space] to Restart");
		text.setPosition(220, 550);
		m_window.draw(text);
	}
	if (menuBool == true) //if user is on the main menu
	{
		m_window.draw(menuSprite); //show sprite

		//display relevant information in text
		text.setString("Main Menu");
		text.setPosition(430, 550);
		m_window.draw(text);
		text.setString("Press [1] to play the game");
		text.setPosition(325, 590);
		m_window.draw(text);
		text.setString("Press [2] for help");
		text.setPosition(370, 630);
		m_window.draw(text);
		text.setString("Press [3] to Exit");
		text.setPosition(370, 670);
		m_window.draw(text);
	}
	if (helpScreenBool == true) //if user in on the help Screen
	{
		//display all relevant information on the help screen
		m_window.draw(helpScreenSprite); //show sprite
		text.setString("Controls");
		text.setPosition(60, 60);
		m_window.draw(text);
		text.setString("Press W to go forwards");
		text.setPosition(60, 90);
		m_window.draw(text);
		text.setString("Press S  to go backwards");
		text.setPosition(60, 120);
		m_window.draw(text);
		text.setString("Press A to rotate left");
		text.setPosition(60, 150);
		m_window.draw(text);
		text.setString("Press D to rotate right");
		text.setPosition(60, 180);
		m_window.draw(text);
		text.setString("Press Spacebar to fire lasers)");
		text.setPosition(60, 210);
		m_window.draw(text);
		text.setString("Press Tab to enter the upgrade menu");
		text.setPosition(60, 240);
		m_window.draw(text);
		text.setString("Press Escape to pause the game");
		text.setPosition(60, 270);
		m_window.draw(text);
		text.setString("What to do");
		text.setPosition(60, 330);
		m_window.draw(text);
		text.setString("Your main mission\nis to clear a path\nthrough the asteroid field\nso that the rebel\nfleet can follow and\nengage the death star\nin battle.");
		text.setPosition(60, 360);
		m_window.draw(text);
		text.setString("You will have to fight\nmore in each asteroid field.\nThe rebels will send a\ndifferent ship each time.\nGood luck, pilot. @");
		text.setPosition(60, 540);
		m_window.draw(text);
		text.setString("Press left shift to return to main menu");
		text.setPosition(60, 750);
		m_window.draw(text);
	
	}
	if (gameWin == true)
	{
		m_window.draw(winSprite);
		text.setString("Well done! \n The rebels made it\n succesfully through\n the asteroid fields\n and fought the death\n star and won!");
		text.setPosition((SCREEN_WIDTH/2) - 40, 60);
		m_window.draw(text);
		text.setString("Press #space# to return to menu");
		text.setPosition((SCREEN_WIDTH/2) -100,500);
		m_window.draw(text);
	}
}

//draw gameplay stuff
void Game::drawGameplay()
{
	m_window.draw(spaceSprite); //background
	if (levelOne)
	{
		text.setString("Level One @");
		text.setPosition(10, 40);
		m_window.draw(text);

		text.setString("Progress to next level: " + std::to_string(myPlayer.getAsteroidsDestroyed()) + " # 30");
		text.setPosition(10, 70);
		m_window.draw(text);
	}
	else if (levelTwo)
	{
		text.setString("Level Two @");
		text.setPosition(10, 40);
		m_window.draw(text);

		text.setString("Progress to next level: " + std::to_string(myPlayer.getAsteroidsDestroyed()) + " # 50");
		text.setPosition(10, 70);
		m_window.draw(text);

		myPlayer.skinChangeOne();
	}
	else if (levelThree)
	{
		text.setString("Level Three @");
		text.setPosition(10, 40);
		m_window.draw(text);

		text.setString("Progress to next level: " + std::to_string(myPlayer.getAsteroidsDestroyed()) + " # 90");
		text.setPosition(10, 70);
		m_window.draw(text);
		myPlayer.skinChangeTwo();
	}
	else if (levelFour)
	{
		text.setString("Level Four @");
		text.setPosition(10, 40);
		m_window.draw(text);

		text.setString("Progress to next level: " + std::to_string(myPlayer.getAsteroidsDestroyed()) + " # 140");
		text.setPosition(10, 70);
		m_window.draw(text);
		myPlayer.skinChangeThree();
	}
	//hud stuff
	displayPlayerStats.setPosition(10, 10);
	displayPlayerStats.setString("Credits: " + std::to_string(myPlayer.getCredits()));
	m_window.draw(displayPlayerStats);
	m_window.draw(myPlayer.getBody()); //player draw
	text.setString("HEALTH");
	text.setPosition(200, 710);
	m_window.draw(text);
	m_window.draw(myPlayer.getPlayerHealth());
	text.setString("SHIELD");
	text.setPosition(700, 710);
	m_window.draw(text);
	m_window.draw(myPlayer.getPlayerShield());
	text.setString("Fuel Levels: ");
	text.setPosition(180, 10);
	m_window.draw(text);
	m_window.draw(myPlayer.getFuelMeter());

	if (myPlayer.getAsteroidCollisionStatus() == true) //if player collides with asteroid
	{
		alertSound.play();
		warningSprite.setPosition(myPlayer.getBody().getPosition()); //set warning symbol to draw
		m_window.draw(warningSprite);
		warningDisplayCounter--; //display for 16 ticks
		if (warningDisplayCounter == 0)
		{
			warningDisplayCounter = 20; //reset counter and set not to have collided
			myPlayer.changeAsteroidCollisionStatus(false);
		}
	}

	for (int i = 0; i < MAX_LARGEASTEROIDS; i++) //draw every asteroid
	{
		if (largeAsteroid[i].getAlive() == true) //only if alive
		{
			m_window.draw(largeAsteroid[i].getBody());
		}
		largeAsteroid[i].breakApart.Draw(m_window);
	}
	
	for (int i = 0; i < MAX_BULLETS; i++) //draw the player's bullets
	{
		m_window.draw(bullets[i].getBulletBody());
	}

	for (int i = 0; i < MAX_DROPS; i++)
	{
		
		m_window.draw(money[i].getImage());//draw the money drop
		if (money[i].getDropped() == true)
		{
			m_window.draw(money[i].getImage());
		}
	
	}

	for (int i = 0; i < MAX_ASTEROIDS; i++) //draw every asteroid
	{
		//draw little asteroids
		m_window.draw(asteroid[i].getBody());
		asteroid[i].explosion.Draw(m_window);
	}

	if (pause == true) //display pause info
	{
		text.setString("PAUSED");
		text.setPosition((SCREEN_WIDTH / 2) - 40, SCREEN_HEIGHT / 2);
		m_window.draw(text);
		text.setString("\n\n\nPress [3] to Exit the game\nProgress will not be saved!");
		text.setPosition((SCREEN_WIDTH / 2) - 180, SCREEN_HEIGHT / 2);
		m_window.draw(text);
	}

	if (upgrading == true) //display relevant data
	{
		m_window.draw(upgradeSprite);
		text.setString("Upgrade Screen");
		displayPlayerStats.setPosition((SCREEN_WIDTH / 2) - 40, 70);
		displayPlayerStats.setString("Credits: " + std::to_string(myPlayer.getCredits()));
		m_window.draw(displayPlayerStats);
		text.setPosition((SCREEN_WIDTH / 2) - 90, 30);
		m_window.draw(text);
		text.setString("Press [1] to restore Health");
		text.setPosition((SCREEN_WIDTH / 2) - 180, 150);
		m_window.draw(text);
		text.setString("cost: 500");
		text.setPosition((SCREEN_WIDTH / 1.6) - 180, 170);
		m_window.draw(text);
		text.setString("Press [2] to restore Shield");
		text.setPosition((SCREEN_WIDTH / 2) - 180, 250);
		m_window.draw(text);
		text.setString("cost: 200");
		text.setPosition((SCREEN_WIDTH / 1.6) - 180, 270);
		m_window.draw(text);
		text.setString("Press [3] to increase fire rate");
		text.setPosition((SCREEN_WIDTH / 2) - 180, 350);
		m_window.draw(text);
		text.setString("cost: 1000");
		text.setPosition((SCREEN_WIDTH / 1.6) - 180, 370);
		m_window.draw(text);
	}
}

//this manages the different menus before you start the gameplay
void Game::manageMenusUpdate()
{
	//manage key input on screens and stuff
	if (gameplayBool == false && menuBool == true)
	{
		//menu -> gameplay
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			beepSound.play();
			gameplayBool = true;
			menuBool = false;
			gameOver = false;
		}
		//menu -> help
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			beepSound.play();
			helpScreenBool = true;
		}
		//help -> menu
		if (helpScreenBool == true && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			beepSound.play();
			helpScreenBool = false;
		}
		//menu to exit
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			m_exitGame = true;
		}
	}

	//game over -> menu
	if (gameOver == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			for (int i = 0; i < MAX_ASTEROIDS; i++)
			{
				asteroid[i].destroyAsteroid();
			}
			for (int i = 0; i < MAX_LARGEASTEROIDS; i++)
			{
				largeAsteroid[i].resetAsteroid();
			}
			for (int i = 0; i < MAX_BULLETS; i++)
			{
				bullets[i].setPos(bullets[i].storageVector);
				bullets[i].setBulletVelocity(0, 0);
			}
			gameOver = false;
			menuBool = true;
			levelOne = true;
			levelTwo = false;
			levelThree = false;
			levelFour = false;
			myPlayer.resetPlayer();
			beepSound.play();
		}
	}

	if (gameWin == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			for (int i = 0; i < MAX_ASTEROIDS; i++)
			{
				asteroid[i].destroyAsteroid();
			}
			for (int i = 0; i < MAX_LARGEASTEROIDS; i++)
			{
				largeAsteroid[i].resetAsteroid();
			}
			for (int i = 0; i < MAX_BULLETS; i++)
			{
				bullets[i].setPos(bullets[i].storageVector);
				bullets[i].setBulletVelocity(0, 0);
			}
			gameWin = false;
			gameOver = false;
			menuBool = true;
			levelOne = true;
			levelTwo = false;
			levelThree = false;
			levelFour = false;
			myPlayer.resetPlayer();
			beepSound.play();
		}
	}
}

//update gameplay loop function
void Game::gameplayLoop()
{
	if (upgrading == false)
	{
		if (pause == false)
		{
			myPlayer.movement(); //player movement
			myPlayer.collisionWithAsteroids(asteroid); //collision detection with asteroid
			myPlayer.collisionWithLargeAsteroids(largeAsteroid, asteroid);//collison detection with big asteroid
			myPlayer.currencyColission(money);
			myPlayer.playerParticle.Update();

			for (int i = 0; i < MAX_BULLETS; i++)
			{
				bullets[i].bulletMovement();	//move bullets
				bullets[i].collisionsWithAsteroids(asteroid, largeAsteroid, money, myPlayer); //bullets hitting little asteroids
				bullets[i].collisionWithLargerAsteroids(largeAsteroid, asteroid); //big asteroid bullet collisions
			}
			for (int i = 0; i < MAX_ASTEROIDS; i++)
			{
				asteroid[i].explosion.Update();
				if (asteroid[i].getAlive() == true && asteroid[i].getFlightStatus() == true) //if little asteroid are alive, move them
				{
					asteroid[i].asteroidMovement(); //move all asteroids
				}
			}
			for (int i = 0; i < MAX_LARGEASTEROIDS; i++)
			{
				largeAsteroid[i].breakApart.Update();
				if (largeAsteroid[i].getAlive() == true) //if big asteroid is alive, move it
				{
					largeAsteroid[i].asteroidMovement(); //move all asteroids
				}
			}
			if (myPlayer.currentHealth() <= 0) //if player dies
			{
				gameplayBool = false; //no longer doin gameplay
				gameOver = true; //game play
				screamSound.play();
			}

			//30,50,90,140 //diffuculty curve
			//checks for level progress
			if (levelOne == true)
			{
				if (myPlayer.getAsteroidsDestroyed() == 30)
				{
					levelOne = false;
					levelTwo = true;
					for (int i = 0; i < MAX_ASTEROIDS; i++)
					{
						asteroid[i].destroyAsteroid();
					}
					for (int i = 0; i < MAX_LARGEASTEROIDS; i++)
					{
						largeAsteroid[i].resetAsteroid();
					}
					myPlayer.nextLevel();
					for (int i = 0; i < MAX_BULLETS; i++)
					{
						bullets[i].setPos(bullets[i].storageVector);
						bullets[i].setBulletVelocity(0, 0);
					}

				}
			}
			else if (levelTwo == true)
			{
				if (myPlayer.getAsteroidsDestroyed() == 50)
				{
					levelOne = false;
					levelTwo = false;
					levelThree = true;
					for (int i = 0; i < MAX_ASTEROIDS; i++)
					{
						asteroid[i].destroyAsteroid();
					}
					for (int i = 0; i < MAX_LARGEASTEROIDS; i++)
					{
						largeAsteroid[i].resetAsteroid();
					}
					myPlayer.nextLevel();
					for (int i = 0; i < MAX_BULLETS; i++)
					{
						bullets[i].setPos(bullets[i].storageVector);
						bullets[i].setBulletVelocity(0, 0);
					}
				}
			}
			else if (levelThree == true)
			{
				if (myPlayer.getAsteroidsDestroyed() == 90)
				{
					levelThree = false;
					levelFour = true;
					for (int i = 0; i < MAX_ASTEROIDS; i++)
					{
						asteroid[i].destroyAsteroid();
					}
					for (int i = 0; i < MAX_LARGEASTEROIDS; i++)
					{
						largeAsteroid[i].resetAsteroid();
					}
					myPlayer.nextLevel();
					for (int i = 0; i < MAX_BULLETS; i++)
					{
						bullets[i].setPos(bullets[i].storageVector);
						bullets[i].setBulletVelocity(0, 0);
					}
				}
			}
			else if (levelFour == true)
			{
				if (myPlayer.getAsteroidsDestroyed() == 140)
				{
					levelFour = false;
					gameWin = true;
					gameplayBool = false;
					for (int i = 0; i < MAX_ASTEROIDS; i++)
					{
						asteroid[i].destroyAsteroid();
					}
					for (int i = 0; i < MAX_LARGEASTEROIDS; i++)
					{
						largeAsteroid[i].resetAsteroid();
					}
					myPlayer.nextLevel();
					for (int i = 0; i < MAX_BULLETS; i++)
					{
						bullets[i].setPos(bullets[i].storageVector);
						bullets[i].setBulletVelocity(0, 0);
					}
				}
			}
			
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				m_exitGame = true;
			}
		}

		
	}

	//if in the upgrade menu
	if (upgrading == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			myPlayer.getCredits();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))//handles upgrade menu option 1
		{
			if (myPlayer.getCredits() >= 500)
			{
				myPlayer.resetHealth();
				myPlayer.removeCredits(500);
			}
			
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))//handles upgrade menu option 2
		{

			if (myPlayer.getCredits() >= 200)
			{
				myPlayer.resetShield();
				myPlayer.removeCredits(200);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))//handles upgrade menu option 3
		{
			if (myPlayer.getCredits() >= 1000)
			{
				for (int i = 0; i < MAX_BULLETS; i++)
				{
					bullets[i].waitToFireCounter = 5;
					bullets[i + 1].waitToFireCounter = 5;
				}
				myPlayer.removeCredits(1000);
			}
		}
	}
}



