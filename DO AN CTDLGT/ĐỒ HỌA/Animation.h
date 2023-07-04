#include <iostream>
#include <string>
#include "HashTable.h"
using namespace std;

void slide_Animation(string s, int x, int y, int color_text);
void text_Animation(string s, double time);

void text_Animation(string s, double time)
{
	for (int i = 0; i < s.length(); i++)
	{
		for (double j = 0; j < time; j++);
		cout << s.at(i);
	}
}

void slide_Animation(string s, int x, int y, int color_text)
{
	gotoXY(x, y);
	for (int i = 0; i < 80; i++)
	{
		for (int j = 0; j < i; j++)
			cout << " ";
		cout << s;
		for (double k = 0; k < 1000000; k++)
			;
		system("cls");
	}
	ToMau(x, y, s, color_text);
	//SetColor(46);
	//cout << s;
}
