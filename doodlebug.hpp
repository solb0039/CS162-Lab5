#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP

#include "critter.hpp"

class doodlebug : public critter {

protected:


public:
	doodlebug();
	~doodlebug();
	virtual void move(critter***, int, int);
	char getIndicator() { return indicator; }
	void eatAnt(critter***, int, int);
	void breed(critter***, int, int);
	

};

#endif
