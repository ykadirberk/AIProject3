#pragma once

#include "../Utils.h"
#include "../Player/Player.h"
#include "../HumanPlayer/HumanPlayer.h"
#include "../CpuPlayer/CpuPlayer.h"
#include "../Heuristic/SimpleHeuristic/SimpleHeuristic.h"
#include "../Heuristic/PunisherHeuristic/PunisherHeuristic.h"

#include <vector>
#include <memory>
#include <iostream>


enum class PlayerType {
	HUMAN_PLAYER,
	AI_PLAYER
};

enum class HeuristicType {
	SIMPLE_HEURISTIC,
	PUNISHER_HEURISTIC
};

class Game {
	public:
		Game(int t_width, int t_height, PlayerType t_player1, PlayerType t_player2, HeuristicType t_heuristic1_type, HeuristicType t_heuristic2_type);
		~Game();

		void Render();
		void Input();

		bool IsEnded();
		void DeclareWinner();

	private:
		std::vector<int> m_Map;
		std::vector<bool> m_SosMap;

		std::shared_ptr<StateHandler> m_StateHandler;
		
		int m_Width;
		int m_Height;

		bool m_Turn = false;

		std::shared_ptr<Player> player1;
		std::shared_ptr<Player> player2;

		int m_Player1Score = 0;
		int m_Player2Score = 0;

		bool Apply(Move t_m);
		int CheckForSOS();

		bool VerticalSos(int row, int col);
		bool HorizontalSos(int row, int col);
		bool LTRBSos(int row, int col); // left-top right-bottom sos
		bool RTLBSos(int row, int col); // right-top left-bottom sos
};