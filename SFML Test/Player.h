#pragma once
using namespace std;
using namespace sf;

class Loader {
public:
	Sprite sprite;
	/*RectangleShape sprite;*/
	/*Loader(int x, int y)
	{
		sprite.setSize(Vector2f(x, y));
	}*/
	void loadtexture(Texture &texture)
	{
		sprite.setTexture(texture);
	}
};
class Player : public Loader {
private:
	int scale = 0;
	int score;
public:
	int i = 0;
	Player(){
		score = 0;
	}
	int SetScore(int plusscore)
	{
		score += plusscore;
		cout << "score: " <<score << endl;
		return score;
	}
	int GetScore()
	{
		return score;
	}
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
class Ball {
public:
	RectangleShape sprite;
	void settexture(Texture& texture)
	{
		sprite.setSize(Vector2f(16, 16));
		sprite.setTexture(&texture);
		sprite.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(16, 16)));
	}
	void changetexture(Texture& texture)
	{
		sprite.setSize(Vector2f(16, 16));
		sprite.setTexture(&texture);
		sprite.setTextureRect(IntRect(Vector2i(16, 0), Vector2i(16, 16)));
	}
	void scale(float scale)
	{
		/*sprite.setScale(scale, scale);*/
		//sprite.setSize(Vector2f(scale, scale));
	}
};

class Block : public Loader {
public:
	int type;
	int health;
};