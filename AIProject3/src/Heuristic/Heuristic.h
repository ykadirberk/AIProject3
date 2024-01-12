#pragma once

#include "../GameState/GameState.h"

class Heuristic {
	public:
		Heuristic() {}
		virtual ~Heuristic() {}
		virtual int Evaluate(std::shared_ptr<GameState> t_state) = 0;
};