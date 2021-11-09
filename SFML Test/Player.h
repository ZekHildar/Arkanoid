#pragma once
using namespace std;
using namespace sf;

class Loader {
public:
	Sprite sprite;
	void loadtexture(Texture &texture)
	{
		sprite.setTexture(texture);
	}
};
class Player : public Loader {
public:
	float xcoord, scale;
	int score;
	int i = 0;
	void move(RenderWindow &game)
	{
		sprite.getPosition().x;
		Vector2i mouse = Mouse::getPosition(game);
		if ((float)mouse.x < 576 && (float)mouse.x>90)
		sprite.setPosition((float)mouse.x, 670);
		/*cout << "y: "<< mouse.y << endl;
		cout << "x: "<<mouse.x << endl;*/
	}
private:
	
};
class Ball : public Loader {
public:
	void scale(float scale)
	{
		sprite.setScale(scale, scale);
	}
};