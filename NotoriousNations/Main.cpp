#include "Game.hpp"

int main()
{
	Game game_game = Game();

	while (game_game.b_is_running())
	{
		game_game.update();
		game_game.late_update();
		game_game.draw();
		game_game.update_delta_time();
	}
}