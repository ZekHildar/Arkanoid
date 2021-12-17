#include "NewLoader.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

	void NewLoader::settexture(Texture& texture,int posx, int sizex, int sizey, int texturenumberx, int i)
	{
		switch (i)
		{
		case 1:
		{
			sprite.setSize(Vector2f(sizex, sizey));
			sprite.setTexture(&texture);
			sprite.setTextureRect(IntRect(Vector2i(sizex * texturenumberx, 0), Vector2i(sizex, sizey)));
			break;
		}
		case 2:
		{
			sprite.setSize(Vector2f(sizex, sizey));
			sprite.setTexture(&texture);
			sprite.setTextureRect(IntRect(Vector2i(posx, 0), Vector2i(sizex, sizey)));
			break;
		}
		}

		
	}
	

