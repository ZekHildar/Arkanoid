#pragma once
using namespace std;
class Player {
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