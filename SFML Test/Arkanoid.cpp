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
int LEVEL[8][11] = { 1, 2, 3, 4, 5, 6, 1,1, 1, 1, 0,
					0, 1, 1, 0, 1, 0, 0,1, 0, 1, 0,
					5, 2, 5, 0, 1, 5, 0,5, 5, 1, 3,
					6, 2, 1, 0, 1, 0, 0,1, 0, 1, 1,
					6, 2, 1, 4, 1, 0, 0,1, 0, 1, 1, 
					6, 1, 1, 0, 1, 0, 0,1, 0, 1, 0,
					6, 4, 4, 0, 6, 0, 0,3, 3, 1, 0, 
					5, 1, 1, 1, 1, 1, 1,1, 1, 1, 0, };
int seticon(RenderWindow &game)
{
	Image icon;
	if (!icon.loadFromFile("images/Ball.png"))
	{
		return 1;
	}
	game.setIcon(31, 31, icon.getPixelsPtr());
}
int setblocks(Block sprite[], RenderWindow &game, Texture &t1, Texture &t2, Texture& t3, Texture& t4, Texture& t5, Texture& t6)
{
	int k = 0;
	int z = 0;
	for (int i = 0; i<8; i++)
		for (int j = 0; j < 11; j++)
		{
			switch (LEVEL[i][j])
			{
			case 1:
				sprite[k].loadtexture(t1);
				sprite[k].sprite.setPosition(92 + 54 * j, 134 + 27 * i);
				z++;
				break;
			case 2:
				sprite[k].loadtexture(t2);
				sprite[k].sprite.setPosition(92 + 54 * j, 134 + 27 * i);
				z++;
				break;
			case 3:
				sprite[k].loadtexture(t3);
				sprite[k].sprite.setPosition(92 + 54 * j, 134 + 27 * i);
				z++;
				break;
			case 4:
				sprite[k].loadtexture(t4);
				sprite[k].sprite.setPosition(92 + 54 * j, 134 + 27 * i);
				z++;
				break;
			case 5:
				sprite[k].loadtexture(t5);
				sprite[k].sprite.setPosition(92 + 54 * j, 134 + 27 * i);
				z++;
				break;
			case 6:
				sprite[k].loadtexture(t6);
				sprite[k].type = 6;
				sprite[k].sprite.setPosition(92 + 54 * j, 134 + 27 * i);
				break;
			}
			
			/*if (j%2==0)
				sprite[k].setTexture(t1);
			else
				sprite[k].setTexture(t2);
			if (LEVEL[i][j] == 1)
			{
				sprite[k].setPosition(92 + 54 * j, 134 + 27 * i);
				game.draw(sprite[k]);
				
			}*/
			k++;
		}
	return z;
}
void AssetsLoader(Texture &tblock1, Texture& tblock2, Texture& tblock3, Texture& tblock4, Texture& tblock5, Texture& tblock6, Texture& tplayer, Texture& tball, Texture& tbackground, Texture& tframe, Texture& tPlay, Texture& tExit, Texture& tMenuBG, Texture& tLogo, Texture& tPlayActive, Texture& tExitActive, Font& font, Text& pScore)
{
	tblock1.loadFromFile("images/Block1.png");
	tblock2.loadFromFile("images/Block2.png");
	tblock3.loadFromFile("images/Block3.png");
	tblock4.loadFromFile("images/Block4.png");
	tblock5.loadFromFile("images/Block5.png");
	tblock6.loadFromFile("images/Block6.png");
	tplayer.loadFromFile("images/Player.png");
	tball.loadFromFile("images/Ball.png");
	tbackground.loadFromFile("images/Background2.png");
	tframe.loadFromFile("images/Frame2.png");
	tPlay.loadFromFile("images/kPlay.png");
	tPlayActive.loadFromFile("images/kPlayActive.png");
	tExit.loadFromFile("images/kExit.png");
	tExitActive.loadFromFile("images/kExitActive.png");
	tLogo.loadFromFile("images/Logo.png");
	tMenuBG.loadFromFile("images/menuBackground.png");
	font.loadFromFile("images/ARCADECLASSIC.TTF");
	
	pScore.setFont(font);
	pScore.setCharacterSize(50);
	pScore.setPosition(735, 117);
	pScore.setLineSpacing(0.55);
	pScore.setOutlineThickness(5);

}
int main()
{
	RenderWindow game(VideoMode(900, 720), "Arkanoid alpha");
	game.setFramerateLimit(60);

	Texture tblock1, tblock2, tblock3, tblock4, tblock5, tblock6, tplayer, tball, tbackground, tframe, tPlay, tExit, tMenuBG, tLogo, tPlayActive, tExitActive;
	Font font;
	Text pScore;
	AssetsLoader(tblock1, tblock2, tblock3, tblock4, tblock5, tblock6, tplayer, tball, tbackground, tframe, tPlay, tExit, tMenuBG, tLogo, tPlayActive, tExitActive, font, pScore);
	seticon(game);
	

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
	
	float ballscale = 0.8;
	float dx = 7, dy = -5;
	float x=200, y=1000;
	float gamespeed = 1;

	Sprite block[88];
	Block blocks[88];
	int z;
	z = setblocks(blocks, game, tblock1, tblock2, tblock3, tblock4, tblock5, tblock6);
	int score = 0;
	float grad = 0;
	int z2 = 0;
	player.score = 0;
	while (game.isOpen())
	{
		Event e;
		while (game.pollEvent(e))
		{
			if (e.type == Event::Closed)
				game.close();

			Vector2i pos = Mouse::getPosition(game);
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

			Logo.move(0, 0 + sin(grad)/3);
			grad = grad + 0.03;
			game.draw(MenuBG);
			game.draw(kPlay);
			game.draw(kExit);
			game.draw(Logo);
			game.display();
		}
		else if (b.play)
		{
			bool platforminvasion = true;
			string k = to_string(player.score);
			pScore.setString("SCORE\n"+k);
			ball.scale(0.8);
			for (int i = 0; i < 88; i++)
			{
				if (ball.sprite.getGlobalBounds().intersects(blocks[i].sprite.getGlobalBounds()))
				{
					float bax = ball.sprite.getPosition().x;
					float bay = ball.sprite.getPosition().y;
					float blx = blocks[i].sprite.getPosition().x;
					float bly = blocks[i].sprite.getPosition().y;
					cout << "//ball x: " << bax << endl;
					cout << "ball y: " << bay << endl << endl;
					cout << "block x: " << blx << endl;
					cout << "block y: " << bly << endl << endl;
					if (((bax + 31)*ballscale <= blx) || (bax*ballscale >= blx+54)) 
						dx = -dx;
					if (((bay+31)*ballscale>=bly)||(bay * ballscale <= bly+24))
						dy = -dy;
					//cout << "z: " << z << endl << "z2: " << z2+2 << endl;
					//if (platforminvasion == true)
					//{
					//	if (i % 2 == 0); //ball.scale(0.2);
					//	else if (i % 3 == 0) gamespeed = 1.3;
					//	else
					//	{
					//		//ball.scale(1.2);
					//		gamespeed = 1;
					//	}
					//	dy = -dy*1.1;
					//	platforminvasion = false;
					//}
					switch (blocks[i].type)
					{
					case 6:
					{
						break;
					}
					default:
					{
						player.score += 10;
						//cout << player.score << endl;
						blocks[i].sprite.setPosition(9999, 0);
						z2++;
					}
					}
					
					/*score = score + 10;
					cout << score << endl;
					blocks[i].sprite.setPosition(9999, 0);
					z2++;*/

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

			if /*(FloatRect(x, y, 31, 31).intersects(player.sprite.getGlobalBounds()))*/
				(player.sprite.getGlobalBounds().intersects(ball.sprite.getGlobalBounds()))
			{
				dy = -5; 
				platforminvasion = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)||Mouse::isButtonPressed(Mouse::Right)) b.mball = false;
			if (z == ((player.score/10)+1))
			{
				b.mball = true;
				ball.sprite.setPosition(player.sprite.getPosition().x + 42, player.sprite.getPosition().y - 31);
			}
			if (!b.mball) ball.sprite.setPosition(x, y);
			else ball.sprite.setPosition(player.sprite.getPosition().x + 42, player.sprite.getPosition().y - 31);


			
			game.draw(sBackground);
			game.draw(ball.sprite);
			game.draw(player.sprite);
			for (int i = 0; i < 88; i++)
				game.draw(blocks[i].sprite);
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
