#pragma once

#include "../Utils.h"
#include "../Player/Player.h"

#include <vector>
#include <memory>
#include <iostream>


class Game {
	public:
		Game(int t_width, int t_height, std::shared_ptr<Player> t_player1, std::shared_ptr<Player> t_player2);
		~Game();

		void Render();
		void Input();

		bool IsEnded();

	private:
		std::vector<int> m_Map;
		std::vector<bool> m_SosMap;
		
		int m_Width;
		int m_Height;

		bool m_Turn = false;

		std::shared_ptr<Player> player1;
		std::shared_ptr<Player> player2;

		bool Apply(Move t_m);
		int CheckForSOS();
};