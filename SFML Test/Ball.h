#pragma once
#include <SFML/Graphics.hpp>
#include "NewLoader.h"
#include "Block.h"
#include "Boolean.h"
#include "Player.h"

using namespace std;
using namespace sf;
class Ball : public NewLoader
{
	public:
		

		void scale(float scale);
		void BlockCollission(Block& block, float& dx, float& dy);
		void BallPosition(Ball& ball, Boolean& b, float& dx, float& dy, float& x, float& y, Player& player, float& gamespeed, int k);
};

