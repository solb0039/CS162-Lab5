#ifndef ANT_HPP
#define ANT_HPP


#include "critter.hpp"
#include "utils.hpp"

class ant : public critter {

protected:
	

public:
	ant();
	~ant();
	virtual void move(critter***, int, int);
	char getIndicator() { return indicator; }
	void breed(critter***, int, int);


};

#endif
