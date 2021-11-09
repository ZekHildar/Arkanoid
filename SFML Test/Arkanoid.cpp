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
	bool menu = true;
	bool play = false;
};
int LEVEL[8][11] = { 0, 1, 1, 1, 1, 1, 1,1, 1, 1, 0,
					0, 1, 1, 0, 1, 0, 0,1, 0, 1, 0,
					0, 1, 1, 0, 1, 0, 0,1, 0, 1, 0,
					1, 1, 1, 0, 1, 0, 0,1, 0, 1, 1,
					1, 1, 1, 0, 1, 0, 0,1, 0, 1, 1, 
					0, 1, 1, 0, 1, 0, 0,1, 0, 1, 0,
					0, 1, 1, 0, 1, 0, 0,1, 0, 1, 0, 
					0, 1, 1, 1, 1, 1, 1,1, 1, 1, 0, };
int seticon(RenderWindow &game)
{
	Image icon;
	if (!icon.loadFromFile("images/Ball.png"))
	{
		return 1;
	}
	game.setIcon(31, 31, icon.getPixelsPtr());
}
void setblocks(Sprite sprite[], RenderWindow &game, Texture &t1, Texture &t2)
{
	int k = 0;
	for (int i = 0; i<8; i++)
		for (int j = 0; j < 11; j++)
		{
			if (j%2==0)
				sprite[k].setTexture(t1);
			else
				sprite[k].setTexture(t2);
			if (LEVEL[i][j] == 1)
			{
				sprite[k].setPosition(92 + 54 * j, 134 + 27 * i);
				game.draw(sprite[k]);
				
			}
			k++;
		}
}

int main()
{
	RenderWindow game(VideoMode(900, 720), "Arkanoid alpha");
	game.setFramerateLimit(60);

	Texture tblock1, tblock2, tblock3, tplayer, tball, tbackground, tframe, tPlay, tExit, tMenuBG, tLogo, tPlayActive, tExitActive;
	tblock1.loadFromFile("images/Block1test.png");
	tblock2.loadFromFile("images/Block2test.png");
	tblock3.loadFromFile("images/Block3.png");
	tplayer.loadFromFile("images/Player.png");
	tball.loadFromFile("images/Ball.png");
	tbackground.loadFromFile("images/Background.png");
	tframe.loadFromFile("images/Frame.png");
	tPlay.loadFromFile("images/kPlay.png");
	tPlayActive.loadFromFile("images/kPlayActive.png");
	tExit.loadFromFile("images/kExit.png");
	tExitActive.loadFromFile("images/kExitActive.png");
	tLogo.loadFromFile("images/Logo.png");
	tMenuBG.loadFromFile("images/menuBackground.png");
	seticon(game);
	Font font;
	font.loadFromFile("images/ARCADECLASSIC.TTF");
	Text pScore;
	pScore.setFont(font);
	pScore.setCharacterSize(50);
	pScore.setPosition(735, 117);
	pScore.setLineSpacing(0.55);

	Sprite sBackground(tbackground), sFrame(tframe), kPlay(tPlay), kExit(tExit), MenuBG(tMenuBG), Logo(tLogo);
	Player player;
	Ball ball;
	Boolean b;
	
	Logo.setPosition(53, 60);
	kPlay.setPosition(321, 414);
	kExit.setPosition(321, 530);

	player.loadtexture(tplayer);
	player.sprite.setTexture(tplayer);
	ball.loadtexture(tball);
	ball.scale(1);
	
	float ballscale = 1;
	float dx = 7, dy = -5;
	float x=200, y=1000;
	float gamespeed = 1;

	Sprite block[88];
	setblocks(block, game, tblock1, tblock2);
	int score = 0;
	float grad = 0;
	while (game.isOpen())
	{
		Event e;
		while (game.pollEvent(e))
		{
			if (e.type == Event::Closed)
				game.close();

			Vector2i pos = Mouse::getPosition(game);
			/*if (b.menu && pos.x >= 321 && pos.x <= 579 && pos.y >= 414 && pos.y <= 504) kPlay.setTexture(tPlayActive);
			else kPlay.setTexture(tPlay);
			if (b.menu && pos.x >= 321 && pos.x <= 579 && pos.y >= 530 && pos.y <= 620) kExit.setTexture(tExitActive);*/
			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
				{
					if (b.menu)
					{
						if (pos.x >= 321 && pos.x <= 579 &&
							pos.y >= 530 && pos.y <= 620)
							game.close();
						else if (pos.x >= 321 && pos.x <= 579 &&
							pos.y >= 414 && pos.y <= 504)
							b.menu = false;
							b.play = true;
					}
				}
		}
		if (b.menu)
		{
			Vector2i pos = Mouse::getPosition(game);
			if (b.menu && pos.x >= 321 && pos.x <= 579 && pos.y >= 414 && pos.y <= 504)
			{
				kPlay.setTexture(tPlayActive);
				cout << "Active!" << endl;
			}
			else kPlay.setTexture(tPlay);
			if (b.menu && pos.x >= 321 && pos.x <= 579 && pos.y >= 530 && pos.y <= 620) kExit.setTexture(tExitActive);
			else kExit.setTexture(tExit);

			Logo.move(0, 0 + sin(grad)/4);
			grad = grad + 0.01;
			//cout << grad << endl;
			//cout << sin(grad) << endl;
			game.draw(MenuBG);
			game.draw(kPlay);
			game.draw(kExit);
			game.draw(Logo);
			game.display();
		}
		else if (b.play)
		{
			bool platforminvasion = true;
			string k = to_string(score);
			pScore.setString("SCORE\n"+k);

			for (int i = 0; i < 88; i++)
			{
				if (ball.sprite.getGlobalBounds().intersects(block[i].getGlobalBounds()))
				{
					if (platforminvasion == true)
					{
						dy = -dy;
						platforminvasion = false;
					}
					score = score + 10;
					cout << score << endl;
					block[i].setPosition(9999, 0);
				}
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

			if (FloatRect(x, y, 11, 11).intersects(player.sprite.getGlobalBounds()))
			{
				dy = -5;
				platforminvasion = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) b.mball = false;

			if (!b.mball) ball.sprite.setPosition(x, y);
			else ball.sprite.setPosition(player.sprite.getPosition().x + 42, player.sprite.getPosition().y - 31);


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
			for (int i = 0; i < 88; i++)
				game.draw(block[i]);
			game.draw(sFrame);
			game.draw(pScore);
			game.display();
		}
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
