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
int Player::GetScore()
{
	return score;
}
void Player::move(RenderWindow& game)
{
	sprite.getPosition().x;
	Vector2i mouse = Mouse::getPosition(game);
	if ((float)mouse.x < 576 && (float)mouse.x>90)
		sprite.setPosition((float)mouse.x, 670);
}