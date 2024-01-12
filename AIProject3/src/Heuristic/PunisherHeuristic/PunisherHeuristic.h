#pragma once

#include "../Heuristic.h"

class PunisherHeuristic : public Heuristic {
	public:
		PunisherHeuristic();
		virtual ~PunisherHeuristic() {}
		int Evaluate(std::shared_ptr<GameState> t_state) override;
};