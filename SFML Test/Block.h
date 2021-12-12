#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Loader.h"
using namespace std;
using namespace sf;

class Block : public Loader
{
	public:
		int type;
		int health;
};

