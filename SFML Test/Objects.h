#pragma once
using namespace std;
class Player {
	Texture tplayer;
	public:
		float x;

		void get_coord()
		{
			cout << x << endl;
		}
		float leght;
		int identify;
		float y;
		int score;
		int health;
		int speed;
private:
	tplayer.loadFromFile("images/paddle.png");
	Sprite sPlayer(tplayer);
	sPlayer.setPosition(640, 620);
};
class Ball {
	public:
		float x;
		float y;
		int health;
		float size;
		int identify;
};
class Plate {
	public:
		int health;
		int identify;
};