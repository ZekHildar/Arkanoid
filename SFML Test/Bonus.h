#pragma once
#include "NewLoader.h"
#include "Boolean.h"
#include <cmath>
using namespace std;
using namespace sf;
class Bonus : public NewLoader
{
public:
	int type;
	int BONUS[88];
	void SetBonus(int i, Texture& texture);
	void BonusGenerator();
	void moveBonus(Boolean& b);
	void BonusAdder(Boolean& b, Texture& tBonus, float x, float y, int i);
};

