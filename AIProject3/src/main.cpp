#include <iostream>

#include "Game/Game.h"
#include "CpuPlayer/CpuPlayer.h"
#include "HumanPlayer/HumanPlayer.h"

int main() {
	Game game(5, 5, PlayerType::AI_PLAYER, PlayerType::AI_PLAYER, HeuristicType::PUNISHER_HEURISTIC);
	
	while (!game.IsEnded()) {
		game.Render();
		game.Input();
	}

	game.Render();
	
	return 0;
}