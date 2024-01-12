#include "CpuPlayer.h"

#include <sstream>

CpuPlayer::CpuPlayer() {
	std::stringstream ss;
	ss << "CPU " << m_PlayerCount;
	m_Name = ss.str();
	m_PlayerCount++;
}
Move CpuPlayer::MakeMove(StateHandler& handler) {

	Move t;
	t.pos_x = 0;
	t.pos_y = 0;
	t.key = Move::CastStr("S");

	return t;
}

std::string CpuPlayer::GetName()
{
	return m_Name;
}
