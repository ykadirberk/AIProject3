#include "PunisherHeuristic.h"

PunisherHeuristic::PunisherHeuristic()
{
}

int PunisherHeuristic::Evaluate(std::shared_ptr<GameState> t_state) {
	//int base_score = t_state->GetScore();
	int base_score = 0;
	int punishment = 0;
	if (t_state->GetMove().key == KEY_S) {
		punishment = CheckPunishmentKeyS(t_state);
	} else {
		punishment = CheckPunishmentKeyO(t_state);
	}

	int sos = CheckSos(t_state);

	if (t_state->GetStateType() == StateType::TYPE_MAX) {
		base_score = base_score + punishment * 2 - sos * 4;
	} else {
		base_score = base_score - punishment * 1 + sos * 4;
	}

	return base_score;
}
int PunisherHeuristic::CheckSos(std::shared_ptr<GameState> t_state) {
	int score = 0;
	auto move = t_state->GetMove();
	auto map = t_state->GetCurrentState();

	// horizontal to the left
	if (move.pos_x - 3 >= 0
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 1] == KEY_S
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 2] == KEY_O
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 3] == KEY_S) {
		score++;
	}

	// horizontal to the right
	if (move.pos_x + 1 < t_state->GetWidth()
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 1] == KEY_S
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x] == KEY_O
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x + 1] == KEY_S) {
		score++;
	}

	// vertical to the top
	if (move.pos_y - 3 >= 0
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 1] == KEY_S
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x - 1] == KEY_O
		&& map[(move.pos_y - 3) * t_state->GetWidth() + move.pos_x - 1] == KEY_S) {
		score++;
	}

	// vertical to the bottom
	if (move.pos_y + 1 < t_state->GetHeight()
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 1] == KEY_S
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x - 1] == KEY_O
		&& map[(move.pos_y + 1) * t_state->GetWidth() + move.pos_x - 1] == KEY_S) {
		score++;
	}

	// diagonal to the bottom right
	if (move.pos_y + 1 < t_state->GetHeight() && move.pos_x + 1 < t_state->GetWidth()
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 1] == KEY_S
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x] == KEY_O
		&& map[(move.pos_y + 1) * t_state->GetWidth() + move.pos_x + 1] == KEY_S) {
		score++;
	}

	// diagonal to the top left
	if (move.pos_y - 3 >= 0 && move.pos_x - 3 >= 0
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 1] == KEY_S
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x - 2] == KEY_O
		&& map[(move.pos_y - 3) * t_state->GetWidth() + move.pos_x - 3] == KEY_S) {
		score++;
	}

	// diagonal to the bottom left
	if (move.pos_y + 1 < t_state->GetHeight() && move.pos_x - 3 >= 0
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 1] == KEY_S
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x - 2] == KEY_O
		&& map[(move.pos_y + 1) * t_state->GetWidth() + move.pos_x - 3] == KEY_S) {
		score++;
	}

	// diagonal to the top right
	if (move.pos_y - 3 >= 0 && move.pos_x + 1 < t_state->GetWidth()
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 1] == KEY_S
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x] == KEY_O
		&& map[(move.pos_y - 3) * t_state->GetWidth() + move.pos_x + 1] == KEY_S) {
		score++;
	}

	///////////////////////////////////////////////////////////////////////////////////
	// horizontal to the left
	if (move.pos_x - 2 >= 0 && move.pos_x < t_state->GetWidth()
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 1] == KEY_O
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 2] == KEY_S
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x] == KEY_S) {
		score++;
	}

	// vertical to the bottom
	if (move.pos_y + 1 < t_state->GetHeight() && move.pos_y - 2 >= 0
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 1] == KEY_O
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x - 1] == KEY_S
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x - 1] == KEY_S) {
		score++;
	}
	// diagonal to the top left
	if (move.pos_y + 1 < t_state->GetHeight() && move.pos_y - 2 >= 0 && move.pos_x + 1 < t_state->GetWidth() && move.pos_x - 2 >= 0
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 1] == KEY_O
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x - 2] == KEY_S
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x] == KEY_S) {
		score++;
	}

	// diagonal to the top right
	if (move.pos_y + 1 < t_state->GetHeight() && move.pos_y - 2 >= 0 && move.pos_x + 1 < t_state->GetWidth() && move.pos_x - 2 >= 0
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 1] == KEY_O
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x] == KEY_S
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x - 2] == KEY_S) {
		score++;
	}

	return score;
}

