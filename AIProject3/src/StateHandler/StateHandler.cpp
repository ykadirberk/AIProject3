#include "StateHandler.h"

StateHandler::StateHandler(std::vector<int>& t_current, int t_width, int t_height, std::shared_ptr<Heuristic> t_heuristic) : m_Width(t_width), m_Height(t_height) {
	heuristic = t_heuristic;
	Move m;
	m.pos_x = 1;
	m.pos_y = 1;
	m.key = KEY_S;
	m_Root = std::make_shared<GameState>(nullptr, m, m_Width, m_Height);
	GenerateNewPlays(t_current);
}

StateHandler::~StateHandler() {

}

Move StateHandler::ChoosePlay() {

	int score_to_go = RecursiveAssignPoints(m_Root, 0, INT_MIN, INT_MAX, m_Root->GetScore());

	auto states = m_Root->GetNextStates();


	for (auto& state : states) {
		if (state->GetScore() == score_to_go) {
			m_Root = state;
			auto mv = state->GetMove();
			//m_Root->SetParent(nullptr);
			//GenerateNewPlays(state->GetCurrentState());
			//return m_Root->GetMove();
			return mv;
		}
	}
	return Move(1, 1, KEY_S);
}

void StateHandler::GenerateNewPlays(std::vector<int>& t_current) {
	auto& t = m_Root->GetCurrentState();

	if (!IsEqual(t_current, t)) {
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
	states.clear();
	auto& map = t_root->GetCurrentState();
	for (int i = 0; i < m_Height; i++) {
		for (int j = 0; j < m_Width; j++) {
			if (map[i * m_Width + j] != KEY_EMPTY) {
				continue;
			}
			std::shared_ptr<GameState> temp1 = std::make_shared<GameState>(t_root, Move(j + 1, i + 1, KEY_O), m_Width, m_Height);
			states.push_back(temp1);

			std::shared_ptr<GameState> temp2 = std::make_shared<GameState>(t_root, Move(j + 1, i + 1, KEY_S), m_Width, m_Height);
			states.push_back(temp2);
			
			RecursiveCreate(temp1, t_depth + 1);
			RecursiveCreate(temp2, t_depth + 1);
		}
	}

}

#include <iostream>

//int StateHandler::RecursiveAssignPoints(std::shared_ptr<GameState> t_root, int t_depth, int max_prune, int min_prune, int t_score) {
//
//	int heuristic_value = 0;
//	if (t_root->GetStateType() == StateType::TYPE_MAX) {
//		heuristic_value = t_score - heuristic->Evaluate(t_root);
//	} else {
//		heuristic_value = t_score + heuristic->Evaluate(t_root);
//	}
//
//	if (t_depth == 4) {
//		return heuristic_value; // apply heuristic to the root
//	}
//
//	//t_root->SetScore(0);
//
//	auto& states = t_root->GetNextStates();
//	
//	int minmax;
//	if (t_root->GetStateType() == StateType::TYPE_MAX) {
//		minmax = INT_MIN;
//		for (auto& state : states) {
//			int val = RecursiveAssignPoints(state, t_depth + 1, minmax, min_prune, 0);
//			if (t_depth == 0) {
//				std::cout << state->GetMove().pos_y << ", " << state->GetMove().pos_x << " " << Move::CastKey(state->GetMove().key) << " : " << val << std::endl;
//			}
//			state->SetScore(val);
//			if (val > min_prune) {
//				return val;
//			}
//			if (val > minmax) {
//				minmax = val;
//			}
//		}
//	} else {
//		minmax = INT_MAX;
//		for (auto& state : states) {
//			int val = RecursiveAssignPoints(state, t_depth + 1, max_prune, minmax, 0);
//			state->SetScore(val);
//			if (t_depth == 0) {
//				std::cout << state->GetMove().pos_y << ", " << state->GetMove().pos_x << " " << Move::CastKey(state->GetMove().key) << " : " << val << std::endl;
//			}
//			if (val < max_prune) {
//				return val;
//			}
//			if (val < minmax) {
//				minmax = val;
//			}
//		}
//	}
//	return minmax;
//}

int StateHandler::RecursiveAssignPoints(std::shared_ptr<GameState> t_root, int t_depth, int max_prune, int min_prune, int t_score) {
	int heuristic_val = t_score + heuristic->Evaluate(t_root);
	if (t_depth == 4) {
		return heuristic_val;
	}

	t_root->SetScore(heuristic_val);

	auto& states = t_root->GetNextStates();
	int minmax;
	if (t_root->GetStateType() == StateType::TYPE_MAX) {
		minmax = INT_MIN;
		for (auto state : states) {
			int val = RecursiveAssignPoints(state, t_depth+1, minmax, min_prune, t_root->GetScore());
			state->SetScore(val);
			if (val > min_prune) {
				return val;
			}
			if (val > minmax) {
				minmax = val;
			}
		}
	} else {
		minmax = INT_MAX;
		for (auto state : states) {
			int val = RecursiveAssignPoints(state, t_depth + 1, max_prune, minmax, t_root->GetScore());
			state->SetScore(val);
			if (val < max_prune) {
				return val;
			}
			if (val < minmax) {
				minmax = val;
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
