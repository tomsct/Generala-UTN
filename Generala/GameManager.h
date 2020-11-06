#pragma once
#include "Draw.h"
#include "Player.h"

class GameManager
{
private:
	int round = 1;
	bool multiplayer = false;
	bool gameOver;
	int highScore = 0;
	std::string highPlayer;
	GameManager() {}
	GameManager(GameManager const&);              // Don't Implement
	void operator=(GameManager const&);			 // Don't implement

public:
	static GameManager& get_instance()
	{
		static GameManager instance; // Guaranteed to be destroyed.
		return instance;				// Instantiated on first use.
	}
	void start_game(bool multiplayer);
	void multiplayer_manager(Player* player1, Player* player2);
	int get_round();
	void set_round(int round);
	int get_random(bool isRandom);
	int check_dices(int* currentDices, Player* player);
	void set_high_score(int score);
	int get_high_score();
	void set_game_is_over(bool gameIsOVer);
	bool get_game_is_over();
	void set_multiplayer(bool multiplayer);
	bool get_multiplayer();
	bool is_generala(int* currentDices);
	bool is_poker(int* currentDices);
	bool is_full(int* currentDices); 
	bool is_stairs(int* currentDices);
	int dice_combination(int* dices);
	void set_high_player(std::string player);
	std::string get_high_player();
	
};
