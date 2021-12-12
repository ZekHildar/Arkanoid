#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Loader.h"
using namespace std;
using namespace sf;
class Player : public Loader
{
	private:
		int scale = 0;
		int score;
	public:
		int i = 0;
		Player() {
			score = 0;
		}
		int SetScore(int plusscore);
		int GetScore();
		void move(RenderWindow& game);
};

