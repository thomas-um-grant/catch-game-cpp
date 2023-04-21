/*
CS 3150
October 26, 2020
*/
#include <iostream> //needed to display content
#include <fstream> //needed to load map
#include <windows.h> //needed for keystroke
#include <string> //needed for string
#include <math.h> //needed to calculate distance
#include<cstdlib>//needed for rand function
#include<ctime>//needed for clock generated seed
#include "functions.h"//needed to reference functions just in case since it doesn't hurt

using namespace std; //namespace to simplify code

int coinsCollected = 0;

void create_map(char map[], int widthMap)
{
	int c;
	ifstream inFile;
	
	inFile.open("map.txt");
	if(!inFile)
	{
		cout << "Unable to open file";
	}
	int rows = 0;
	for(string line; getline(inFile, line);)
	{
		for(int cols=0; cols<widthMap; cols++)
		{
			c = line[cols];

			if(c=='W')
			{
				map[rows*widthMap+cols] = '#';
			}
			else
			{
				map[rows*widthMap+cols] = ' ';
			}
		}
		rows++;
	}
	inFile.close();
}

void create_badguys(char map[], int heightMap, int widthMap, Badguy badguys[], int sizeBadguys)
{
	srand(53);//set initial seed to 5436
	rand();//call rand once to have "better" random numbers

	//Create the badguys
	for(int i=0; i<sizeBadguys; i++)
	{
		bool placed = false;
		int y_rand;
		int x_rand;

		while(!placed)
		{
			if(i<5)
			{
				y_rand = int((rand()%8));
				x_rand = int((rand()%widthMap)/5 + i*widthMap/5);
			}
			else
			{
				y_rand = int((rand()%7) + 13);
				x_rand = int((rand()%heightMap) + (i-5)*heightMap);
			}
			if(y_rand!=-1 && x_rand!=-1)
			{
				if(map[y_rand*widthMap+x_rand] != '#')
				{
					badguys[i].y_badguy = y_rand;
					badguys[i].x_badguy = x_rand;
					placed = true;
				}
			}
		}
	}
}

void create_doors(char map[], int heightMap, int widthMap, Door doors[], int sizeDoors)
{
	srand(5236);//set initial seed to 5436
	rand();//call rand once to have "better" random numbers

	//Create the doors
	for(int i=0; i<sizeDoors; i++)
	{
		bool placed = false;
		int y_rand;
		int x_rand;

		while(!placed)
		{
			if(i<2)
			{
				y_rand = int((rand()%8));
				x_rand = int((rand()%widthMap)/2 + i*widthMap/2);
			}
			else
			{
				y_rand = int((rand()%7) + 13);
				x_rand = int((rand()%widthMap)/2 + (i-2)*widthMap/2);
			}
			if(y_rand!=-1 && x_rand!=-1)
			{
				if((map[y_rand*widthMap+x_rand] != '#') && (map[y_rand*widthMap+x_rand] != '&'))
				{
					doors[i].y_door = y_rand;
					doors[i].x_door = x_rand;
					placed = true;
				}
			}
		}
	}
}

void teleport(char map[], int heightMap, int widthMap, Hero *h, Door doors[], int sizeDoors)
{
	srand(689);
	rand();

	//Check if hero teleports
	for(int i=0; i<sizeDoors; i++)
	{
		if((h->y_hero == doors[i].y_door) && (h->x_hero == doors[i].x_door))
		{
			if(i+1 == sizeDoors){
				i=-1;
			}
			h->y_hero = doors[i+1].y_door;
			h->x_hero = doors[i+1].x_door;
			break;
		}
	}
}

void create_coins(char map[], int heightMap, int widthMap, Coin coins[], int sizeCoins)
{
	srand(365);//set initial seed to 5436
	rand();//call rand once to have "better" random numbers

	//Create the doors
	for(int i=0; i<sizeCoins; i++)
	{
		bool placed = false;
		int y_rand;
		int x_rand;

		while(!placed)
		{
			if(i<10)
			{
				y_rand = int((rand()%8));
				x_rand = int((rand()%widthMap)/10 + i*widthMap/10);
			}
			else
			{
				y_rand = int((rand()%7) + 13);
				x_rand = int((rand()%widthMap)/10 + (i-10)*widthMap/10);
			}
			if(y_rand!=-1 && x_rand!=-1)
			{
				if((map[y_rand*widthMap+x_rand] != '#') && (map[y_rand*widthMap+x_rand] != '&') && (map[y_rand*widthMap+x_rand] != 'D'))
				{
					coins[i].y_coin = y_rand;
					coins[i].x_coin = x_rand;
					placed = true;
				}
			}
		}
	}
}

