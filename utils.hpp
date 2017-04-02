#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include <string>
#include <limits>
#include <cstdlib>
#include <iostream>
#include <time.h>

int getRandomInteger(int);

int getInteger(std::string, int, int, int = 0);

bool getBoolean(std::string);

double getDouble(std::string, double, double);

std::string getString(std::string);


#endif /* utils_hpp */



