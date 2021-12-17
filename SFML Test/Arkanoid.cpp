#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include "Player.h"
#include "Loader.h"
#include "Ball.h"
#include "Block.h"
#include "Bonus.h"
using namespace std;
using namespace sf;
class Boolean {
public: 
	bool mball = true;
	bool menu = true;
	bool leaders = false;
	bool play = false;
	bool pause = false;
	bool gameover = false;
	bool entername = false;
	bool textentering = false;
	bool bonus = false;
	bool bonusfalling = false;
};
Text pScore;
Text Pause;
Text GameOver;
Text EnterName;
Text LeadersNames;
string str;
sf::String name;
ofstream fout;          // поток для записи

int z;
int k = 0;
Event p;
float PI = 3.14159;
inline float to_radians(float degrees)
{
	return degrees * PI / 180;
}
inline float to_degrees(float radians)
{
	// Normalize between 0 and 360
	float degrees = int(radians / PI * 180) % 360;
	return degrees < 0 ? degrees + 360 : degrees;
}
inline float angle(const sf::Vector2f& a, const sf::Vector2f& b = sf::Vector2f(0.f, 0.f))
{
	// Y-axis is flipped
	return std::atan2(b.y - a.y, b.x - a.x);
}

struct leaders
{
	string names;
	int scores;
	leaders(string n, int s) : names(n), scores(s)
	{}
	
};
void LeadersNamesSetting(Font& font, vector<leaders>& new_operations)
{
	LeadersNames.setFont(font);
	LeadersNames.setCharacterSize(50);
	string players;

	for (int i = 0; i < new_operations.size(); i++)
	{
		players += new_operations[i].names;
		players += "    ";
		players += to_string(new_operations[i].scores);
		players += "  POINTS\n";
	}
	LeadersNames.setString(players);
	LeadersNames.setPosition(450 - LeadersNames.getGlobalBounds().width / 2, 360 - LeadersNames.getGlobalBounds().height / 2 - 20);
	LeadersNames.setLineSpacing(1);
	LeadersNames.setOutlineThickness(10);
	/*for (int i = 0; i < new_operations.size(); i++)
	{
		players += new_operations[i].names;
		players += to_string(new_operations[i].scores);
		players += "\n";
	}
	LeadersNames.setString(players);*/
}
void EnterNameText(Font& font, string text)
{
	EnterName.setFont(font);
	EnterName.setCharacterSize(100);
	EnterName.setPosition(450 - EnterName.getGlobalBounds().width / 2, 360 - EnterName.getGlobalBounds().height / 2 - 20);
	EnterName.setLineSpacing(0.55);
	EnterName.setOutlineThickness(10);
	EnterName.setString(text);
}
void PauseText(Font &font)
{
	Pause.setFont(font);
	Pause.setCharacterSize(100);
	Pause.setPosition(304, 290);
	Pause.setLineSpacing(0.55);
	Pause.setOutlineThickness(10);
	Pause.setString("PAUSE");
}
void GameOverText(Font& font, String str)
{
	GameOver.setFont(font);
	GameOver.setCharacterSize(100);
	GameOver.setPosition(213, 290);
	GameOver.setLineSpacing(0.55);
	GameOver.setOutlineThickness(10);
	GameOver.setString(str);
}
int LEVEL[8][11] = { 0, 0, 2, 2, 2, 2, 2,2, 2, 0, 0,
					0, 1, 3, 3, 3, 3, 3, 3, 3, 1, 0,
					0, 1, 3, 4, 4, 4, 4, 4, 3, 1, 0,
					0, 1, 3, 4, 5, 5, 5, 4, 3, 1, 0,
					0, 1, 3, 4, 5, 5, 5, 4, 3, 1, 0,
					0, 1, 3, 4, 4, 4, 4, 4, 3, 1, 0,
					0, 1, 3, 3, 3, 3, 3, 3, 3, 1, 0,
					0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, };