void collect_check(char map[], Hero *h, Coin coins[], int sizeCoins)
{
	for(int i=0; i<sizeCoins; i++)
	{
		if((h->x_hero == coins[i].x_coin) && (h->y_hero == coins[i].y_coin))
		{
			coins[i].x_coin = 0;
			coins[i].y_coin = 0;
			coins[i].collect_status = collected;
			coinsCollected++;
		}
	}
}

void draw_map(char map[], int heightMap, int widthMap, Hero *h, Badguy badguys[], int sizeBadguys, Door doors[], int sizeDoors, Coin coins[], int sizeCoins)
{
	//Check if teleport
	teleport(map, heightMap, widthMap, h, doors, sizeDoors);
	collect_check(map, h, coins, sizeCoins);

	//Add doors
	for(int i=0; i<sizeCoins; i++)
	{
		if((coins[i].y_coin != 0) && (coins[i].x_coin != 0))
		{
			map[coins[i].y_coin*widthMap+coins[i].x_coin] = 'O';
		}
	}

	//Add doors
	for(int i=0; i<sizeDoors; i++)
	{
		map[doors[i].y_door*widthMap+doors[i].x_door] = 'D';
	}

	//Add hero
	map[h->y_hero*widthMap+h->x_hero] = '@';

	//Add badguys
	for(int i=0; i<sizeBadguys; i++)
	{
		map[badguys[i].y_badguy*widthMap+badguys[i].x_badguy] = '&';
	}

	//Draw map
	for(int rows=0; rows<heightMap; rows++)
	{	
		for(int cols=0; cols<widthMap; cols++)
		{
			if(map[rows*widthMap+cols] == 'O')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << map[rows*widthMap+cols];
			}
			else if(map[rows*widthMap+cols] == 'D')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
				cout << map[rows*widthMap+cols];
			}
			else if(map[rows*widthMap+cols] == '@')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout << map[rows*widthMap+cols];
			}
			else if(map[rows*widthMap+cols] == '&')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cout << map[rows*widthMap+cols];
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << map[rows*widthMap+cols];
			}
		}
		cout << endl;
	}
}

float distance_characters(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x2-x1,2)+pow(y2-y1,2)*1.0);
}

//Sort algo found at https://www.geeksforgeeks.org/insertion-sort/
//Using this alog because the sort from <algorithm> doesn't work with my compiler
void sortArray(float arr[], int n)  
{  
    int i, j;
    float key;
    for (i = 1; i < n; i++) 
    {  
        key = arr[i];  
        j = i - 1;  
        while (j >= 0 && arr[j] > key) 
        {  
            arr[j + 1] = arr[j];  
            j = j - 1;  
        }  
        arr[j + 1] = key; 
    }  
}

void move_hero(char map[], int widthMap, Hero *h)
{
	bool moved = false;

	while (!moved)
	{
		if(GetAsyncKeyState(VK_UP))
		{
			int y = h->y_hero-1;
			if(map[y*widthMap+h->x_hero] != '#')
			{
				map[h->y_hero*widthMap+h->x_hero]=' ';
				h->y_hero--;
				moved = true;
			}
		}

		if(GetAsyncKeyState(VK_DOWN))
		{
			int y = h->y_hero+1;
			if(map[y*widthMap+h->x_hero] != '#')
			{
				map[h->y_hero*widthMap+h->x_hero]=' ';
				h->y_hero++;
				moved = true;
			}
		}

		if(GetAsyncKeyState(VK_RIGHT))
		{
			int x = h->x_hero+1;
			if(map[h->y_hero*widthMap+x] != '#')
			{
				map[h->y_hero*widthMap+h->x_hero]=' ';
				h->x_hero++;
				moved = true;
			}
		}

		if(GetAsyncKeyState(VK_LEFT))
		{
			int x = h->x_hero-1;
			if(map[h->y_hero*widthMap+x] != '#')
			{
				map[h->y_hero*widthMap+h->x_hero]=' ';
				h->x_hero--;
				moved = true;
			}
		}
	}
}

