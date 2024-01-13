#include "CpuPlayer.h"

#include <sstream>
#include <iostream>
#include <chrono>

CpuPlayer::CpuPlayer() {
	std::stringstream ss;
	ss << "CPU " << m_PlayerCount;
	m_Name = ss.str();
	m_PlayerCount++;
}
Move CpuPlayer::MakeMove(std::shared_ptr<StateHandler> handler, std::vector<int>& t_current) {
	auto timer_start = std::chrono::high_resolution_clock::now();
	
	handler->GenerateNewPlays(t_current);
	Move t = handler->ChoosePlay();
	
	auto timer_end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration = timer_end - timer_start;

	std::cout << "(" << t.pos_y << ", " << t.pos_x << ") -> " << Move::CastKey(t.key) << ", took " << duration.count() << " milliseconds to choose." << std::endl;
	std::cin.get();

	return t;
}

std::string CpuPlayer::GetName()
{
	return m_Name;
}
