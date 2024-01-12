#pragma once

#include "../Move/Move.h"
#include "../StateHandler/StateHandler.h"

class Player {
	public:
		Player() {}
		virtual ~Player() {}
		virtual Move MakeMove(StateHandler& handler) = 0;
		virtual std::string GetName() = 0;
	private:


};