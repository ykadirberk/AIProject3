#pragma once

#include "../Move/Move.h"
#include "../StateHandler/StateHandler.h"

class Player {
	public:
		Player() {}
		virtual ~Player() {}
		virtual Move MakeMove(std::shared_ptr<StateHandler> handler, std::vector<int>& t_current) = 0;
		virtual std::string GetName() = 0;
	private:


};