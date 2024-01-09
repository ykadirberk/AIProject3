#pragma once

#include <string>
#include <sstream>

#include "../Utils.h"

class Move {
	public:
		Move() {}
		~Move() {}
		int pos_x = 0;
		int pos_y = 0;
		int key = 0;
		std::string ToString() {
			std::stringstream ss;
			ss << "(" << pos_x << ", " << pos_y << ") -> " << CastKey(key);
			return ss.str();
		}

		static std::string CastKey(int t_key) {
			if (t_key == KEY_S) {
				return "S";
			}
			if (t_key == KEY_O) {
				return "O";
			}	
			return " ";
		}

		static int CastStr(std::string t_str) {
			if (t_str == "S" || t_str == "s") {
				return KEY_S;
			}
			if (t_str == "O" || t_str == "o") {
				return KEY_O;
			}
			return KEY_EMPTY;
		}
};