#include "MoneyDrop.h"


MoneyDrop::MoneyDrop()
{
	loadImage();
	moneySprite.setPosition(-200, -200);
	dropped = false;
}

void MoneyDrop::loadImage()
{
	if (!moneyTexture.loadFromFile("ASSETS/IMAGES/credits2.png")) //load
	{
		std::cout << "error with credits sprite file"; //error
	}
	moneySprite.setTexture(moneyTexture); //set texture to sprite
	moneySprite.setOrigin(43, 43);
	moneySprite.setScale(.06, .06);
}

sf::Sprite MoneyDrop::getImage()
{
	return moneySprite;
}

bool MoneyDrop::getDropped()
{
	return dropped;
}

void MoneyDrop::spawnCredits(sf::Vector2f t_position)
{
	moneySprite.setPosition(t_position);
	dropped = true;
}

void MoneyDrop::changeDrop(bool t_bool)
{
	dropped = t_bool;
}

void MoneyDrop::destroyCredits()
{
	moneySprite.setPosition(100,1000);
}
