#include <time.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include "Player.h"
#include "Ball.h"
#include "Block.h"
#include "Bonus.h"
#include "Boolean.h"

using namespace std;
using namespace sf;
//class Boolean {
//public:
//	bool mball = true;
//	bool menu = true;
//	bool leaders = false;
//	bool play = false;
//	bool pause = false;
//	bool gameover = false;
//	bool entername = false;
//	bool textentering = false;
//	bool bonus = false;
//	bool bonusfalling = false;
//};
Text pScore;
Text Pause;
Text GameOver;
Text EnterName;
Text LeadersNames;
string str;
sf::String name;
ofstream fout;

int z;
int k = 0;
Event p;

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
void PauseText(Font& font)
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
	GameOver.setPosition(450 - GameOver.getGlobalBounds().width / 2, 360 - GameOver.getGlobalBounds().height / 2 - 20);
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

int seticon(RenderWindow& game)
{
	Image icon;
	if (!icon.loadFromFile("images/Ball.png"))
	{
		return 1;
	}
	game.setIcon(31, 31, icon.getPixelsPtr());
}
int setblocks(Block sprite[], RenderWindow& game, Texture& tNewBlocks)
{
	int k = 0;
	int z = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 11; j++)
		{
			sprite[k].SetBlocks(i, j, LEVEL, tNewBlocks, z);
			k++;
		}
	return z;
}
void BlockBounds(Ball& ball, Block(&blocks)[88], float ballscale, float& dx, float& dy, int* z2, Player& player, Texture& t, Texture& tBonus, Bonus& bonus, Boolean& b)
{
	if (b.bonusfalling) 
	bonus.moveBonus(b);
	for (int i = 0; i < 88; i++)
	{
		if (ball.sprite.getGlobalBounds().intersects(blocks[i].sprite.getGlobalBounds()))
		{
			
			blocks[i].collision();
			ball.BlockCollission(blocks[i], dx, dy);
			
			switch (blocks[i].type)
			{
			case 6:
			{
				break;
			}
			default:
			{
				bonus.BonusAdder(b, tBonus, ball.sprite.getPosition().x, ball.sprite.getPosition().y, i);
				player.SetScore(10);
				z2++;
			}
			}
		}
	}
}
void AssetsLoader(Texture& tblock1, Texture& tblock2, Texture& tblock3, Texture& tblock4, Texture& tblock5, Texture& tblock6, Texture& tplayer, Texture& tball, Texture& tbackground, Texture& tframe, Texture& tPlay, Texture& tExit, Texture& tMenuBG, Texture& tLogo, Texture& tPlayActive, Texture& tExitActive, Font& font, Text& pScore, Texture& tLeaders, Texture& tLeadersActive, Texture& tPause, Texture& tPauseActive, Texture& tPauseScreen, Texture& tLife, Texture& tNewBlocks, Texture& tBonus)
{
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
}
void DrawObjects(RenderWindow& game, Sprite sBackground, RectangleShape& ball, RectangleShape& player, Block(&blocks)[88], Sprite& sFrame, Text& pScore, Sprite& kPause, Boolean& b, Sprite& PauseScreen, Sprite(&Life)[3], Player oplayer, Bonus& bonus)
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
	if (b.pause && (oplayer.Lives(2) > 0))
	{
		game.draw(PauseScreen);
		game.draw(Pause);
	}

	game.display();
}
void LeaderBoardMenu(Boolean& b, RenderWindow& game, Sprite& background, Event& e)
{

	game.draw(background);
	game.draw(LeadersNames);
	game.display();

}
void LeaderBoard(Boolean& b, RenderWindow& game, vector<leaders>& new_operations, Font& font)
{
	string names;
	int scores;
	std::ifstream in("highscores.txt");
	if (in.is_open())
	{
		while (in >> names >> scores)
		{
			new_operations.push_back(leaders(names, scores));
		}
	}
	in.close();

	LeadersNamesSetting(font, new_operations);
}
void AnalyzeMenu(RenderWindow& game, Event& e, Boolean& b, Font& font, vector<leaders>& new_operations, Sprite& MenuBG, float& texttimer)
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
			if (b.play & !b.pause)
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
void AnalyzeEvent(Event& e, RenderWindow& game, Boolean& b, Font& font, vector<leaders>& new_operations, Sprite& MenuBG, float& menutimer)
{
	while (game.pollEvent(e))
	{
		if (e.type == Event::Closed)
			game.close();
		AnalyzeMenu(game, e, b, font, new_operations, MenuBG, menutimer);
	}
}
void Menu(Boolean& b, RenderWindow& game, Sprite& kPlay, Sprite& kExit, Texture& tPlayActive, Texture& tPlay, Texture& tExit, Sprite& MenuBG, float& grad, Sprite& Logo, Texture& tExitActive, Sprite& kLeaders, Texture& tLeadersActive, Texture& tLeaders)
{
	Vector2i pos = Mouse::getPosition(game);
	if (b.menu && pos.x >= 321 && pos.x <= 579 && pos.y >= 360 && pos.y <= 450)
	{
		kPlay.setTexture(tPlayActive);
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

void WriteToFile(std::string name, Player& player)
{
	fout.open("highscores.txt", ios::app);
	if (fout.is_open())
	{
		fout << name << " " << player.GetScore() << std::endl;
	}
	fout.close();
}
void PlayerAndBall(Player& player, Ball& ball, float& dx, float& dy, Bonus& bonus, Boolean& b, Texture& tplayer)
{
	if (player.sprite.getGlobalBounds().intersects(ball.sprite.getGlobalBounds()))
	{
		dy = -dy;
	}
	player.BonusIntersects(bonus, tplayer, b);
}
void Score(Player& player, Boolean& b, Ball& ball, Font& font, Event& e, float& texttimer) {
	string k = to_string(player.GetScore());
	string enteredname;
	pScore.setString("SCORE\n" + k);
	if ((z == ((player.GetScore() / 10))) || player.Lives(2) <= 0)
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
		else
		{
			b.gameover = true;
			GameOverText(font, "YOU WIN!");
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
	Ball ball, ball1;
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
	player.settexture(tplayer, 85, 105, 22, 1, 2);
	ball.settexture(tball, 0, 16, 16, 0, 1);

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
	bonus.BonusGenerator();
	

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
			z = setblocks(blocks, game, tNewBlocks);
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
			ball.BallPosition(ball, b, dx, dy, x, y, player, gamespeed, k);
			PlayerAndBall(player, ball, dx, dy, bonus, b, tplayer);
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