#pragma once

#include "../Heuristic.h"

class PunisherHeuristic : public Heuristic {
	public:
		PunisherHeuristic();
		virtual ~PunisherHeuristic() {}
		int Evaluate(std::shared_ptr<GameState> t_state) override;
	private:
		int CheckSos(std::shared_ptr<GameState> t_state);
		int CheckPunishmentKeyS(std::shared_ptr<GameState> t_state);
		int CheckPunishmentKeyO(std::shared_ptr<GameState> t_state);

};