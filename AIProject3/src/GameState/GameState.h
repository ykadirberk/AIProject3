#pragma once

#include "../Move/Move.h"

#include <vector>
#include <memory>

enum class StateType {
	TYPE_MAX,
	TYPE_MIN
};

class GameState {
	public:
		GameState(std::shared_ptr<GameState> t_parent, Move t_move, int t_width, int t_height);
		~GameState();
		
		std::vector<std::shared_ptr<GameState>>& GetNextStates();
		std::vector<int>& GetCurrentState();
		
		/*std::shared_ptr<GameState> GetParent();
		void SetParent(std::shared_ptr<GameState> t_parent);*/

		Move GetMove();
		
		int GetScore();
		void SetScore(int t_score);

		StateType GetStateType();
		void SetStateType(StateType t_state);

		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }
		
	private:
		int m_Score = 0;
		StateType m_StateType;
		Move m_Move;
		
		int m_Width;
		int m_Height;

		//std::shared_ptr<GameState> m_ParentState;
		std::vector<std::shared_ptr<GameState>> m_NextStates;
		std::vector<int> m_CurrentState;

};