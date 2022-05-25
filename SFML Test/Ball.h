#pragma once
#include <SFML/Graphics.hpp>
#include "NewLoader.h"
#include "Block.h"
using namespace std;
using namespace sf;
class Ball : public NewLoader
{
	public:
		void scale(float scale);
		void BlockCollission(Block& block, float& dx, float& dy);
};

