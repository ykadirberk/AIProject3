#include <iostream>

#include "Game/Game.h"
#include "CpuPlayer/CpuPlayer.h"
#include "HumanPlayer/HumanPlayer.h"

int main() {

	Game game(5, 5, PlayerType::HUMAN_PLAYER, PlayerType::AI_PLAYER, HeuristicType::PUNISHER_HEURISTIC, HeuristicType::PUNISHER_HEURISTIC);

	//IN THIS STUATION:
	//PLAYER CPU 0 WILL USE PUNISHER HEURISTIC
	//PLAYER CPU 1 WILL USE SIMPLE HEURISTIC

	
	while (!game.IsEnded()) {
		game.Render();
		game.Input();
	}

	game.Render();
	game.DeclareWinner();
	
	return 0;
}