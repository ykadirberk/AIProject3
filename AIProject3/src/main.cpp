#include <iostream>

#include "Game/Game.h"
#include "CpuPlayer/CpuPlayer.h"
#include "HumanPlayer/HumanPlayer.h"

int main() {
	Game game(5,5, std::make_shared<HumanPlayer>(), std::make_shared<HumanPlayer>());
	
	while (!game.IsEnded()) {
		std::cout << "===============" << std::endl;
		game.Render();
		game.Input();
		std::cout << "===============" << std::endl;
	}
	
	return 0;
}