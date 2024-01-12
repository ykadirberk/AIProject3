#include "GameState.h"

GameState::GameState(std::shared_ptr<GameState> t_parent, Move t_move, int t_width, int t_height) {
	m_Width = t_width;
	m_Height = t_height;

	m_Move = t_move;
	
	if (t_parent == nullptr) {
		m_StateType = StateType::TYPE_MAX;
		m_Score = INT_MAX;
		m_CurrentState.reserve(m_Width * m_Height);
		for (int row = 0; row < m_Height; row++) {
			for (int col = 0; col < m_Width; col++) {
				m_CurrentState[row * m_Width + col] = KEY_EMPTY;
			}
		}
		m_CurrentState[0] = KEY_S;
		m_CurrentState[m_Width - 1] = KEY_S;
		m_CurrentState[(m_Height - 1) * m_Width] = KEY_S;
		m_CurrentState[m_Height * m_Width - 1] = KEY_S;

	} else {
		m_ParentState = t_parent;
		auto par_state = m_ParentState.lock();
		if (par_state->GetStateType() == StateType::TYPE_MAX) {
			m_StateType = StateType::TYPE_MIN;
			m_Score = INT_MIN;
		} else {
			m_StateType = StateType::TYPE_MAX;
			m_Score = INT_MAX;
		}

		m_CurrentState.reserve(m_Width * m_Height);
		for (int i = 0; i < m_Width * m_Height; i++) {
			m_CurrentState[i] = t_parent->GetCurrentState()[i];
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
	return m_ScoreMaxPlayer - m_ScoreMinPlayer;
}

int GameState::GetMinPlayerScore() {
	return m_ScoreMinPlayer;
}

void GameState::SetMinPlayerScore(int t_score) {
	m_ScoreMinPlayer = t_score;
}

int GameState::GetMaxPlayerScore() {
	return m_ScoreMaxPlayer;
}

void GameState::SetMaxPlayerScore(int t_score)
{
	m_ScoreMaxPlayer = t_score;
}

StateType GameState::GetStateType() {
	return m_StateType;
}

void GameState::SetStateType(StateType t_state) {
	m_StateType = t_state;
}
