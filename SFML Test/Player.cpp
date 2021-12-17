#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
using namespace std;
using namespace sf;

int Player::SetScore(int plusscore) 
{
	score += plusscore;
	cout << "score: " << score << endl;
	return score;
}
void Player::ResetScore()
{
	score = 0;
}
int Player::GetScore()
{
	return score;
}
void Player::GetPlayerCoords()
{
	x = sprite.getPosition().x;
}
void Player::move(RenderWindow& game)
{
	Vector2i mouse = Mouse::getPosition(game);
	if (((float)mouse.x < 693  -sprite.getSize().x) && (float)mouse.x>90)
		sprite.setPosition((float)mouse.x, 670);
}

int Player::Lives(int i)
{
	if (i == 1) lives -= 1;
	if (i == 3) lives = 3;
	return lives;
}