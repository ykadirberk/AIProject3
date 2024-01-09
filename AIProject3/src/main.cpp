#include <iostream>

#include "Game/Game.h"
#include "CpuPlayer/CpuPlayer.h"
#include "HumanPlayer/HumanPlayer.h"

int main() {
	Game game(8, 8, std::make_shared<HumanPlayer>(), std::make_shared<HumanPlayer>());
	
	while (!game.IsEnded()) {
		game.Render();
		game.Input();
	}
	
	return 0;
}