#include "Bonus.h"
#include "NewLoader.h"
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
