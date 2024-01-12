#pragma once

#include "../Player/Player.h"
#include "../StateHandler/StateHandler.h"

#include <memory>

class CpuPlayer : public Player {
	public:
		CpuPlayer();
		virtual ~CpuPlayer() {}

		Move MakeMove(StateHandler& handler) override;
		std::string GetName() override;
		
	private:
		std::string m_Name;
		inline static int m_PlayerCount = 0;

};