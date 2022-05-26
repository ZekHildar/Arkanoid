#include "Bonus.h"
#include "NewLoader.h"
#include "Boolean.h"
#include <iostream>
using namespace std;
using namespace sf;
void Bonus::SetBonus(int i, Texture &texture)
{
	switch (i) {
	case 1: 
	case 2:
	case 3: Bonus::settexture(texture, 0, 40, 24,i-1, 1);
	}
	
}

void Bonus::BonusGenerator()
{
	int a;
	srand(time(0));
	for (int i = 0; i < 88; i++)
	{
		a = rand() % 10 + 1;
		if ((a < 4) && (a > 0)) this->BONUS[i] = a;
		else  this->BONUS[i] = 0;
	}
	
}

void Bonus::moveBonus(Boolean& b)
{
	if (!b.pause) sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 5);
	if (sprite.getPosition().y > 720)
	{
		b.bonusfalling = false;
		b.bonus = false;
	}
}

void Bonus::BonusAdder(Boolean& b, Texture& tBonus, float x, float y, int i)
{
	if ((this->BONUS[i] > 0) && (this->BONUS[i] < 4) & !b.bonus)
	{
		type = BONUS[i];
		SetBonus(BONUS[i], tBonus);
		b.bonusfalling = true;
		b.bonus = true;
		sprite.setPosition(x, y);
		moveBonus(b);
	}
	
}
