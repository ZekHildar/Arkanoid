#include "Ball.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


void Ball::scale(float scale)
{
	sprite.setSize(Vector2f(scale, scale));
}