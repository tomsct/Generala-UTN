#pragma once
#include <iostream>
#include <string.h>
#include <conio.h>
#include "rlutil.h"
#include "GameManager.h"
#include "Player.h"
#include "Draw.h"

void Draw::draw_menu()
{
	GameManager::get_instance().set_game_is_over(false);
	int key;
	std::pair<int, int> coordenates{ 1,2 };

	do
	{
		system("cls");
		rlutil::locate(1, 1);
		std::cout << "--------------- MENU PRINCIPAL ---------------";
		rlutil::locate(2, 2);
		std::cout << "\t1 - SinglePlayer" << std::endl;
		std::cout << "\t2 - MultiPlayer" << std::endl;
		std::cout << "\t3 - High Scores" << std::endl;
		std::cout << "\t0 - Exit " << std::endl;

		rlutil::locate(coordenates.first, coordenates.second);
		std::cout << ">>";

		key = rlutil::getkey();

		switch (key)
		{
		case 14:
			if (coordenates.second > 2)
				coordenates.second--;
			break;
		case 15:
			if (coordenates.second < 5)
				coordenates.second++;
			break;
		default:
			break;
		}
	} while (key != 1);

	switch (coordenates.second)
	{
	case 2:
		GameManager::get_instance().start_game(false);
		break;
	case 3:
		GameManager::get_instance().start_game(true);
		break;
	case 4:
		Draw::draw_high_score();
		break;
	case 5:
		//exit
		break;
	default:
		break;
	}
}

std::string Draw::draw_username_set()
{
	std::string username;
	system("cls");
	std::cout << "INGRESE SU NOMBRE : ";
	std::cin >> username;

	return username;
}

void Draw::draw_ui(Player* player)
{
	if (!GameManager::get_instance().get_game_is_over())
	{
		do
		{
			//Draw::console_config();
			system("cls");
			rlutil::locate(1, 1);
			std::cout << "\tTURNO DE " << player->get_username() << "\t|";
			std::cout << "\tRONDA N # " << GameManager::get_instance().get_round() << "\t|";
			std::cout << "\tPUNTAJE TOTAL : " << player->get_points() << std::endl;
			std::cout << "-------------------------------------------------------------------------" << std::endl << std::endl;
			std::cout << "LANZAMIENTO N # " << player->get_rolls() << std::endl;
			std::cout << "-------------------------------------------------------------------------" << std::endl;

			draw_dices(player->get_dices());

			if (player->get_rolls() < 3)
				draw_questions(player);
			else
				break;
		} while (player->get_rolls() <= 3 && !player->get_turn_is_over());
		
		std::cout << std::endl << "-------------------------------------------------------------------------";
		std::cout << std::endl << "\nPUNTAJE DEL TURNO : " << GameManager::get_instance().check_dices(player->get_dices(), player);
		player->set_points(player->get_points() + GameManager::get_instance().check_dices(player->get_dices(), player));
		player->set_rolls(0);
		if(!GameManager::get_instance().get_multiplayer())
			GameManager::get_instance().set_round(GameManager::get_instance().get_round() + 1);
		std::cout << std::endl << std::endl << "Presione Enter para continuar...";
		getch();
		if (GameManager::get_instance().get_round() <= 10 && !GameManager::get_instance().get_game_is_over())
		{
			if (!GameManager::get_instance().get_multiplayer())
				Draw::draw_scores_ui(player);
		}
		else if(!GameManager::get_instance().get_multiplayer())
			Draw::draw_game_over_ui(player);
	}
}

void Draw::draw_scores_ui(Player* player)
{
	system("cls");
	rlutil::locate(5, 1);
	std::cout << "----------------------------------------";
	rlutil::locate(15, 3);
	std::cout << "RONDA NUMERO # " << GameManager::get_instance().get_round() << std::endl;
	rlutil::locate(15, 5);
	std::cout << "NOMBRE DEL JUGADOR : " << player->get_username() << std::endl;
	rlutil::locate(15, 7);
	std::cout << "PUNTAJE : " << player->get_points();
	rlutil::locate(5, 9);
	std::cout << "----------------------------------------";
	std::cout << std::endl << std::endl << "Presione Enter para continuar...";
	getch();
	if (!GameManager::get_instance().get_multiplayer())
		player->play_turn();
}

void Draw::draw_questions(Player* player)
{
	char c;
	std::cout << std::endl << "\n¿CONTINUAR LANZANDO (S/N)? : ";
	std::cin >> c;

	bool keepRolling = toupper(c) == 'S';
	if (keepRolling)
	{
		std::string str;
		std::cout << "¿CUALES? : ";
		std::cin >> str;
		for (size_t i = 0; i < str.size(); i++)
		{
			int aux = str[i] - 48;
			if (aux > 0 && aux < 6)
				player->reroll(aux);
		}
		player->set_rolls(player->get_rolls() + 1);
		if(!GameManager::get_instance().get_multiplayer())
			Draw::draw_ui(player);
	}
	else
		player->set_turn_is_over(true);
}

void Draw::draw_dices(int* dices)
{
	for (int i = 0; i < 5; i++)
	{
		switch (dices[i])
		{
		case 1:
			std::cout << " 1 ";
			//std::cout << u8" ⚀ ";
			break;
		case 2:
			std::cout << " 2 ";
			//std::cout << u8" ⚁ ";
			break;
		case 3:
			std::cout << " 3 ";
			//std::cout << u8" ⚂ ";
			break;
		case 4:
			std::cout << " 4 ";
			//std::cout << u8" ⚃ ";
			break;
		case 5:
			std::cout << " 5 ";
			//std::cout << u8" ⚄ ";
			break;
		case 6:
			std::cout << " 6 ";
			//std::cout << u8" ⚅ ";
			break;
		}
	}
}

void Draw::draw_game_over_ui(Player* player)
{
	GameManager::get_instance().set_game_is_over(true);

	system("cls");
	rlutil::locate(10, 5);
	std::cout << "----------------- GAME OVER -----------------" << std::endl;
	rlutil::locate(15, 6);
	if (GameManager::get_instance().get_multiplayer())
		std::cout << "GANADOR : " << player->get_username();
	rlutil::locate(15, 7);
	std::cout << "PUNTUACION FINAL : " << player->get_points();
	rlutil::locate(10, 9);
	std::cout << "----------------- GAME OVER -----------------" << std::endl;
	if (player->get_points() > GameManager::get_instance().get_high_score())
	{
		GameManager::get_instance().set_high_score(player->get_points());
		GameManager::get_instance().set_high_player(player->get_username());
	}
	std::cout << std::endl << std::endl << "Presione Enter para continuar...";
	getch();
	Draw::draw_menu();
}

void Draw::draw_high_score()
{
	system("cls");
	std::cout << "EL MAYOR PUNTAJE ES : " << GameManager::get_instance().get_high_score() << std::endl;
	std::cout << "Y FUE CONSEGUIDO POR : " << GameManager::get_instance().get_high_player() << std::endl;
	std::cout << std::endl << std::endl << "Presione Enter para continuar...";
	getch();
	Draw::draw_menu();
}

void Draw::console_config()
{
	//Segoe UI Symbol

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 24;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Segoe UI Symbol");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	SetConsoleOutputCP(CP_UTF8);
	// Enable buffering to prevent VS from chopping up UTF-8 byte sequences
	setvbuf(stdout, nullptr, _IOFBF, 1000);
}
