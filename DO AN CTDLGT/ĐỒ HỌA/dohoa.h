#include <stdio.h>
#include <iostream>
#include <conio.h>
//#include <io.h>
//#include <fcntl.h>
#include<ctime> /* thư viện hỗ trợ về thời gian thực */
#include "windows.h" // thư viện này bá đạo lắm nhé - chứa nhiều đồ chơi nek - cứ tìm hiểu dần dần s
//======= lấy tọa độ x của con trỏ hiện tại =============
#define KEY_NONE	-1
#define MAX 100
using namespace std;

//===============
void box(int x, int y, int w, int h, int t_color, int b_color, string nd);
void n_box(int x, int y, int w, int h, int t_color, int b_color, string nd, int sl);
void menu();
void thanh_sang(int x, int y, int w, int h, int b_color, string nd, int x_nd, int y_nd, int t_color);
int whereX();
int whereY();
void gotoXY(int x, int y);
void SetColor(WORD color);
void ShowCur(bool CursorVisibility);
void ToMauKiTu(int x, int y, char a, int color);
int inputKey();
//void textcolor(int x);
void resizeConsole(int width, int height);
void setColor_TextAndBackground(int x);
void setFontSize(int FontSize);
void XoaManHinh();
void ToMau(int x, int y, string a, int color);

int x = 50; int y = 5;

//========= lấy tọa độ y của con trỏ hiện tại =======
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}
//========= lấy tọa độ y của con trỏ hiện tại =======
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}
//============== dịch con trỏ hiện tại đến điểm có tọa độ (x,y) ==========
void gotoXY(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
//============= đặt màu cho chữ =========
void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//============== làm ẩn trỏ chuột ===========
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
//======= trả về mã phím người dùng bấm =========
int inputKey()
{
	if (_kbhit()) //true
	{
		int key = _getch();

		if (key == 224)
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return KEY_NONE;
	}
	return KEY_NONE;
}
// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}
void menu()
{
	ShowCur(0);
	//----- setting ----
	int w = 20;
	int h = 2;
	int t_color = 11;
	int b_color = 1;
	int b_color_sang = 75;
	string nd = "hello";
	int sl = 4;
	n_box(x, y, w, h, t_color, b_color, nd, sl);

	//-------------
	int xp = x; int yp = y;//tọa độ thanh sáng
	int xcu = xp; int ycu = yp;
	bool kt = true;
	while (true)
	{
		//------ in ----
		if (kt == true)
		{
			//----- back space ----
			gotoXY(xcu, ycu);
			thanh_sang(xcu, ycu, w, h, b_color, nd,xcu+1, ycu+1, 15);//rs thanh sang cu
			xcu = xp; ycu = yp;
			//-------------
			thanh_sang(xp, yp, w, h, b_color_sang, nd, xp + 1, yp + 1, 15);
			kt = false;
		}
		//----- dieu khien ---- //----- di chuyen ----
		if (_kbhit())
		{
			char c = _getch();
			if (c == -32)
			{
				kt = true;// đã bấm
				c = _getch();
				if (c == 72)
				{
					if (yp != y)
						yp -= 2;
					else
					{
						yp = y + h * (sl - 1);
					}
				}
				else if (c == 80)
				{
					if (yp != y + h * (sl - 1))
						yp += 2;
					else
					{
						yp = y;
					}
				}
			}
		}
		//---- speed ----
	}

}
void thanh_sang(int x, int y, int w, int h, int b_color, string nd, int x_nd, int y_nd, int t_color)
{
	textcolor(b_color);
	for (int iy = y + 1; iy <= y + h - 1; iy++)
	{
		for (int ix = x + 1; ix <= x + w - 1; ix++)
		{
			gotoXY(ix, iy); cout << " ";
		}
	}
	SetColor(t_color);
	gotoXY(x_nd, y_nd);
	cout << nd;
}
void box(int x, int y, int w, int h, int t_color, int b_color, string nd)
{
	textcolor(b_color);
	for (int iy = y + 1; iy <= y + h - 1; iy++)
	{
		for (int ix = x + 1; ix <= x + w - 1; ix++)
		{
			gotoXY(ix, iy); cout << " ";
		}
	}
	SetColor(t_color);
	gotoXY(x + 1, y + 1);
	cout << nd;
	//============= ve vien =============
	textcolor(1);
	SetColor(t_color);//update
	if (h <= 1 || w <= 1)return;
	for (int ix = x; ix <= x + w; ix++)
	{
		gotoXY(ix, y);
		cout << char(196);
		gotoXY(ix, y + h);
		cout << char(196);
	}
	for (int iy = y; iy <= y + h; iy++)
	{
		gotoXY(x, iy);
		cout << char(179);
		gotoXY(x + w, iy);
		cout << char(179);
	}
	gotoXY(x, y); cout << char(218);
	gotoXY(x + w, y); cout << char(191);
	gotoXY(x, y + h); cout << char(192);
	gotoXY(x + w, y + h); cout << char(217);

}
void n_box(int x, int y, int w, int h, int t_color, int b_color, string nd, int sl)
{
	for (int i = 0; i < sl; i++)
	{
		box(x, y + (i * 2), w, h, t_color, b_color, nd);//i = 0 => x,y, i = 1: x,y+2
		if (i != 0)
		{
			gotoXY(x, y + (i * 2)); cout << char(195);
			gotoXY(x + w, y + (i * 2)); cout << char(180);
		}
	}
}
// Hàm thay đổi kích cỡ của khung cmd với tham số truyền vào là chiều cao, chiều rộng.
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
// Ham thay doi textcolor va backgroundcolor
void setColor_TextAndBackground(int x) 
{
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, x);
}
//set mau cho bg
void BackGroundColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void ToMau(int x, int y, string a, int color) // x, y là tọa độ con trỏ cần nhảy đến để viết, a là chuỗi cần truyền vào, color là màu truyền vào.
{
	gotoXY(x, y);
	SetColor(color);
	cout << a;
	textcolor(7);
}
//xoa man hinh
void XoaManHinh()
{
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void ToMauKiTu(int x, int y, char a, int color) // x, y là tọa độ con trỏ cần nhảy đến để viết, a là chuỗi cần truyền vào, color là màu truyền vào.
{
	gotoXY(x, y);
	SetColor(color);
	cout << a;
	textcolor(7);
}