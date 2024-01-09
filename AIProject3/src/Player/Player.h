#pragma once

#include "../Move/Move.h"

class Player {
	public:
		Player() {}
		virtual ~Player() {}
		virtual Move MakeMove() = 0;
		virtual std::string GetName() = 0;
	private:


};