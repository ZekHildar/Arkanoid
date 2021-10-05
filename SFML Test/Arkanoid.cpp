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
	sPlayer.setPosition(640, 690);
	sBall.setPosition(640, 500);
	sBall.setScale(0.7, 0.7);
	Player oPlayer;
	while (game.isOpen())
	{
		Event e;
		while (game.pollEvent(e))
		{
			if (e.type == Event::Closed)
				game.close();
		}
		sPlayer.getPosition().x;

		if (Keyboard::isKeyPressed(Keyboard::Right)&& (sPlayer.getPosition().x<1130)) sPlayer.move(15, 0);
		if (Keyboard::isKeyPressed(Keyboard::Left)&&(sPlayer.getPosition().x>0)) sPlayer.move(-15, 0);
		game.draw(sBackground);
		//game.draw(oPlayer.texture());
		game.draw(sPlayer);
		game.draw(sBall);
		game.display();
	}
	return 0;
}
