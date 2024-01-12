#include "StateHandler.h"

StateHandler::StateHandler(std::vector<int> t_current, int t_width, int t_height) : m_Width(t_width), m_Height(t_height) {
	m_Root = std::make_shared<GameState>(nullptr, Move(), m_Width, m_Height);
	GenerateNewPlays(t_current);
}

StateHandler::~StateHandler() {

}

Move StateHandler::ChoosePlay() {
	int score_to_go = RecursiveAssignPoints(m_Root, 0, INT_MIN, INT_MAX);
	auto& states = m_Root->GetNextStates();
	for (auto& state : states) {
		if (state->GetScore() == score_to_go) {
			return state->GetMove();
		}
	}
	return Move(1, 1, KEY_S);
}

void StateHandler::GenerateNewPlays(std::vector<int> t_current) {
	if (!IsEqual(t_current, m_Root->GetCurrentState())) {
		auto& states = m_Root->GetNextStates();
		for (auto& state : states) {
			if (IsEqual(t_current, state->GetCurrentState())) {
				m_Root = state;
				break;
			}
		}
	}
	RecursiveCreate(m_Root, 0);
}
void StateHandler::RecursiveCreate(std::shared_ptr<GameState> t_root, int t_depth) {

	// We want 4 ply
	if (t_depth == 4) {
		return;
	}

	auto& states = t_root->GetNextStates();
	if (states.size() == 0) {
		auto& map = t_root->GetCurrentState();
		for (int i = 0; i < m_Height; i++) {
			for (int j = 0; j < m_Width; j++) {
				if (map[i * m_Width + j] == KEY_EMPTY) {
					std::shared_ptr<GameState> temp1 = std::make_shared<GameState>(t_root, Move(i + 1, j + 1, KEY_O), m_Width, m_Height);
					RecursiveCreate(temp1, t_depth + 1);
					states.push_back(temp1);

					std::shared_ptr<GameState> temp2 = std::make_shared<GameState>(t_root, Move(i + 1, j + 1, KEY_S), m_Width, m_Height);
					RecursiveCreate(temp2, t_depth + 1);
					states.push_back(temp2);
				}
			}
		}
	}
}

int StateHandler::RecursiveAssignPoints(std::shared_ptr<GameState> t_root, int t_depth, int max_prune, int min_prune) {

	auto heuristic_value = heuristic->Evaluate(t_root);
	if (t_depth == 4) {
		return heuristic_value; // apply heuristic to the root
	}

	//t_root->SetScore(heuristic_value);

	auto& states = t_root->GetNextStates();
	
	int minmax;
	if (t_root->GetStateType() == StateType::TYPE_MAX) {
		minmax = INT_MIN;
		for (auto& state : states) {
			int val = RecursiveAssignPoints(state, t_depth + 1, minmax, min_prune);
			state->SetMaxPlayerScore(val);
			if (val > min_prune) {
				return val;
			}
			if (state->GetScore() > minmax) {
				minmax = state->GetScore();
			}
		}
	} else {
		minmax = INT_MAX;
		for (auto& state : states) {
			int val = RecursiveAssignPoints(state, t_depth + 1, max_prune, minmax);
			state->SetMinPlayerScore(val);
			if (val < max_prune) {
				return val;
			}
			if (state->GetScore() < minmax) {
				minmax = state->GetScore();
			}
		}
	}
	return minmax;
}

bool StateHandler::IsEqual(std::vector<int>& t1, std::vector<int>& t2) {
	if (t1.size() != t2.size()) {
		return false;
	}

	for (int i = 0; i < t1.size(); i++) {
		if (t1[i] != t2[i]) {
			return false;
		}
	}

	return true;
}
