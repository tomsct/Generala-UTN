#pragma once
#include <iostream>

class Player
{
private:
	std::string username;
	int turn;
	int points;
	int rolls;
	int* currentDices;
	bool turnIsOver;

public:
	Player();
	void set_username(std::string username);
	std::string get_username();
	int* get_dices();
	int get_rolls();
	void set_rolls(int rolls);
	void set_turn(int turn);
	int get_turn();
	void set_points(int points);
	int get_points();
	void roll_dice();
	void reroll(int index);
	void play_turn();
	bool get_turn_is_over();
	void set_turn_is_over(bool isOver);
};


