#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "Objects.h"
using namespace std;
using namespace sf;

int main()
{
	RenderWindow game(VideoMode(1280, 720), "Arkanoid alpha");
	game.setFramerateLimit(60);
	// t = texture
	Texture tblock1, tblock2, tblock3, tplayer, tball, tbackground;
	tblock1.loadFromFile("images/block01.png");
	tblock2.loadFromFile("images/block02.png");
	tblock3.loadFromFile("images/block03.png");
	tplayer.loadFromFile("images/paddle.png");
	tball.loadFromFile("images/ball.png");
	tbackground.loadFromFile("images/background.jpg");

	Sprite sPlayer(tplayer), sBall(tball), sBackground(tbackground);
	sPlayer.setPosition(640, 620);
	sBall.setPosition(640, 500);
	Player oPlayer
	while (game.isOpen())
	{
		Event e;
		while (game.pollEvent(e))
		{
			if (e.type == Event::Closed)
				game.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) sPlayer.move(10, 0);
		if (Keyboard::isKeyPressed(Keyboard::Left)) sPlayer.move(-10, 0);
		game.draw(sBackground);
		game.draw(oPlayer);
		game.draw(sBall);
		game.display();
	}
	return 0;
}
