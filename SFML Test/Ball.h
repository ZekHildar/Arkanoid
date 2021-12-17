#pragma once
#include <SFML/Graphics.hpp>
#include "NewLoader.h"
using namespace std;
using namespace sf;
class Ball : public NewLoader
{
	public:
		void scale(float scale);
};

