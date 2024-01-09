#pragma once

#include "../Player/Player.h"

class CpuPlayer : public Player {
	public:
		CpuPlayer();
		virtual ~CpuPlayer() {}

		Move MakeMove() override;
		std::string GetName() override;
		
	private:
		std::string m_Name;
		inline static int m_PlayerCount = 0;

};