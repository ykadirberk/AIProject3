#pragma once

#include "../Heuristic.h"

class SimpleHeuristic : public Heuristic {
	public:
		SimpleHeuristic();
		virtual ~SimpleHeuristic() {}
		int Evaluate(std::shared_ptr<GameState> t_state) override;
	private:
		int CheckSos(std::shared_ptr<GameState> t_state);

};