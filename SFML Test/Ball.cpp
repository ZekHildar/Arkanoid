#include "Ball.h"
#include "Block.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


void Ball::scale(float scale)
{
	sprite.setSize(Vector2f(scale, scale));
}
void Ball::BlockCollission(Block& block, float &dx, float &dy)
{
	float bax = sprite.getPosition().x;
	float bay = sprite.getPosition().y;
	float blx = block.sprite.getPosition().x;
	float bly = block.sprite.getPosition().y;
	if ((bay > bly + block.sprite.getSize().y - 8) || (bay + sprite.getSize().y < bly + 8))
	{
		dy = -dy;
		cout << "NO! Y!!" << endl;

	}
	if ((bax + sprite.getSize().x < blx + 8) || (bax > blx + block.sprite.getSize().x - 8))
	{
		dx = -dx;
		cout << "YES! X!!" << endl;
	}
}
