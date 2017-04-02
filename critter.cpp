#include "critter.hpp"

critter::critter() 
{
	lives = 0;

}

critter::~critter() 
{

}

void critter::incrementLives() 
{
	lives += 1;
}

void critter::resetLives()
{
	lives = 0;
}

void critter::incrementEatCounter()
{
	eatCounter += 1;
}

void critter::resetEatCounter()
{
	eatCounter = 0;
}

void critter::setMovedAlready()
{
	movedAleady = true;
}

void critter::resetMovedAlready() 
{ 
	movedAleady = false;
}
