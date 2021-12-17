#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "NewLoader.h"
using namespace std;
using namespace sf;
class Player : public NewLoader
{
	private:
		int lives = 3;
		float x;
		int scale = 0;
		int score;
	public:
		int i = 0;
		Player() {
			score = 0;
			void GetPlayerCoords();
		}
		int Lives(int i);
		void GetPlayerCoords();
		int SetScore(int plusscore);
		int GetScore();
		void move(RenderWindow& game);
		void ResetScore();
};

