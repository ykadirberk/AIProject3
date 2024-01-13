#include <iostream>

#include "Game/Game.h"
#include "CpuPlayer/CpuPlayer.h"
#include "HumanPlayer/HumanPlayer.h"

int main() {
	Game game(5, 5, PlayerType::HUMAN_PLAYER, PlayerType::AI_PLAYER, HeuristicType::SIMPLE_HEURISTIC);
	
	while (!game.IsEnded()) {
		game.Render();
		game.Input();
	}

	game.Render();
	
	return 0;
}