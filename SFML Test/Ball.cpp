#include "Ball.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

void Ball::settexture(Texture& texture)
{
	sprite.setSize(Vector2f(16, 16));
	sprite.setTexture(&texture);
	sprite.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(16, 16)));
}
void Ball::changetexture(Texture& texture)
{
	sprite.setSize(Vector2f(16, 16));
	sprite.setTexture(&texture);
	sprite.setTextureRect(IntRect(Vector2i(16, 0), Vector2i(16, 16)));
}
void Ball::scale(float scale)
{
	/*sprite.setScale(scale, scale);*/
	//sprite.setSize(Vector2f(scale, scale));
}