int PunisherHeuristic::CheckPunishmentKeyS(std::shared_ptr<GameState> t_state) {
	int punishment = 0;
	auto move = t_state->GetMove();
	auto map = t_state->GetCurrentState();

	// horizontal to the left
	if ( move.pos_x - 3 >= 0
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 2] == KEY_O
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 3] == KEY_EMPTY) {
		punishment++;
	}

	// horizontal to the right
	if (move.pos_x + 1 < t_state->GetWidth()
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x] == KEY_O
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x + 1] == KEY_EMPTY) {
		punishment++;
	}

	// vertical to the top
	if (move.pos_y - 3 >= 0
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x - 1] == KEY_O
		&& map[(move.pos_y - 3) * t_state->GetWidth() + move.pos_x - 1] == KEY_EMPTY) {
		punishment++;
	}

	// vertical to the bottom
	if (move.pos_y + 1 < t_state->GetHeight()
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x - 1] == KEY_O
		&& map[(move.pos_y + 1) * t_state->GetWidth() + move.pos_x - 1] == KEY_EMPTY) {
		punishment++;
	}

	// diagonal to the bottom right
	if (move.pos_y + 1 < t_state->GetHeight() && move.pos_x + 1 < t_state->GetWidth()
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x] == KEY_O
		&& map[(move.pos_y + 1) * t_state->GetWidth() + move.pos_x + 1] == KEY_EMPTY) {
		punishment++;
	}

	// diagonal to the top left
	if (move.pos_y - 3 >= 0 && move.pos_x - 3 >= 0
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x - 2] == KEY_O
		&& map[(move.pos_y - 3) * t_state->GetWidth() + move.pos_x - 3] == KEY_EMPTY) {
		punishment++;
	}

	// diagonal to the bottom left
	if (move.pos_y + 1 < t_state->GetHeight() && move.pos_x - 3 >= 0
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x - 2] == KEY_O
		&& map[(move.pos_y + 1) * t_state->GetWidth() + move.pos_x - 3] == KEY_EMPTY) {
		punishment++;
	}

	// diagonal to the top right
	if (move.pos_y - 3 >= 0 && move.pos_x + 1 < t_state->GetWidth()
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x] == KEY_O
		&& map[(move.pos_y - 3) * t_state->GetWidth() + move.pos_x + 1] == KEY_EMPTY) {
		punishment++;
	}

	///////////////////////////////////////////////////////////////////////////////////
	// horizontal to the left
	if (move.pos_x - 3 >= 0
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 2] == KEY_EMPTY
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 3] == KEY_S) {
		punishment++;
	}

	// horizontal to the right
	if (move.pos_x + 1 < t_state->GetWidth()
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x] == KEY_EMPTY
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x + 1] == KEY_S) {
		punishment++;
	}

	// vertical to the top
	if (move.pos_y - 3 >= 0
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x - 1] == KEY_EMPTY
		&& map[(move.pos_y - 3) * t_state->GetWidth() + move.pos_x - 1] == KEY_S) {
		punishment++;
	}

	// vertical to the bottom
	if (move.pos_y + 1 < t_state->GetHeight()
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x - 1] == KEY_EMPTY
		&& map[(move.pos_y + 1) * t_state->GetWidth() + move.pos_x - 1] == KEY_S) {
		punishment++;
	}

	// diagonal to the bottom right
	if (move.pos_y + 1 < t_state->GetHeight() && move.pos_x + 1 < t_state->GetWidth()
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x] == KEY_EMPTY
		&& map[(move.pos_y + 1) * t_state->GetWidth() + move.pos_x + 1] == KEY_S) {
		punishment++;
	}

	// diagonal to the top left
	if (move.pos_y - 3 >= 0 && move.pos_x - 3 >= 0
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x - 2] == KEY_EMPTY
		&& map[(move.pos_y - 3) * t_state->GetWidth() + move.pos_x - 3] == KEY_S) {
		punishment++;
	}

	// diagonal to the bottom left
	if (move.pos_y + 1 < t_state->GetHeight() && move.pos_x - 3 >= 0
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x - 2] == KEY_EMPTY
		&& map[(move.pos_y + 1) * t_state->GetWidth() + move.pos_x - 3] == KEY_S) {
		punishment++;
	}

	// diagonal to the top right
	if (move.pos_y - 3 >= 0 && move.pos_x + 1 < t_state->GetWidth()
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x] == KEY_EMPTY
		&& map[(move.pos_y - 3) * t_state->GetWidth() + move.pos_x + 1] == KEY_S) {
		punishment++;
	}

	return punishment;
}

