/*
CS 3150
October 26, 2020

Used main.cpp to run the main program
Used functions.cpp to store all the functions used in main
Used functions.h to reference all our functions across the entire program
Used a ENUM to check for the hero's status and end the game accordingly
Used extern variables to be accessible from all our functions as needed
Didn't need to use a static variable as all our variables were being used in multiple files
Used structs for hero, badguy, door and coin
Used random numbers to spawn ennemies and items on the map
Used a txt file to load the map, so we can easily build other maps if we want to.
*/
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <math.h>
#include "functions.h"

using namespace std;

char* map = new char[20*60];
struct Hero h = {"Hero", 11, 29, alive};
struct Badguy badguys[10];
struct Door doors[4];
struct Coin coins[20];
int highscore = 0;

int main()
{

	bool program_running = true;
	bool game_running;
	int turn;
	//initialize game variables
	int heightMap = 20;
	int widthMap = 60;
	int sizeBadguys = 10;
	int sizeDoors = 4;
	int sizeCoins = 20;

	//Create game
	create_map(map, widthMap);
	create_badguys(map, heightMap, widthMap, badguys, sizeBadguys);
	create_doors(map, heightMap, widthMap, doors, sizeDoors);
	create_coins(map, heightMap, widthMap, coins, sizeCoins);

	//Run game
	//Instructions
	display_menu();
	bool start = ask_to_play();
	//Press start
	if(start){
		game_running = true;
		turn = 0;
		coinsCollected = 0;
	}
	else{
		program_running = false;
	}
	while(game_running)
	{
		system("cls");
		draw_map(map, heightMap, widthMap, &h, badguys, sizeBadguys, doors, sizeDoors, coins, sizeCoins);
		
		cout << "\nTurns: " << turn++ << endl;
		cout << "Coins: " << coinsCollected << endl;
		cout << "State: " << h.state << endl;
		display_instructions();
		system("pause>nul");
		move_hero(map, widthMap, &h);
		move_badguys(map, widthMap, h, badguys, sizeBadguys);

		for(int i=0; i<sizeBadguys; i++)
		{
			if((h.x_hero == badguys[i].x_badguy) && (h.y_hero == badguys[i].y_badguy))
			{
				h.state = dead;
			}
		}

		if(h.state == dead)
		{
			game_running = false;
			cout << endl;
			cout << "*****************************" << endl;
			cout << "***       GAME OVER       ***" << endl;
			cout << "*** Thank you for playing ***" << endl;
			cout << "*****************************" << endl << endl;
			system("pause>nul");
		}
		else if(coinsCollected == 20)
		{
			game_running = false;
			if(highscore > turn)
			{
				highscore = turn;
			}
			cout << endl;
			cout << "*****************************" << endl;
			cout << "***       YOU WON!        ***" << endl;
			cout << "*** Thank you for playing ***" << endl;
			cout << "*****************************" << endl << endl;
			system("pause>nul");
		}
	}
}