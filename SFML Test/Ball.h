#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class Ball
{
	public:
		RectangleShape sprite;
		void settexture(Texture& texture);
		void changetexture(Texture& texture);
		void scale(float scale);
};

