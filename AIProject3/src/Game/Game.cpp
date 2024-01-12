#include "Game.h"

Game::Game(int t_width, int t_height, PlayerType t_player1, PlayerType t_player2) {
	m_Width = t_width;
	m_Height = t_height;

	// fill the map with empty space
	m_Map.reserve(m_Width * m_Height);
	for (int i = 0; i < m_Width * m_Height; i++) {
		m_Map[i] = KEY_EMPTY;
	}

	m_SosMap.reserve(m_Width * m_Height);
	for (int i = 0; i < m_Width * m_Height; i++) {
		m_SosMap[i] = false;
	}

	// put S key on corners
	m_Map[0] = KEY_S;
	m_Map[m_Width - 1] = KEY_S;
	m_Map[m_Width * (m_Height - 1)] = KEY_S;
	m_Map[m_Width * m_Height - 1] = KEY_S;

	m_StateHandler = std::make_shared<StateHandler>(m_Map, m_Width, m_Height);

	if (t_player1 == PlayerType::HUMAN_PLAYER) {
		player1 = std::make_shared<HumanPlayer>();
	}
	else {
		player1 = std::make_shared<CpuPlayer>();
	}

	if (t_player2 == PlayerType::HUMAN_PLAYER) {
		player2 = std::make_shared<HumanPlayer>();
	}
	else {
		player2 = std::make_shared<CpuPlayer>();
	}
}

Game::~Game() {
	
}

void Game::Render() {
	std::cout << "--------------------------" << std::endl;
	std::cout << player1->GetName() << " score: " << m_Player1Score << std::endl;
	std::cout << player2->GetName() << " score: " << m_Player2Score << std::endl;
	std::cout << "--------------------------" << std::endl;

	int colnums = 1;
	std::cout << " ";
	for (int i = 0; i < m_Width * 2 + 1; i++) {
		if (i % 2 == 0) {
			std::cout << "   ";
			continue;
		}
		std::cout << colnums;
		colnums++;
	}
	std::cout << std::endl;

	for (int row = 0; row < m_Height * 2 + 1; row++) {
		if (row % 2 == 0) {
			for (int i = 0; i < m_Width * 2 + 2; i++) {
				std::cout << "- ";
			}
			std::cout << std::endl;
			continue;
		}
		for (int col = 0; col < m_Width * 2 + 1; col++) {
			if (col == 0) {
				std::cout << (((row - 1) / 2) + 1) << " ";
			}
			if (col % 2 == 0) {
				std::cout << "| ";
			} else {
				std::cout << Move::CastKey(m_Map[(m_Width) * ((row - 1) / 2) + ((col - 1) / 2)]) << " ";
			}
		}
		std::cout << std::endl;
	}
}

void Game::Input() {
	if (!m_Turn) {
		while (1) {
			std::cout << player1->GetName() << " >> " << std::endl;
			auto move = player1->MakeMove(*m_StateHandler);
			if (Apply(move)) {
				m_Player1Score += CheckForSOS();
				break;
			} else {
				std::cout << "The positions provided by you are either invalid or that place is already used." << std::endl;
			}
		}
	} else {
		while (1) {
			std::cout << player2->GetName() << " >> " << std::endl;
			auto move = player2->MakeMove(*m_StateHandler);
			if (Apply(move)) {
				m_Player2Score += CheckForSOS();
				break;
			}
			else {
				std::cout << "The positions provided by you are either invalid or that place is already used." << std::endl;
			}
		}
	}
	m_Turn = !m_Turn;
}

bool Game::IsEnded() {
	// return false if there is an empty position
	for (int i = 0; i < m_Width * m_Height; i++) {
		if (m_Map[i] == KEY_EMPTY) {
			return false;
		}
	}
	return true;
}

bool Game::Apply(Move t_m) {
	// if positions are out of board
	if (t_m.pos_x > m_Width || t_m.pos_y > m_Height) {
		return false;
	}

	// if positions already filled 
	if (m_Map[((t_m.pos_y - 1) * m_Width) + t_m.pos_x - 1] != KEY_EMPTY) {
		return false;
	}

	// fill with key
	m_Map[((t_m.pos_y - 1) * m_Width) + t_m.pos_x - 1] = t_m.key;
	return true;
}

