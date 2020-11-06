#pragma once
#include <iostream>
#include "Player.h"

static class Draw
{
public:
	static void console_config();
	static void draw_questions(Player* player);
	static void draw_menu();	
	static std::string draw_username_set();
	static void draw_dices(int* dices);
	static void draw_ui(Player* player);
	static void draw_scores_ui(Player* player);
	static void draw_game_over_ui(Player* player);
	static void draw_high_score();
};