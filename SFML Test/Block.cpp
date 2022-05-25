#include "Block.h"
#include "Ball.h"

void Block::changehealth()
{
	health--;
}
void Block::collision()
{
	sprite.setPosition(9999, 0);
}
