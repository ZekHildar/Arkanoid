#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "NewLoader.h"


using namespace std;
using namespace sf;

class Block : public NewLoader
{
	public:
		int type;
		int health=1;
		void changehealth();
		void collision(	);
		void SetBlocks(int i, int j, int(&LEVEL)[8][11], Texture& tNewBlocks, int& z);
};