int BONUS[88];
void BonusAdder()
{
	int a;
	for (int i = 0; i < 88; i++)
		{
			a = rand() % 10 + 1;
			if ((a < 4)&&(a>0)) BONUS[i] = a;
			else  BONUS[i] = 0;
		}
	for (int i = 0; i < 88; i++) cout << BONUS[i] << " ";
}
void moveBonus(Bonus& bonus)
{
	bonus.sprite.setPosition(bonus.sprite.getPosition().x, bonus.sprite.getPosition().y+5);
}
int seticon(RenderWindow &game)
{
	Image icon;
	if (!icon.loadFromFile("images/Ball.png"))
	{
		return 1;
	}
	game.setIcon(31, 31, icon.getPixelsPtr());
}
int setblocks(Block sprite[], RenderWindow &game, Texture &t1, Texture &t2, Texture& t3, Texture& t4, Texture& t5, Texture& t6, Texture &tNewBlocks)
{
	int k = 0;
	int z = 0;
	for (int i = 0; i<8; i++)
		for (int j = 0; j < 11; j++)
		{
			switch (LEVEL[i][j])
			{
			case 1:
				sprite[k].settexture(tNewBlocks,0, 54, 27, LEVEL[i][j]-1, 1);
				sprite[k].sprite.setPosition(92 + 54 * j, 134 + 27 * i);
				z++;
				break;
			case 2:
				sprite[k].settexture(tNewBlocks,54, 54, 27, LEVEL[i][j] - 1, 1);
				sprite[k].sprite.setPosition(92 + 54 * j, 134 + 27 * i);
				z++;
				break;
			case 3:
				sprite[k].settexture(tNewBlocks, 108,54, 27, LEVEL[i][j] - 1, 1);
				sprite[k].sprite.setPosition(92 + 54 * j, 134 + 27 * i);
				z++;
				break;
			case 4:
				sprite[k].settexture(tNewBlocks, 162, 54, 27, LEVEL[i][j] - 1, 1);
				sprite[k].sprite.setPosition(92 + 54 * j, 134 + 27 * i);
				z++;
				break;
			case 5:
				sprite[k].settexture(tNewBlocks, 216, 54, 27, LEVEL[i][j] - 1, 1);
				sprite[k].sprite.setPosition(92 + 54 * j, 134 + 27 * i);
				z++;
				break;
			case 6:
				sprite[k].settexture(tNewBlocks, 270, 54, 27, LEVEL[i][j] - 1,1);
				sprite[k].type = 6;
				sprite[k].sprite.setPosition(92 + 54 * j, 134 + 27 * i);
				break;
			}
			k++;
		}
	return z;
}
void BlockBounds(Ball& ball, Block(&blocks)[88], float ballscale, float& dx, float& dy, int *z2, Player &player, Texture &t, Texture &tBonus, Bonus &bonus, Boolean &b)
{
	if (b.bonusfalling) moveBonus(bonus);
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
			
			const sf::Vector2f ballCenter(
				ball.sprite.getPosition().x +ball.sprite.getScale().x / 2,
				ball.sprite.getPosition().y +ball.sprite.getScale().y / 2
			);
			const sf::Vector2f brickCenter(
				blocks[i].sprite.getPosition().x + 27,
				blocks[i].sprite.getPosition().y + 13.5
			);
			float ballAngle = to_degrees(angle(ballCenter, brickCenter));

			// Get brick ratio angle
			float brickRatio = to_degrees(
				std::tan(static_cast<float>(27) / 54)
			);
			if ((ballAngle > brickRatio && ballAngle < (180 - brickRatio)) ||
				(ballAngle > 180 + brickRatio && ballAngle < (360 - brickRatio)))
			{
				// Vertical side, flip Y-axis
				dx = -dx;
			}
			else
			{
				// Horizontal side, flip X-axis
				dx = PI - dx;
			}
			//{
			//	// Vertical side, flip Y-axis
			//	dy = -dy;
			//}
			//else
			//{
			//	// Horizontal side, flip X-axis
			//	dx = - dx;
			//}
			/*if ((bay<bly)&&((bax + 16 >= blx)|| (blx + 54 <= bax))) dx = -dx;
			if ((bax > blx) && ((bay + 16 >= bly) || (bay -27 <= bly))) dy = -dy;*/
			/*if (((bay + 16 >= bly) && (bax > blx)) || 
			((bax > blx) && (bay + 16 >= bly))) dy = -dy;*/
			/*if (((bax + 16) >= blx) && ((bax + 16) < blx + 54) || ((bay <= bly + 27) && ((bay - 16) >= bly)))
				{
					dx = -dx;
					cout << "YES! X!!" << endl;
				}
			else
				{
					dy = -dy;
					cout << "NO! Y!!" << endl;
				}*/
			switch (blocks[i].type)
			{
			case 6:
				{
					break;
				}
			default:
				{
				if ((BONUS[i] > 0) && (BONUS[i] < 4)&!b.bonus)
				{
					cout << "//////////////////////    " << BONUS[i] << endl;
					bonus.type = BONUS[i];
					bonus.SetBonus(BONUS[i], tBonus);
					b.bonusfalling = true;
					b.bonus = true;
					bonus.sprite.setPosition(blx, bly);
					moveBonus(bonus);
				}
				
					player.SetScore(10);
					blocks[i].sprite.setPosition(9999, 0);
					z2++;
				}
			}
		}
	}
}
void AssetsLoader(Texture &tblock1, Texture& tblock2, Texture& tblock3, Texture& tblock4, Texture& tblock5, Texture& tblock6, Texture& tplayer, Texture& tball, Texture& tbackground, Texture& tframe, Texture& tPlay, Texture& tExit, Texture& tMenuBG, Texture& tLogo, Texture& tPlayActive, Texture& tExitActive, Font& font, Text& pScore, Texture &tLeaders, Texture &tLeadersActive, Texture& tPause, Texture& tPauseActive, Texture &tPauseScreen, Texture &tLife, Texture &tNewBlocks, Texture &tBonus)
{
	tblock1.loadFromFile("images/Block1.png");
	tblock2.loadFromFile("images/Block2.png");
	tblock3.loadFromFile("images/Block3.png");
	tblock4.loadFromFile("images/Block4.png");
	tblock5.loadFromFile("images/Block5.png");
	tblock6.loadFromFile("images/Block6.png");
	/*tplayer.loadFromFile("images/Player.png");*/
	tplayer.loadFromFile("images/newpaddles.png");
	tball.loadFromFile("images/Balls.png");
	tbackground.loadFromFile("images/Background.png");
	tframe.loadFromFile("images/Frame2.png");
	tPlay.loadFromFile("images/kPlay.png");
	tPlayActive.loadFromFile("images/kPlayActive.png");
	tExit.loadFromFile("images/kExit.png");
	tExitActive.loadFromFile("images/kExitActive.png");
	tLeaders.loadFromFile("images/kLeaders.png");
	tLeadersActive.loadFromFile("images/kLeadersActive.png");
	tPause.loadFromFile("images/kPause.png");
	tPauseActive.loadFromFile("images/kPauseActive.png");
	tLogo.loadFromFile("images/Logo.png");
	tMenuBG.loadFromFile("images/menuBackground.png");
	tPauseScreen.loadFromFile("images/PauseScreen.png");
	font.loadFromFile("images/ARCADECLASSIC.TTF");
	tLife.loadFromFile("images/life.png");
	tNewBlocks.loadFromFile("images/Blocks.png");
	tBonus.loadFromFile("images/bonus.png");
	pScore.setFont(font);
	pScore.setCharacterSize(50);
	pScore.setPosition(745, 117);
	pScore.setLineSpacing(0.55);
	pScore.setLetterSpacing(0.01);
	pScore.setOutlineThickness(5);
	
	
	/*pScore.setColor(Color())*/

}
void DrawObjects(RenderWindow& game, Sprite sBackground, RectangleShape &ball, RectangleShape &player, Block(&blocks)[88], Sprite &sFrame, Text &pScore, Sprite &kPause, Boolean &b, Sprite &PauseScreen, Sprite (&Life)[3], Player oplayer, Bonus &bonus)
{
	game.draw(sBackground);
	game.draw(ball);
	game.draw(player);
	for (int i = 0; i < 88; i++)
		game.draw(blocks[i].sprite);
	game.draw(sFrame);
	game.draw(pScore);
	game.draw(kPause);
	for (int i = 0; i < oplayer.Lives(2); i++)
	{
		game.draw(Life[i]);
	}
	if (b.bonusfalling) game.draw(bonus.sprite);
	
	if (b.gameover)
	{
		game.draw(PauseScreen);
		if (!b.entername)
		{
			game.draw(GameOver);
		}
		else if (!b.textentering) game.draw(EnterName);
	}
	if (b.pause&& (oplayer.Lives(2) > 0))
	{
		game.draw(PauseScreen);
		game.draw(Pause);
	}
	
	game.display();
}
void LeaderBoardMenu(Boolean& b, RenderWindow& game, Sprite& background, Event &e)
{
	
	game.draw(background);
	game.draw(LeadersNames);
	game.display();
	
}
void LeaderBoard(Boolean& b, RenderWindow& game, vector<leaders>& new_operations, Font&font)
{
	string names;
	int scores;
	std::ifstream in("highscores.txt"); // окрываем файл для чтения
	if (in.is_open())
	{
		while (in >> names >> scores)
		{
			new_operations.push_back(leaders(names, scores));
		}
	}
	in.close();     // закрываем файл
	for (int i = 0; i < new_operations.size(); i++)
	{
		std::cout << new_operations[i].names << " - " << new_operations[i].scores << std::endl;
	}
	LeadersNamesSetting(font, new_operations);
}
void AnalyzeMenu(RenderWindow &game, Event &e, Boolean &b, Font &font, vector<leaders>& new_operations, Sprite& MenuBG, float& texttimer)
{
	Vector2i pos = Mouse::getPosition(game);
	if (e.type == Event::MouseButtonPressed)
		if (e.key.code == Mouse::Left)
		{
			if (b.leaders && texttimer > 2000)
			{
				if (pos.x >= 0 && pos.x <= 900 && pos.y >= 0 && pos.y <= 720)
				{
					b.leaders = false;
					b.menu = true;
				}
				texttimer = 0;
			}
			if (b.menu && texttimer > 2000)
			{
				
				if (pos.x >= 321 && pos.x <= 579 && pos.y >= 566 && pos.y <= 656) game.close();
				else if (pos.x >= 321 && pos.x <= 579 && pos.y >= 463 && pos.y <= 553)
				{
					b.menu = false;
					b.leaders = true;
					LeaderBoard(b, game, new_operations, font);
					LeaderBoardMenu(b, game, MenuBG, e);
				}
				else if (pos.x >= 321 && pos.x <= 579 && pos.y >= 360 && pos.y <= 450)
				{
					b.menu = false;
					b.play = true;
				}
				texttimer = 0;
			}
			
			if (b.play && b.pause)
			{
					if (pos.x >= 0 && pos.x <= 900 &&
						pos.y >= 0 && pos.y <= 720)
					{
						b.mball = false;
						b.pause = false;
						k = 0;
						PauseText(font);
					}
			}
			if (b.play &! b.pause)
			{
				if (pos.x >= 793 && pos.x <= 884 &&
					pos.y >= 13 && pos.y <= 104)
				{
					b.pause = true;
					k = 3;
					PauseText(font);
				}
			}
			
			
		}
}
void AnalyzeEvent(Event &e, RenderWindow &game, Boolean &b, Font &font, vector<leaders>& new_operations, Sprite &MenuBG, float &menutimer)
{
	while (game.pollEvent(e))
	{
		if (e.type == Event::Closed)
			game.close();
		AnalyzeMenu(game, e, b, font, new_operations, MenuBG, menutimer);
	}
}
void Menu(Boolean &b,RenderWindow& game, Sprite& kPlay, Sprite& kExit, Texture& tPlayActive, Texture& tPlay, Texture& tExit, Sprite& MenuBG, float &grad, Sprite &Logo, Texture &tExitActive, Sprite &kLeaders, Texture &tLeadersActive, Texture &tLeaders)
{
	Vector2i pos = Mouse::getPosition(game);
	if (b.menu && pos.x >= 321 && pos.x <= 579 && pos.y >= 360 && pos.y <= 450)
	{
		kPlay.setTexture(tPlayActive);
		cout << "Active!" << endl;
	}
	else kPlay.setTexture(tPlay);
	if (b.menu && pos.x >= 321 && pos.x <= 579 && pos.y >= 463 && pos.y <= 553) kLeaders.setTexture(tLeadersActive);
	else kLeaders.setTexture(tLeaders);
	if (b.menu && pos.x >= 321 && pos.x <= 579 && pos.y >= 566 && pos.y <= 656) kExit.setTexture(tExitActive);
	else kExit.setTexture(tExit);

	Logo.move(0, 0 + sin(grad) / 4);
	grad = grad + 0.01;
	game.draw(MenuBG);
	game.draw(kPlay);
	game.draw(kLeaders);
	game.draw(kExit);
	game.draw(Logo);
	game.display();
}