int PunisherHeuristic::CheckPunishmentKeyO(std::shared_ptr<GameState> t_state) {
	int punishment = 0;
	auto move = t_state->GetMove();
	auto map = t_state->GetCurrentState();
	
	// horizontal to the left
	if (move.pos_x - 2 >= 0 && move.pos_x < t_state->GetWidth()
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 2] == KEY_S
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x] == KEY_EMPTY) {
		punishment++;
	}

	// horizontal to the right
	if (move.pos_x + 1 < t_state->GetWidth() && move.pos_x - 2 >= 0
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x] == KEY_S
		&& map[(move.pos_y - 1) * t_state->GetWidth() + move.pos_x - 2] == KEY_EMPTY) {
		punishment++;
	}

	// vertical to the top
	if (move.pos_y - 2 >= 0 && move.pos_y < t_state->GetHeight()
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x - 1] == KEY_S
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x - 1] == KEY_EMPTY) {
		punishment++;
	}

	// vertical to the bottom
	if (move.pos_y + 1 < t_state->GetHeight() && move.pos_y - 2 >= 0
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x - 1] == KEY_S
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x - 1] == KEY_EMPTY) {
		punishment++;
	}

	// diagonal to the bottom right
	if (move.pos_y - 2 >= 0 && move.pos_y < t_state->GetHeight() && move.pos_x + 1 < t_state->GetWidth() && move.pos_x - 2 >= 0
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x] == KEY_S
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x - 2] == KEY_EMPTY) {
		punishment++;
	}

	// diagonal to the top left
	if (move.pos_y + 1 < t_state->GetHeight() && move.pos_y - 2 >= 0 && move.pos_x + 1 < t_state->GetWidth() && move.pos_x - 2 >= 0
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x - 2] == KEY_S
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x] == KEY_EMPTY) {
		punishment++;
	}

	// diagonal to the bottom left
	if (move.pos_y - 2 >= 0 && move.pos_y < t_state->GetHeight() && move.pos_x + 1 < t_state->GetWidth() && move.pos_x - 2 >= 0
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x - 2] == KEY_S
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x] == KEY_EMPTY) {
		punishment++;
	}

	// diagonal to the top right
	if (move.pos_y + 1 < t_state->GetHeight() && move.pos_y - 2 >= 0 && move.pos_x + 1 < t_state->GetWidth() && move.pos_x - 2 >= 0
		&& map[(move.pos_y - 2) * t_state->GetWidth() + move.pos_x] == KEY_S
		&& map[(move.pos_y) * t_state->GetWidth() + move.pos_x - 2] == KEY_EMPTY) {
		punishment++;
	}

	return punishment;
}
