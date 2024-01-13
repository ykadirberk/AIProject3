#include "GameState.h"

GameState::GameState(std::shared_ptr<GameState> t_parent, Move t_move, int t_width, int t_height) {
	m_Width = t_width;
	m_Height = t_height;

	m_Move = t_move; 
	m_Score = 0;

	if (!t_parent) {
		m_StateType = StateType::TYPE_MAX;
		//m_Score = INT_MAX;

		m_CurrentState.reserve(m_Width * m_Height);
		for (int row = 0; row < m_Height; row++) {
			for (int col = 0; col < m_Width; col++) {
				m_CurrentState.push_back(KEY_EMPTY);
			}
		}
		m_CurrentState[0] = KEY_S;
		m_CurrentState[m_Width - 1] = KEY_S;
		m_CurrentState[(m_Height - 1) * m_Width] = KEY_S;
		m_CurrentState[m_Height * m_Width - 1] = KEY_S;

	} else {
		if (t_parent->GetStateType() == StateType::TYPE_MAX) {
			m_StateType = StateType::TYPE_MIN;
			//m_Score = INT_MIN;
		} else {
			m_StateType = StateType::TYPE_MAX;
			//m_Score = INT_MAX;
		}

		m_CurrentState.reserve(m_Width * m_Height);
		for (int i = 0; i < m_Width * m_Height; i++) {
			m_CurrentState.push_back(t_parent->GetCurrentState()[i]);
		}
		m_CurrentState[((m_Move.pos_y - 1) * m_Width) + m_Move.pos_x - 1] = m_Move.key;
	}
}

GameState::~GameState() {

}

std::vector<std::shared_ptr<GameState>>& GameState::GetNextStates() {
	return m_NextStates;
}

std::vector<int>& GameState::GetCurrentState() {
	return m_CurrentState;
}

Move GameState::GetMove() {
	return m_Move;
}

int GameState::GetScore() {
	return m_Score;
}

void GameState::SetScore(int t_score)
{
	m_Score = t_score;
}

StateType GameState::GetStateType() {
	return m_StateType;
}

void GameState::SetStateType(StateType t_state) {
	m_StateType = t_state;
}
