#pragma once

#include "../GameState/GameState.h"
#include "../Heuristic/Heuristic.h"

#include <memory>
#include <vector>

class StateHandler {
	public:
		StateHandler(std::vector<int>& t_current, int t_width, int t_height, std::shared_ptr<Heuristic> t_heuristic);
		~StateHandler();

		void GenerateNewPlays(std::vector<int>& t_current);
		Move ChoosePlay();

	private:

		std::shared_ptr<GameState> m_Root;
		int m_Width;
		int m_Height;

		std::shared_ptr<Heuristic> heuristic;

		void RecursiveCreate(std::shared_ptr<GameState> t_root, int t_depth);
		int RecursiveAssignPoints(std::shared_ptr<GameState> t_root, int t_depth, int max_prune, int min_prune, int t_score);

		bool IsEqual(std::vector<int>& t1, std::vector<int>& t2);

};