void BallPosition(Ball &ball, Boolean& b, float &dx, float & dy,float &x, float	&y, Player &player, float &gamespeed)
{
	if (Keyboard::isKeyPressed(Keyboard::Space) || Mouse::isButtonPressed(Mouse::Right))
	{
		b.mball = false;
		dx = 6;
		dy = -5;
	}
	if (ball.sprite.getPosition().y >= 688)
	{
		b.mball = true;
		player.Lives(1);
		
	}
	if (b.mball && (k==0))
	{
		ball.sprite.setPosition((player.sprite.getPosition().x + (player.sprite.getSize().x / 2)- (ball.sprite.getSize().x/2)), player.sprite.getPosition().y - 17);
		x = player.sprite.getPosition().x + 50;
		y = player.sprite.getPosition().y - 17;
	}
	if (b.pause && (k == 3) && !b.mball)
	{
		b.mball = true;
		x = x;
		y = y;
		ball.sprite.setPosition(x, y);
	}
	if (!b.mball)
	{
		if (!b.pause)
		{
			x += dx * gamespeed;
			y += dy * gamespeed;
		}
		ball.sprite.move(0.4 * 30 * std::cos(dx),0.7 * 30 * std::sin(dx));
		//ball.sprite.setPosition(x, y);
		//ball.sprite.move(1.5*10* std::cos(dx), -1.5 * std::sin(dy));
	}
	if ((ball.sprite.getPosition().x < 90 || ball.sprite.getPosition().x + ball.sprite.getScale().x>675)) dx = PI - dx;
	if ((ball.sprite.getPosition().y < 30 || ball.sprite.getPosition().y + ball.sprite.getScale().y>720))  dx = -dx;
	/*if (x < 90 || x>675)  dx = -dx;
	if (y < 28 || y>720)  dy = -dy;*/
}
void WriteToFile(std::string name, Player& player)
{
	fout.open("highscores.txt", ios::app); // окрываем файл для записи
	if (fout.is_open())
	{
		fout << name << " " << player.GetScore() << std::endl;
	}
	fout.close();
}
void PlayerAndBall(Player &player, Ball &ball, float& dx, float& dy, Bonus &bonus, Boolean &b, Texture &tplayer)
{
	if (player.sprite.getGlobalBounds().intersects(ball.sprite.getGlobalBounds()))
	{

		float ballx = ball.sprite.getPosition().x;
		float playerx = player.sprite.getPosition().x;
		const float x = ballx + ball.sprite.getScale().x / 2 - playerx;
		const float range = 180 - 30 * 2;
		const float degrees = (range * x / player.sprite.getScale().x) + 30;
		dx = -dx + ((rand() % 1 -1)/2);
		/*if ((ballx >= player.sprite.getSize().x * 0.2) && (ballx <= playerx + player.sprite.getSize().x*0.8))
		{
			dy = -5;
			dx = dx * 0.9;
		}
		else
		{
			dy = -4;
			dx = dx * 1.1;
		}*/
	}
	if (player.sprite.getGlobalBounds().intersects(bonus.sprite.getGlobalBounds()))
	{
		switch(bonus.type)
		{
		case 1: 
		{
			player.settexture(tplayer, 0, 85, 22, 0, 2);
			break;
		}
		case 2: 
		{
			player.settexture(tplayer, 190, 137, 22, 0, 2);
			break;
		}

		}
		b.bonusfalling = false;
		b.bonus = false;
	}
}
void Score(Player &player, Boolean &b, Ball &ball, Font &font, Event &e, float &texttimer) {
	string k = to_string(player.GetScore());
	string enteredname;
	pScore.setString("SCORE\n" + k);
	if ((z == ((player.GetScore() / 10)))||player.Lives(2) <= 0)
	{
		b.mball = true;
		ball.sprite.setPosition((player.sprite.getPosition().x + (player.sprite.getSize().x / 2) - (ball.sprite.getSize().x / 2)), player.sprite.getPosition().y - 17);
		if (player.Lives(2) <= 0)
		{
			b.gameover = true;
			GameOverText(font, "GAMEOVER");
			if (e.type == sf::Event::TextEntered && texttimer > 2000)
			{
				if (e.text.unicode == 32)
				{
					b.entername = true;
					}
				switch (e.text.unicode)
				{
				case 0x20: break;
				case 0xD://Enter
				{
					if (!name.isEmpty())
					{
						enteredname = name;
						WriteToFile(enteredname, player);
					}
					b.entername = false;
					b.textentering = false;
					b.gameover = false;
					b.menu = true;
					b.play = false;
					player.Lives(3);
					break;
				}
				case 0x8://Backspace
					if (!name.isEmpty() && texttimer > 2000)
						name.erase(name.getSize() - 1);
						texttimer = 0;
					break;
				default:
				{
					name += static_cast<char>(e.text.unicode);
					cout << e.text.unicode << endl;
					texttimer = 0;
					break;

				}
				}
			}
		}
		EnterNameText(font, name);
	}
		
}
	