int Game::CheckForSOS() {
	int points = 0;

	for (int row = 0; row < m_Height; row++) {
		for (int col = 0; col < m_Width; col++) {
			if (m_Map[(m_Width)*row + col] != KEY_S) {
				continue;
			}

			if (VerticalSos(row, col)) {
				points++;
			}

			if (HorizontalSos(row, col)) {
				points++;
			}

			if (LTRBSos(row, col)) {
				points++;
			}

			if (RTLBSos(row, col)) {
				points++;
			}
		}
	}

	return points;
}

bool Game::VerticalSos(int row, int col) {
	if (col >= m_Width) return false;
	if (col < 0) return false;
	if (row < 0) return false;
	if (row + 2 >= m_Height) false;

	bool o_recent = false;
	bool s_recent = false;

	bool sos_available = false;

	if (m_Map[(row + 1) * m_Width + col] == KEY_O) {
		o_recent = true;
	}

	if (m_Map[(row + 2) * m_Width + col] == KEY_S) {
		s_recent = true;
	}

	if (o_recent && s_recent) {
		if (!m_SosMap[row * m_Width + col]
			|| !m_SosMap[(row + 1) * m_Width + col]
			|| !m_SosMap[(row + 2) * m_Width + col]) {
			m_SosMap[row * m_Width + col] = true;
			m_SosMap[(row + 1) * m_Width + col] = true;
			m_SosMap[(row + 2) * m_Width + col] = true;
			sos_available = true;
		}
	}

	return sos_available;
}

bool Game::HorizontalSos(int row, int col) {
	if (col + 2 >= m_Width) return false;
	if (col < 0) return false;
	if (row < 0) return false;
	if (row >= m_Height) false;

	bool o_recent = false;
	bool s_recent = false;

	bool sos_available = false;

	if (m_Map[row * m_Width + col + 1] == KEY_O) {
		o_recent = true;
	}

	if (m_Map[row * m_Width + col + 2] == KEY_S) {
		s_recent = true;
	}

	if (o_recent && s_recent) {
		if (!m_SosMap[row * m_Width + col]
			|| !m_SosMap[row * m_Width + col + 1]
			|| !m_SosMap[row* m_Width + col + 2]) {
			m_SosMap[row * m_Width + col] = true;
			m_SosMap[row * m_Width + col + 1] = true;
			m_SosMap[row * m_Width + col + 2] = true;
			sos_available = true;
		}
	}

	return sos_available;
}

bool Game::LTRBSos(int row, int col) {
	if (col + 2 >= m_Width) return false;
	if (col < 0) return false;
	if (row < 0) return false;
	if (row + 2 >= m_Height) false;

	bool o_recent = false;
	bool s_recent = false;

	bool sos_available = false;

	if (m_Map[(row + 1) * m_Width + col + 1] == KEY_O) {
		o_recent = true;
	}

	if (m_Map[(row + 2) * m_Width + col + 2] == KEY_S) {
		s_recent = true;
	}

	if (o_recent && s_recent) {
		if (!m_SosMap[row * m_Width + col]
			|| !m_SosMap[(row + 1) * m_Width + col + 1]
			|| !m_SosMap[(row + 2) * m_Width + col + 2]) {
			m_SosMap[row * m_Width + col] = true;
			m_SosMap[(row + 1) * m_Width + col + 1] = true;
			m_SosMap[(row + 2)* m_Width + col + 2] = true;
			sos_available = true;
		}
	}

	return sos_available;
}

bool Game::RTLBSos(int row, int col) {
	if (col >= m_Width) return false;
	if (col - 2 < 0) return false;
	if (row < 0) return false;
	if (row + 2 >= m_Height) false;

	bool o_recent = false;
	bool s_recent = false;

	bool sos_available = false;

	if (m_Map[(row + 1) * m_Width + col - 1] == KEY_O) {
		o_recent = true;
	}

	if (m_Map[(row + 2) * m_Width + col - 2] == KEY_S) {
		s_recent = true;
	}

	if (o_recent && s_recent) {
		if (!m_SosMap[row * m_Width + col]
			|| !m_SosMap[(row + 1) * m_Width + col - 1]
			|| !m_SosMap[(row + 2) * m_Width + col - 2]) {
			m_SosMap[row * m_Width + col] = true;
			m_SosMap[(row + 1) * m_Width + col - 1] = true;
			m_SosMap[(row + 2) * m_Width + col - 2] = true;
			sos_available = true;
		}
	}

	return sos_available;
}
