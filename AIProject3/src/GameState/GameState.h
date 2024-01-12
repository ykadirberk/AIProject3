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
		
		Move GetMove();
		
		int GetScore();

		int GetMinPlayerScore();
		void SetMinPlayerScore(int t_score);
		int GetMaxPlayerScore();
		void SetMaxPlayerScore(int t_score);

		StateType GetStateType();
		void SetStateType(StateType t_state);
		
	private:
		int m_ScoreMaxPlayer;
		int m_ScoreMinPlayer;
		int m_Score = 0;
		StateType m_StateType;
		Move m_Move;
		
		int m_Width;
		int m_Height;

		std::weak_ptr<GameState> m_ParentState;
		std::vector<std::shared_ptr<GameState>> m_NextStates;
		std::vector<int> m_CurrentState;

};