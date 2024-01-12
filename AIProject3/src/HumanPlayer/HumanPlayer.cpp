#include "HumanPlayer.h"

#include <sstream>
#include <iostream>
#include <vector>

HumanPlayer::HumanPlayer() {
	std::stringstream ss;
	ss << "Human " << m_PlayerCount;
	m_Name = ss.str();
	m_PlayerCount++;
}

Move HumanPlayer::MakeMove(std::shared_ptr<StateHandler> handler, std::vector<int>& t_current) {
	std::string line;
	std::getline(std::cin, line);
	
	std::stringstream ss;
	ss << line;
	int pos_x, pos_y;
	std::string key;
	ss >> pos_y >> pos_x >> key;

	Move t;
	t.pos_x = pos_x;
	t.pos_y = pos_y;
	t.key = Move::CastStr(key);

	return t;
}

std::string HumanPlayer::GetName()
{
	return m_Name;
}
