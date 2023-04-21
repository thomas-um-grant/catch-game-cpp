/*
CS 3150
October 26, 2020
*/
#pragma once 
#include <string>

using namespace std;

enum STATE{alive, dead};
enum COLLECT{Not_collected, collected};

struct Hero
{
	string name;
	int y_hero;
	int x_hero;
	STATE state;
};

struct Badguy
{
	int y_badguy;
	int x_badguy;
};

struct Door
{
	int y_door;
	int x_door;
};

struct Coin
{
	int y_coin;
	int x_coin;
	COLLECT collect_status;

};

extern char* map;
extern struct Hero h;
extern struct Badguy badguys[];
extern struct Door doors[];
extern struct Coin coins[];
extern int coinsCollected;
extern int highscore;

void create_map(char map[], int widthMap);
void create_badguys(char map[], int heightMap, int widthMap, Badguy badguys[], int sizeBadguys);
void create_doors(char map[], int heightMap, int widthMap, Door doors[], int sizeDoors);
void teleport(char map[], int heightMap, int widthMap, Hero *h, Door doors[], int sizeDoors);
void create_coins(char map[], int heightMap, int widthMap, Coin coins[], int sizeCoins);
void collect_check(char map[], Hero *h, Coin coins[], int sizeCoins);
void draw_map(char map[], int heightMap, int widthMap, Hero *h, Badguy badguys[], int sizeBadguys, Door doors[], int sizeDoors, Coin coins[], int sizeCoins);
float distance_characters(int x1, int y1, int x2, int y2);
void sortArray(float arr[], int n);
void move_hero(char map[], int widthMap, Hero *h);
void move_badguys(char map[], int widthMap, Hero h, Badguy badguys[], int sizeBadguys);
void display_menu();
bool ask_to_play();
void display_instructions();