#include <iostream>
#include "GameManager.h"
#include "Player.h"
#include "Draw.h"

int Player::get_rolls() { return rolls; }
void Player::set_rolls(int rolls) { this->rolls = rolls; }
std::string Player::get_username() { return username; } 
void Player::set_username(std::string username) { this->username = username; }
void Player::set_turn(int turn) { this->turn = turn; }
int Player::get_turn() { return turn; }
void Player::set_points(int points) { this->points = points; }
int Player::get_points() { return points; }
int* Player::get_dices() { return currentDices; }
bool Player::get_turn_is_over() { return this->turnIsOver; }
void Player::set_turn_is_over(bool isOver) { this->turnIsOver = isOver; }

Player::Player()
{
	this->turn = 0;
	this->points = 0;
	this->rolls = 0;
}

void Player::play_turn()
{
	if (GameManager::get_instance().get_multiplayer())
	{
		if (!this->get_turn_is_over())
		{
			if (rolls == 0)
				this->roll_dice();

			Draw::draw_ui(this);
		}
	}
	else
	{
		if (rolls == 0)
			this->roll_dice();

		Draw::draw_ui(this);
	}
}

void Player::roll_dice()
{
	int* dices = new int[5];

	for (int i = 0; i < 5; i++)
		dices[i] = GameManager::get_instance().get_random(true);

	this->rolls++;
	this->currentDices = dices;
}

void Player::reroll(int index)
{
	currentDices[index - 1] = GameManager::get_instance().get_random(true);
}

