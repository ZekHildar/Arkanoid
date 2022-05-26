#include "Block.h"
#include "Ball.h"
#include "NewLoader.h"

void Block::changehealth()
{
	health--;
}
void Block::collision()
{
	sprite.setPosition(9999, 0);
}

void Block::SetBlocks(int i, int j, int(&LEVEL)[8][11], Texture& tNewBlocks, int& z)
{
	switch (LEVEL[i][j])
	{
	case 1:
		settexture(tNewBlocks, 0, 54, 27, LEVEL[i][j] - 1, 1);
		sprite.setPosition(92 + 54 * j, 134 + 27 * i);
		z++;
		break;
	case 2:
		settexture(tNewBlocks, 54, 54, 27, LEVEL[i][j] - 1, 1);
		sprite.setPosition(92 + 54 * j, 134 + 27 * i);
		z++;
		break;
	case 3:
		settexture(tNewBlocks, 108, 54, 27, LEVEL[i][j] - 1, 1);
		sprite.setPosition(92 + 54 * j, 134 + 27 * i);
		z++;
		break;
	case 4:
		settexture(tNewBlocks, 162, 54, 27, LEVEL[i][j] - 1, 1);
		sprite.setPosition(92 + 54 * j, 134 + 27 * i);
		z++;
		break;
	case 5:
		settexture(tNewBlocks, 216, 54, 27, LEVEL[i][j] - 1, 1);
		sprite.setPosition(92 + 54 * j, 134 + 27 * i);
		z++;
		break;
	case 6:
		settexture(tNewBlocks, 270, 54, 27, LEVEL[i][j] - 1, 1);
		type = 6;
		sprite.setPosition(92 + 54 * j, 134 + 27 * i);
		break;
	}
}
