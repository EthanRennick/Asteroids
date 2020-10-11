//money class declaration header file
#pragma once

//include shtuff
#include "SFML/Graphics.hpp" 
#include "Globals.h"
#include <iostream>
#include "MyVector3.h"

//money class
class MoneyDrop
{
	sf::Texture moneyTexture;
	sf::Sprite moneySprite;
	bool dropped; //has it been dropped yet

public:
	MoneyDrop(); //default constructor
	void loadImage();
	sf::Sprite getImage(); //get sprite
	bool getDropped();
	void spawnCredits(sf::Vector2f t_position);
	void changeDrop(bool t_bool);
	void destroyCredits();
};