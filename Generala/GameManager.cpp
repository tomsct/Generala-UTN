#include <random>
#include <algorithm>
#include <vector>
#include "GameManager.h"

int GameManager::get_round() {  return this->round; }
void GameManager::set_round(int round) { this->round = round; }
bool GameManager::get_game_is_over() { return this->gameOver; }
void GameManager::set_game_is_over(bool gameIsOver) { this->gameOver = gameIsOver; }
void GameManager::set_multiplayer(bool multiplayer) { this->multiplayer = multiplayer; }
bool GameManager::get_multiplayer() { return this->multiplayer; }
void GameManager::set_high_score(int score) { this->highScore = score; }
int GameManager::get_high_score() { return this->highScore; }
void GameManager::set_high_player(std::string player) { this->highPlayer = player; }
std::string GameManager::get_high_player() { return this->highPlayer; }

void GameManager::start_game(bool multiplayer)
{
	set_game_is_over(false);
	set_round(1);
	set_multiplayer(multiplayer);
	if (!multiplayer)
	{
		Player* player = new Player;
		player->set_username(Draw::draw_username_set());
		player->play_turn();
	}
	else
	{
		Player* player1 = new Player;
		Player* player2 = new Player;

		player1->set_username(Draw::draw_username_set());
		player2->set_username(Draw::draw_username_set());

		multiplayer_manager(player1, player2);
	}
}

void GameManager::multiplayer_manager(Player* player1, Player* player2)
{
	while (get_round() <= 3 && !get_game_is_over())
	{
		Draw::draw_scores_ui(player1);
		player1->play_turn();
		player1->set_turn_is_over(true);
		Draw::draw_scores_ui(player2);
		player2->play_turn();
		player1->set_turn_is_over(true);
		set_round(get_round() + 1);
		player1->set_turn_is_over(false);
		player2->set_turn_is_over(false);
	} 

	if (player1->get_points() > player2->get_points())
		Draw::draw_game_over_ui(player1);
	else
		Draw::draw_game_over_ui(player2);
}

int GameManager::check_dices(int* currentDices, Player* player)
{
	int* dices = new int[5];

	for (int i = 0; i < 5; i++)
		dices[i] = currentDices[i];

	std::sort(dices, dices + 5);

	if (is_generala(dices))
	{
		if (player->get_rolls() == 1)
			this->gameOver = true;

		return 50;
	}
	if (is_poker(dices)) return 40;
	if(is_full(dices)) return 30;
	if (is_stairs(dices))return 25;
	return dice_combination(dices);
}

int GameManager::dice_combination(int* dices)
{
	int maxCombination = 0;

	for (int i = 0; i < 4; i++)
	{
		int count = 1;
		for (int j = i + 1; j < 5; j++)
		{
			if (dices[i] == dices[j]) count++;
		}
		if (dices[i] * count > maxCombination) maxCombination = dices[i] * count;
	}

	if (maxCombination < dices[4]) return dices[4];	

	return maxCombination;
}

bool GameManager::is_stairs(int* dices)
{
	bool isStairs = true;

	for (int i = 1; i < 5; i++)
		if (dices[i] - dices[i - 1] != 1) isStairs = false;

	return isStairs;
}

bool GameManager::is_full(int* dices)
{
	if (dices[0] == dices[1] && dices[2] == dices[3] && dices[3] == dices[4]) return true;
	if (dices[0] == dices[1] && dices[1] == dices[2] && dices[3] == dices[4]) return true;

	return false;
}

bool GameManager::is_poker(int* dices)
{
	bool isPoker = false;
	for (int i = 0; i < 4; i++)
	{
		int count = 1;
		for (int j = i + 1; j < 5; j++) 
		{
			if (dices[i] == dices[j]) count++;
		}
		if (count == 4) isPoker = true;
	}
	return isPoker;
}

bool GameManager::is_generala(int* dices)
{
	bool isGenerala = true;

	for (int i = 0; i < 5; i++)
		if (dices[0] != dices[i]) isGenerala = false;

	return isGenerala;
}

int GameManager::get_random(bool isRandom)
{
	if (isRandom)
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 6); // distribution in range [1, 6]
		return dist6(rng);
	}
	else
	{
		int number;
		std::cin >> number;
		return number;
	}
}