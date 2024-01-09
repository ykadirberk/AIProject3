#pragma once

#include "../Player/Player.h"

class HumanPlayer : public Player {
public:
	HumanPlayer();
	virtual ~HumanPlayer() {}

	Move MakeMove() override;
	std::string GetName() override;

private:
	std::string m_Name;
	inline static int m_PlayerCount = 0;

};