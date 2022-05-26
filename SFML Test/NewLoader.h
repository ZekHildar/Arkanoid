#pragma once
#include <SFML/Graphics.hpp>



using namespace std;
using namespace sf;
class NewLoader
{
public:
	RectangleShape sprite;
	void settexture(Texture& texture, int posx, int sizex, int sizey, int texturenumberx, int i);
};
