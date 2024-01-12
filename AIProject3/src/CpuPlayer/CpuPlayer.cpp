#include "CpuPlayer.h"

#include <sstream>
#include <iostream>

CpuPlayer::CpuPlayer() {
	std::stringstream ss;
	ss << "CPU " << m_PlayerCount;
	m_Name = ss.str();
	m_PlayerCount++;
}
Move CpuPlayer::MakeMove(std::shared_ptr<StateHandler> handler, std::vector<int>& t_current) {

	handler->GenerateNewPlays(t_current);

	Move t = handler->ChoosePlay();

	std::cout << "(" << t.pos_y << ", " << t.pos_x << ") -> " << Move::CastKey(t.key) << std::endl;
	std::cin.get();

	return t;
}

std::string CpuPlayer::GetName()
{
	return m_Name;
}
