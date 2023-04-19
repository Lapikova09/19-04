#include "game.h"
#include <ctime>
using namespace sf;

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	Game game;
	game.play();
	return 0;
}