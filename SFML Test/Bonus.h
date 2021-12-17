#pragma once
#include "NewLoader.h"
using namespace std;
using namespace sf;
class Bonus : public NewLoader
{
public:
	int type;
	void SetBonus(int i, Texture& texture);
};

