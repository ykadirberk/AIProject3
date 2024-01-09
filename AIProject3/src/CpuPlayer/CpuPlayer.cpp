#include "CpuPlayer.h"

#include <sstream>

CpuPlayer::CpuPlayer() {
	std::stringstream ss;
	ss << "CPU " << m_PlayerCount;
	m_Name = ss.str();
	m_PlayerCount++;
}
Move CpuPlayer::MakeMove() {
	return Move();
}

std::string CpuPlayer::GetName()
{
	return m_Name;
}
