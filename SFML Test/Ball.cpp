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

void Ball::BallPosition(Ball& ball, Boolean& b, float& dx, float& dy, float& x, float& y, Player& player, float& gamespeed, int k)
{
	if (Keyboard::isKeyPressed(Keyboard::Space) || Mouse::isButtonPressed(Mouse::Right))
	{
		b.mball = false;
		dx = dx;
		dy = dy;
	}
	if (ball.sprite.getPosition().y >= 688)
	{
		b.mball = true;
		player.Lives(1);

	}
	if (b.mball && (k == 0))
	{
		ball.sprite.setPosition((player.sprite.getPosition().x + 
			(player.sprite.getSize().x / 2) - (ball.sprite.getSize().x / 2)), player.sprite.getPosition().y - 17);
		x = player.sprite.getPosition().x + 50;
		y = player.sprite.getPosition().y - 17;
	}
	if (b.pause && (k == 3) && !b.mball)
	{
		b.mball = true;
		x = x;
		y = y;
		ball.sprite.setPosition(x, y);
	}
	if (!b.mball)
	{
		if (!b.pause)
		{
			x += dx * gamespeed;
			y += dy * gamespeed;
		}
		ball.sprite.setPosition(x, y);

	}
	if ((ball.sprite.getPosition().x < 90 || ball.sprite.getPosition().x + ball.sprite.getScale().x>675)) dx = -dx;
	if ((ball.sprite.getPosition().y < 30 || ball.sprite.getPosition().y + ball.sprite.getScale().y>720))  dy = -dy;
}