int main()
{
	
	RenderWindow game(VideoMode(900, 720), "Arkanoid alpha");
	game.setFramerateLimit(30);

	Texture tblock1, tblock2, tblock3, tblock4, tblock5, tblock6, tplayer, tball, tbackground, tframe, 
		tPlay, tExit, tMenuBG, tLogo, tPlayActive, tExitActive, tLeaders, tLeadersActive, tPause, 
		tPauseActive, tPauseScreen, tLife, tNewBlocks, tBonus;
	Font font;
	Player player;
	Ball ball;
	Bonus bonus;
	Boolean b;
	AssetsLoader(tblock1, tblock2, tblock3, tblock4, tblock5, tblock6, tplayer, tball, tbackground, tframe, 
		tPlay, tExit, tMenuBG, tLogo, tPlayActive, tExitActive, font, pScore, tLeadersActive, tLeaders, tPause, 
		tPauseActive, tPauseScreen, tLife, tNewBlocks, tBonus);
	seticon(game);
	Sprite sBackground(tbackground), sFrame(tframe), kPlay(tPlay), kExit(tExit), kLeaders(tLeaders), 
		MenuBG(tMenuBG), Logo(tLogo), kPause(tPause), PauseScreen(tPauseScreen), Life[3];

	Logo.setPosition(53, 60);
	kPlay.setPosition(321, 360);
	kLeaders.setPosition(321, 463);
	kExit.setPosition(321, 566);
	kPause.setPosition(793, 13);
	player.settexture(tplayer,85, 105, 22, 1, 2);
	ball.settexture(tball,0, 16, 16, 0, 1);

	Clock clock;
	float texttimer = 0;
	float menutimer = 0;
	sf::Time t1 = sf::microseconds(10000);
	sf::Time t2 = sf::milliseconds(10);
	sf::Time t3 = sf::seconds(0.01f);
	for (int i = 0; i < 3; i++)
	{
		Life[i].setTexture(tLife);
		Life[i].setPosition(750 + 37 * i, 202);
	}

	float ballscale = 0.8;
	float dx = 7, dy = -5;
	float x = 200, y = 1000;
	float bonusx, bonusy;
	float bonusdy = -5;
	float gamespeed = 1.5;
	
	Block blocks[88];
	
	float grad = 0;
	int z2 = 0;
	BonusAdder();

	while (game.isOpen())
	{


		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); //перезагружает время
		time = time / 100; //скорость игры
		Event e;
		vector<leaders> new_operations;
		menutimer += time;
		AnalyzeEvent(e, game, b, font, new_operations, MenuBG, menutimer);
		b.textentering = false;
		if (b.menu)
		{
			Menu(b, game, kPlay, kExit, tPlayActive, tPlay, tExit, MenuBG, grad, Logo, 
				tExitActive, kLeaders, tLeaders, tLeadersActive);
			z = setblocks(blocks, game, tblock1, tblock2, tblock3, tblock4, tblock5, 
				tblock6, tNewBlocks);
			player.ResetScore();

		}
		else if (b.leaders)
		{
			LeaderBoardMenu(b, game, MenuBG, e);
		}
		else if (b.play)
		{
			texttimer += time;
			Vector2i pos = Mouse::getPosition(game);
			if (b.play && pos.x >= 793 && pos.x <= 884 && pos.y >= 13 && pos.y <= 104) 
				kPause.setTexture(tPauseActive);
			else kPause.setTexture(tPause);
			BlockBounds(ball, blocks, ballscale, dx, dy, &z2, player, tball, tBonus, bonus, b);
			player.move(game);
			BallPosition(ball, b, dx, dy, x, y, player, gamespeed);
			PlayerAndBall(player, ball, dx, dy,  bonus, b, tplayer);
			Score(player, b, ball, font, e, texttimer);

			DrawObjects(game, sBackground, ball.sprite, player.sprite, blocks, sFrame, pScore,
				kPause, b, PauseScreen, Life, player, bonus);
		
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
