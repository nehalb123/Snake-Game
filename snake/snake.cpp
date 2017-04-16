// snake.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;

class Snake {
public:
	int snakex, snakey, foodx, foody, food = 0;
	enum Surf { stop = 0, Left, Right, up, down };
	Surf dir;


	int tail=0;
	int tailx[200] = {0}, taily[200] = {0};
	const int width = 20;
	const int height = 20;
	bool gameover;
	void Start();
	void set_input();
	void Grid();
	void build();

};

void Snake::Start() {
	gameover = false;
	dir = stop;
	tailx[0] = 0;  taily[0] = 0;
	snakex = width / 3;
	snakey = height / 2;
	foodx = rand() % width;
	foody = rand() % height;
}
void Snake::set_input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = Left;
			break;
		case 'd':
			dir = Right;
			break;
		case 'w':
			dir = up;
			break;
		case 's':
			dir = down;
			break;
		case 'q':
			gameover = true;
			break;
		}
	}

}
void Snake::Grid() {
	system("cls");
	for (int i = 0; i < width + 1; i++) {
		cout << "_";
	}
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) {
				cout << "|";
			}

		if (i == snakey && j == snakex) //placing head of snake
			cout << "O";
			else if (i == foody && j == foodx) //placing food 
				cout << "@";
			else {
				bool add = false;
				for (int k = 0; k < tail; k++) {

					if (tailx[k] == j && taily[k] == i) {
						cout << "o";
						add = true;
					}

				}
				if (!add) {
					cout << " ";
				}
			}

			if (j == width - 1)
				cout << "|";
		}
		cout << endl;
	}
	for (int i = 0; i < width / 2 + 1; i++) {
		cout << "--";
	}
	cout << endl;
	cout << "Food:" << food;
}
void Snake::build() {
	int prevx = tailx[0];
	int prevy = taily[0];
	tailx[0] = snakex;
	taily[0] = snakey;
	int prev2x, prev2y;
	for (int i = 1; i < tail; i++) {
		prev2x = tailx[i];
		prev2y = taily[i];
		tailx[i] = prevx;
		taily[i] = prevy;
		prevx = prev2x;
		prevy = prev2y;
	}
	switch (dir)
	{
	case Left:
		snakex--;
		break;
	case Right:
		snakex++;
		break;
	case up:
		snakey--;
		break;
	case down:
		snakey++;
		break;
	default:
		break;
	}
	/*if (snakex > width || snakex<0 || snakey>height || snakey < 0) {
	gameover = true;
	}*/
	if (snakex >= width) snakex = 0; else if (snakex < 0) snakex = width - 1;
	if (snakey >= height) snakey = 0; else if (snakey < 0) snakey = height - 1;
	for (int i = 0; i < tail; i++) {
		if (tailx[i] == snakex && taily[i] == snakey) {
			gameover = true;
		}
	}
	if (snakex == foodx && snakey == foody) {
		food += 1;
		foodx = rand() % width;
		foody = rand() % height;
		tail++;
	}
}
int main()
{
	Snake s;
	s.Start();
	while (!s.gameover) {
		s.Grid();
		s.set_input();
		s.build();
		Sleep(200);

	}
	return 0;
}