void move_badguys(char map[], int widthMap, Hero h, Badguy badguys[], int sizeBadguys)
{	
	for(int i=0; i<sizeBadguys; i++)
	{
		int index = 0;
		bool moved = false;

		// UP - direction
		float upDist = distance_characters(h.x_hero, h.y_hero, badguys[i].x_badguy, badguys[i].y_badguy-1);
		// DOWN - direction
		float downDist = distance_characters(h.x_hero, h.y_hero, badguys[i].x_badguy, badguys[i].y_badguy+1);
		// RIGHT - direction
		float rightDist = distance_characters(h.x_hero, h.y_hero, badguys[i].x_badguy+1, badguys[i].y_badguy);
		// LEFT - direction
		float leftDist = distance_characters(h.x_hero, h.y_hero, badguys[i].x_badguy-1, badguys[i].y_badguy);
		//float leftDist = int(sqrt((pow(((badguys[i].x_badguy-1)-(h.x_hero)),2))-(pow(((badguys[i].y_badguy)-(h.y_hero)),2))));

		float bestMoves[] = {upDist, downDist, rightDist, leftDist};

		sortArray(bestMoves, 4);
		
		int x;
		int y;

		while(!moved)
		{
			//Move
			if(bestMoves[index] == upDist)
			{
				y = badguys[i].y_badguy-1;
				if(map[y*widthMap+badguys[i].x_badguy] != '#')
				{
					map[badguys[i].y_badguy*widthMap+badguys[i].x_badguy]=' ';
					badguys[i].y_badguy--;
					moved = true;
					continue;
				}
			}
			if(bestMoves[index] == downDist)
			{
				y = badguys[i].y_badguy+1;
				if(map[y*widthMap+badguys[i].x_badguy] != '#')
				{
					map[badguys[i].y_badguy*widthMap+badguys[i].x_badguy]=' ';
					badguys[i].y_badguy++;
					moved = true;
					continue;
				}
			}
			if(bestMoves[index] == rightDist)
			{
				x = badguys[i].x_badguy+1;
				if(map[badguys[i].y_badguy*widthMap+x] != '#')
				{
					map[badguys[i].y_badguy*widthMap+badguys[i].x_badguy]=' ';
					badguys[i].x_badguy++;
					moved = true;
					continue;
				}
			}
			if(bestMoves[index] == leftDist)
			{
				x = badguys[i].x_badguy-1;
				if(map[badguys[i].y_badguy*widthMap+x] != '#')
				{
					map[badguys[i].y_badguy*widthMap+badguys[i].x_badguy]=' ';
					badguys[i].x_badguy--;
					moved = true;
					continue;
				}
			}
			index++;
		}
	}
}

void display_menu()
{
cout << "**************************************\n" << endl;
cout << "* Welcome!!! This is the catch game. *" << endl;
cout << "* Try to collect all the coins before*" << endl;
cout << "*     you get caught! Good luck!     *\n" << endl;
cout << "**************************************" << endl << endl;
}
bool ask_to_play()
{
	bool start=false;

	if(highscore == 0)
	{
		cout << "No one was able to finish the game yet.." << endl;
	}
	else
	{
		cout << "The current highscore is " << highscore;
		cout << " to collect all the coins!\nTry to get that number down!" << endl;
	}
	cout << "Would you like to start a new game? Y/N" << endl;
	string answer;
	cin >> answer;
	if((answer == "Y") || (answer == "y"))
	{
		start = true;
	}
	return start;
}

void display_instructions()
{
	cout << endl;
	cout << "** Instructions **" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "@";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " --> This is you, the hero!" << endl << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cout << "&";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " --> These are the ennemies, watch out!" << endl << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	cout << "D";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " --> These are doors to teleport!" << endl << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "O";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " --> These are the coins to collect!" << endl << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "#";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " --> These are the walls." << endl << endl;

}