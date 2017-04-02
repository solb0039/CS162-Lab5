#ifndef CRITTER_HPP
#define CRITTER_HPP
#include <iostream>

class critter {

protected:
	int lives;
	char indicator;
	int eatCounter;
	bool movedAleady;

public:
	critter();
	~critter();
	char getIndicator() {return indicator;}
	void incrementLives();
	int getLives() { return lives; }
	void resetLives();
	
	void incrementEatCounter();
	int getEatCounter() { return eatCounter; }
	void resetEatCounter();

	bool getMovedAlready() { return movedAleady; }
	void setMovedAlready();
	void resetMovedAlready();

	virtual void move(critter***, int, int) = 0 ;

};

#endif
