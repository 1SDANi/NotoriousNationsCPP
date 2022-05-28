#include "Game.hpp"

Game::Game() : window("Notorious Nations")
{
	testSprite.setTexture(*Globals::glob_get_globals().asmp_get_asset_maps().p_txtr_get_soil_cover_atlas());
}

void Game::update()
{
	window.update();
}

void Game::late_update()
{

}

void Game::draw()
{
	window.begin_draw();

	window.draw(testSprite);

	window.end_draw();
}

bool Game::b_is_running() const
{
	return window.b_is_open();
}