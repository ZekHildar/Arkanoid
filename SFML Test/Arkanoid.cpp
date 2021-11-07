#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "Objects.h"
#include "Player.h"
using namespace std;
using namespace sf;
class Boolean {
public: 
	bool mball = true;
};

int seticon(RenderWindow &game)
{
	Image icon;
	if (!icon.loadFromFile("images/Ball.png"))
	{
		return 1;
	}
	game.setIcon(31, 31, icon.getPixelsPtr());
}
void setblocks(Sprite sprite[], RenderWindow &game, Texture &t1)
{
	for (int i = 0; i<3; i++)
		for (int j = 0; j < 11; j++)
		{
			sprite[i * j + i + j].setTexture(t1);
			sprite[i*j+i+j].setPosition(274 + 40 * j, 0 + j * 20);
			game.draw(sprite[i * j + i + j]);
		}
}
int main()
{
	RenderWindow game(VideoMode(900, 720), "Arkanoid alpha");
	game.setFramerateLimit(60);

	Texture tblock1, tblock2, tblock3, tplayer, tball, tbackground, tframe;
	tblock1.loadFromFile("images/block01.png");
	tblock2.loadFromFile("images/block02.png");
	tblock3.loadFromFile("images/block03.png");
	tplayer.loadFromFile("images/Player.png");
	tball.loadFromFile("images/Ball.png");
	tbackground.loadFromFile("images/Background.png");
	tframe.loadFromFile("images/Frame.png");

	seticon(game);

	Sprite sBackground(tbackground), sFrame(tframe);
	Player player;
	Ball ball;
	Boolean b;

	player.loadtexture(tplayer);
	player.sprite.setTexture(tplayer);
	ball.loadtexture(tball);
	ball.scale(1);
	
	float ballscale = 1;
	float dx = 7, dy = -5;
	float x=200, y=1000;
	float gamespeed = 1.5;

	Sprite testplatform[1000];
	setblocks(testplatform, game, tblock1);

	while (game.isOpen())
	{
		Event e;
		while (game.pollEvent(e))
		{
			if (e.type == Event::Closed)
				game.close();
		}
		player.move(game);
		if (ball.sprite.getPosition().y >= 700)
		{
			b.mball = true;
			dx = 6;
			dy = -5;
			x = player.sprite.getPosition().x + 42;
			y = player.sprite.getPosition().y - 31;
		}
		else {
			x += dx * gamespeed;
			y += dy * gamespeed;
		}
		if (x < 90 || x>660)  dx = -dx;
		if (y < 28 || y>720)  dy = -dy;

		if (FloatRect(x, y, 12, 12).intersects(player.sprite.getGlobalBounds())) dy = -5;
		if (Keyboard::isKeyPressed(Keyboard::Space)) b.mball = false;

		if (!b.mball) ball.sprite.setPosition(x, y);
		else ball.sprite.setPosition(player.sprite.getPosition().x+42, player.sprite.getPosition().y - 31);
		

		//if (ball.sprite.getPosition().y >= 700)
		//{
		//	b.mball = true;
		//	dx = 6;
		//	dy = -5;
		//	x = player.sprite.getPosition().x + 42;
		//	y = player.sprite.getPosition().y - 31;
		//}
		game.draw(sBackground);
		game.draw(ball.sprite);
		game.draw(player.sprite);
		game.draw(sFrame);
		for (int i = 0; i < 1000; i++)
			game.draw(testplatform[i]);
		game.display();
	}
	return 0;
}



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@ & %%%%&@@@@@@@@@@@@@@@@@@@@@@@@@@ % %%##@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@ & %%%%%# % &%%%%#@@@@@@@@@@@@@@@@@@@ & %%%%%%###(@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@ & %%##### % %%##(/ @@@@@@@@@@@@@@ & %%%%##(((((///#@@@@&&&&@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@ & ##(((((((//*/@@@@@@@@@@@@@%#######(((((/*(&&&@@@@@@@@@@@@@&&&&@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@& (/////***/(&@@@@@@@@&%%%%%#((((////***&&&@@@&&&&&&&@&@@@@@@@@&%%&@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@#((/****///(#@@@@@%%%%%%##(////***/%&&&&&&&&&&&&&&&&&&&&&&&&&@&&%#&@@@@@@@@@@@@@@
//@@@@@@@@@ % %%&%%&@@###///*****/(((%@&%%%%#((##((//(#%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&@&&%%#&@@@@@@@@@@
//@@@@@@@ % %%%%&%%%%%####(((//(((((((#&%%%/###(/**/(%%%%&&&&&%%%##%##%&&&%%%##%%%&&&&&%&%%%#&@@@@@@@@
//@@@@@@## % %%%%%%%%%%%%%%#(///(((////(#/(####///(/%%%%%&&%%###((((#((%&%(((((((#%%&&&&&%%%%##@@@@@@@
//@@@@@@@#### % # % %%# % &&&&%%#///**/*//(##((##//%%%%&&&&%%#((((///(%((&#(///((((#%%&&&&%%%%##@@@@@@
//@@@@@@@@@#(((#### % %%%###(/****/*******//(#((/#%%%%&&&&&%#((##/,.,/((%%(*,.,/##((#%&&&&&&%%%#&@@@@@
//@@@@@@@@@ & ##//*(##(###(///*******//((((#((//##%%%%%&&&&&%##((##((####%%(((((((##%&&&&&&&%%%#%@@@@@
//@@@@@@@@@# % ##((//////////,****//((((((((//(@##%%%%&&&&&&&&&%#((((#%&@&#(((((#%&&&&&&&&&%%%%#%@@@@@
//@@@@@&%%%&%% (//////*********//((((((((///@@@##(%%%%&&&&&&&&&&&&&&@@@@@@@@@&&&&&&&&&&&&&%%%#(&@@@@@@
//@@@@## % %%%%%%#(///((/**//////(((((////*%@@@@%#(%%%%&&&&&&&&&&@@@@@@@&&&@@&&&&&&&&&&&%%%%##((@@@@@@
//@@@@ % # % %%%%%%%%%## / ((//((((((////*///&@@@@@(@%(###(////((((((((((((((((((((((/((#%%###((&@@@@@
//@@@@@ & ((### % ## % %%%%%(/ (//((/(////*#@@@@@@@@(@@%((((((((((((((((((((((((((((((((####((#&@@@@@@
//@@@@ % %####### % &%%%%#(///(((//*(@@@@@@@@@@@@@@@@(&(####%%%%%%%&&&&&&&&&&%%%%%%#######((#@@@@@@@@@
//@@@@ % %%%%#(((####((///(((//%@@@@@@@@@@@@@@@@@@@@@@((######%%%%%%%%%%%%%%%%%%######((/#@@@@@@@@@@@@
//@@@@# % %%####//////((/((///@@@@@@@@@@@@@@@@@@@@@@@@@&#(((############%#########(((/(&@@@@@@@@@@@@@@
//@@@ & %%%%###(/***////((//%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&(((((((###########(((((%@@@@@@@@@@@@@@@@@@
//@@@# % &&%%#(/*****,*/**&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ & ###((((((## % %&@@@@@@@@@@@@@@@@@@@
//@@@# % %%%##(/ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@ % %%%%#(@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@ % %%%## / @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ % # % ##/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@&(#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
