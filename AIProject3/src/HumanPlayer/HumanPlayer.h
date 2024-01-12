#pragma once

#include "../Player/Player.h"


class HumanPlayer : public Player {
	public:
		HumanPlayer();
		virtual ~HumanPlayer() {}
	
		Move MakeMove(std::shared_ptr<StateHandler> handler, std::vector<int>& t_current) override;
		std::string GetName() override;
	
	private:
		std::string m_Name;
		inline static int m_PlayerCount = 0;
};