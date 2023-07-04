#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <string>
#include <io.h>
#include <fcntl.h>
#include "Animation.h"
#include <conio.h>
#include <cstdlib> // for rand() and srand()
#include <ctime>
#include <stdint.h>
using namespace std;

#define sizemax 100

//thay doi title
BOOL WINAPI SetConsoleTitle(
	_In_ LPCTSTR lpConsoleTitle
);

void setKichThuocManHinh()
{
	static CONSOLE_FONT_INFOEX  fontex;
	fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hOut, 14, &fontex);
	fontex.FontWeight = 7500;
	fontex.dwFontSize.X = 25;
	fontex.dwFontSize.Y = 25;
	SetCurrentConsoleFontEx(hOut, 11, &fontex);
}
void SetWindowSize(SHORT width, SHORT height)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	SMALL_RECT WindowSize;
	WindowSize.Top = 0;
	WindowSize.Left = 0;
	WindowSize.Right = width;
	WindowSize.Bottom = height;

	SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}
void SetScreenBufferSize(SHORT width, SHORT height)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD NewSize;
	NewSize.X = width;
	NewSize.Y = height;

	SetConsoleScreenBufferSize(hStdout, NewSize);
}
//an hien thanh cuon
void ShowScrollbar(BOOL Show)
{
	HWND hWnd = GetConsoleWindow();
	ShowScrollBar(hWnd, SB_BOTH, Show);
}
//không cho bôi đen
void DisableSelection()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}
//cho bôi đen 
void EnableSelection()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleMode(hStdin, ENABLE_QUICK_EDIT_MODE);
}

void traCuuTuDien(TRANSLATELANGUEGE*& tudien, TRANSLATELANGUEGE*& lichSu, string Arr[]);
NODEWORD* veGiaoDienChinh(TRANSLATELANGUEGE* tudien, string input, int pos);
void themTuMoi(TRANSLATELANGUEGE*& tudien);
void veGiaoDienChiTietTu(TRANSLATELANGUEGE* tudien, NODEWORD* p);
void ghiFile(TRANSLATELANGUEGE*& tudien);
void setFontSize(int FontSize);
void suaTu(TRANSLATELANGUEGE* tudien, NODEWORD*& word);
void manHinhStart(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[]);
void giaoDien2(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[]);
void giaoDien3(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[]);
void thongBaoSuaTu(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu);
void xemLichSu(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[]);
void themTuVaoCuoiLichSu(TRANSLATELANGUEGE*& lichSu, NODEWORD* NewWord);
NODEWORD* taoNodeLichSu(NODEWORD* p);
NODEWORD* randomTu(TRANSLATELANGUEGE* tudien);
//game1
void gameDoanChu(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[]);
void randomDapAn(string da);
void prinfNghia(NODE* nghia);
bool checkDapAn(string ketQua, string s);
bool checkCauHoi(TRANSLATELANGUEGE* game, string s);
void giaoDienEndGame(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* game, TRANSLATELANGUEGE* lichSu, string Arr[], int diemSo);
void giaoDienHuongdan(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu);
//game2
void gameNgheViet(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[]);
void giaoDienHuongDanGame2(TRANSLATELANGUEGE* tudien);
int randomCauHoiGame2();
bool checkCauHoiGame2(string B[], int idx_rand);
string docTuGame2(string& s);
void docFileDapAnGame2(string Arr[]);
void xoaKiTu(int x, int y, string s);
void demNguoc(char tgian, int x, int y);
void playCauHoiGame2(int i);
void themTuVaoMangKetQua(string Arr[], int idx, string B[]);
void giaoDienEndGame2(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[], string B[], int diemSo);
int STT_TuVung(string B[], int key, int soCauHoi_DaTraLoi);
void giaoDienEndGame2(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[], string B[], int diemSo, int soCauHoi);
//game3
void gameNoiChu(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[]);
void giaoDienEndGame3(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[], string C[], int diemSo, int soCauHoi);
bool checkDapAnGame3(string deBai, string dapAn);
void themTuVaoLuuTru(string C[], int& idx, string s);
bool checkCauHoiGame3(string C[], string s);
NODEWORD* randomTuGame3(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[], string dapAn);
void giaoDienHuongDanGame3(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[]);
//game4
void khungDapAn();
void an_BangDapAn(int DapAn[][5], bool CheckDapAn[][5]);
void hien_BangDapAn(int DapAn[][5], bool CheckDapAn[][5]);
bool luuVaoMang2Chieu(int DapAn[][5], int chuCai, int i, int j);
void randomDapAnGame3(int DapAn[][5], bool CheckDapAn[][5], string da);
bool hienThiLuaChon(int DapAn[][5], bool CheckDapAn[][5], int x, int y, int b_color);
void giaoDienEndGame4(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* game, TRANSLATELANGUEGE* lichSu, string Arr[], int diemSo);
void hienChuCaiDung(string key, string& temp, char chuCai, int& x, int y);
void gameChonODung(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[]);
void giaoDienHuongDanGame4(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[]);

//bien toan cuc
int demSoLan_Ignore = 1;
int demSoLan_Ignore2 = 1;
int demSoLan_Ignore3 = 1;

//bien toan cuc game 4
int kichThuocBang = 5;// 5x 5
int chieuNgangOChu = 6;//chiều ngang 1 ô
int chieuDocOChu = 3;//chiều dọc 1 ô
int x_viTriDau = 15; //vị trí đầu của ô đầu tiên
int y_ViTriDau = 7;//vị trí đầu của ô đầu
int x_ChuCai_ODauTien = x_viTriDau + (chieuNgangOChu / 2);
int y_ChuCai_ODauTien = y_ViTriDau + (chieuDocOChu / 2);
	//khoảng cách từ đầu ô này tới đầu ô tiếp theo 
int khoangCachNgang = chieuNgangOChu + 2; //theo chiều ngang
int khoangCachDoc = chieuDocOChu + 1;//theo chiều dọc


int main()
{
	SetConsoleTitle(L"TU DIEN - NHOM 1");
	SetWindowSize(1570, 980);
	SetScreenBufferSize(1570, 30);

	//tudien
	TRANSLATELANGUEGE* tudien = new TRANSLATELANGUEGE[26];
	ShowScrollbar(0);
	initTranslateLanguege(tudien);

	//lich su
	TRANSLATELANGUEGE* lichSu = new TRANSLATELANGUEGE;
	initHistory(lichSu);

	//game 2
	string Arr[50] = { "" }; //tao mang luu KEY dap an

	docFileDapAnGame2(Arr);

	setKichThuocManHinh();
	
	docFileTuVung(tudien);
	manHinhStart(tudien, lichSu, Arr);

	return 0;
}

//man hinh start
void manHinhStart(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[])
{
	DisableSelection();//khong cho bôi đen
	ShowCur(0);

	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");


	int X = 34;
	int Y = 13;
	//TU DIEN
	gotoXY(X, Y);

	text_Animation("LANGUAGE TRANSLATOR ENGLISH - VIETNAM ", 4500000);
	PlaySound(TEXT("TuDienAnhViet.wav"), NULL, SND_APPLICATION);

	//hiện gợi ý

	string s1 = "ENTER : VAO MAN HINH CHINH ";
	ToMauKiTu(37, Y + 5, char(16), 72);
	ToMau(39, Y + 5, s1, 72);
	ToMauKiTu(39 + s1.length(), Y + 5, char(17), 72);

	string s2 = "ESC : THOAT CHUONG TRINH ";
	ToMauKiTu(38, Y + 7, char(16), 72);
	ToMau(40, Y + 7, s2, 72);
	ToMauKiTu(40 + s2.length(), Y + 7, char(17), 72);


	int key = 0;
	while (true)
	{

		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case 13: //ENTER
				//vao phan chinh
				giaoDien2(tudien, lichSu, Arr);
				break;
			case 27: //ESC
				if (dataChange == true)
				{
					//ghiFile(tudien);
					XoaManHinh();
					ToMau(43, 13, "S A V E   D A T A", 11);
					gotoXY(44 + 17, 13);
					SetColor(11);
					text_Animation(".......", 20000000);
					gotoXY(100, 1000);
				}


				exit(EXIT_SUCCESS);
				break;
			default:
				break;
			}
		}
	}
}
//man hinh 2:
void giaoDien2(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[])
{
	//yêu cầu chọn lại:
chonLai:
	setColor_TextAndBackground(15);
	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");
	int X = 34;
	int Y = 10;

	//box 1
	box(X, Y, 30, 2, 14, 14, "");
	string s1 = "1. TRA CUU TU VUNG";
	ToMau(X + 6, Y + 1, s1, 15);

	//box 2
	box(X, Y + 3, 30, 2, 14, 14, "");
	string s2 = "2. MINI GAME";
	ToMau(X + 8, Y + 4, s2, 15);

	//box 3
	box(X, Y + 6, 30, 2, 14, 14, "");
	string s3 = "3. THOAT";
	ToMau(X + 11, Y + 7, s3, 15);

	//moi nhap lua chon
	string s4 = "Lua chon cua ban la:";
	ToMau(X, Y + 12, s4, 11);

	thanh_sang(X + 20, Y + 11, 10, 2, 243, "", X+20, y+11, 0);
	gotoXY(X + 20 + 5, Y + 12);
	SetColor(12);

	char key;
	//cin.ignore();
	cin >> key;
	//int key = luaChon;
	while (true)
	{

		//if (_kbhit())
		//{
			//key = _getch();
		switch (key)
		{
		case 50: //
			thanh_sang(X, Y + 3, 30, 2, 252, "2. MINI GAME", X + 8, Y + 4, 12);
			Sleep(300);
			XoaManHinh();
			setColor_TextAndBackground(15);//
			BackGroundColor(0);//chua set ve bg den dc
			gotoXY(45, 14);
			text_Animation("loading.......", 20000000);
			PlaySound(TEXT("VoGame.wav"), NULL, SND_SYNC);
			giaoDien3(tudien, lichSu, Arr);
			break;
		case 49:
			//vao phan chinh
			thanh_sang(X, Y, 30, 2, 252, "1. TRA CUU TU VUNG", X + 6, Y + 1, 12);
			Sleep(300);
			XoaManHinh();
			setColor_TextAndBackground(15);//
			BackGroundColor(0);//chua set ve bg den dc
			gotoXY(45, 14);
			text_Animation("loading.......", 20000000);
			PlaySound(TEXT("VoGame.wav"), NULL, SND_SYNC);
			traCuuTuDien(tudien, lichSu, Arr);
			break;

		case 51: //3 Thoat ra lai
			thanh_sang(X, Y + 6, 30, 2, 252, "3. THOAT", X + 11, Y + 7, 12);
			Sleep(300);
			manHinhStart(tudien, lichSu, Arr);
			break;
		default:
			if (key != '1' && key != '2' && key != '3')
				//ToMau(X + 22, Y + 14, "Moi chon lai !", 26);
				gotoXY(X + 8, Y + 14);
			setColor_TextAndBackground(207);
			cout << "Moi chon lai !";
			Sleep(500);
			goto chonLai;
			break;
		}

	}
	//}
}
//giao dien chon minigame
void giaoDien3(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[])
{
	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");
	ShowCur(0);
	DisableSelection();
	int X = 34;
	int Y = 10;

	gotoXY(38, 7);
	SetColor(11);
	text_Animation("M  I  N  I     G  A  M  E", 5000000);

	//box 1
	box(X, Y, 30, 2, 14, 14, "");
	string s1 = "1. DOAN CHU";

	ToMau(X + 10, Y + 1, s1, 15);
	//setColor_TextAndBackground(252);

	//box 2
	box(X, Y + 3, 30, 2, 14, 14, "");
	string s2 = "2. LISTEN - WRITE";
	ToMau(X + 7, Y + 4, s2, 15);

	//box 3
	box(X, Y + 6, 30, 2, 14, 14, "");
	string s3 = "3. WORD LINK";
	ToMau(X + 10, Y + 7, s3, 15);

	//box 4
	box(X, Y + 9, 30, 2, 14, 14, "");
	string s4 = "4.CROSSWORD";
	ToMau(X + 10, Y + 10, s4, 15);


	ToMau(40, 27, "Press ESC to exit", 8);
	int key = 0;
	while (true)
	{
		key = _getch();
		switch (key)
		{
		case 49: //doan chu
			//vao phan chinh
			thanh_sang(X, Y, 30, 2, 252, "1. DOAN CHU", X + 10, Y + 1, 12);
			PlaySound(TEXT("Tick.wav"), NULL, SND_RING);
			gameDoanChu(tudien, lichSu, Arr);
			break;
		case 50: //2
			thanh_sang(X, Y + 3, 30, 2, 252, "2. LISTEN - WRITE", X + 7, Y + 4, 12);
			PlaySound(TEXT("Tick.wav"), NULL, SND_RING);
			gameNgheViet(tudien, lichSu, Arr);
			break;
		case 51: //3
			thanh_sang(X, Y + 6, 30, 2, 252, "3. WORD LINK", X + 10, Y + 7, 12);
			PlaySound(TEXT("Tick.wav"), NULL, SND_RING);
			gameNoiChu(tudien, lichSu, Arr);
			break;
		case 52: //4
			thanh_sang(X, Y + 9, 30, 2, 252, "4.CROSSWORD", X + 10, Y + 10, 12);
			PlaySound(TEXT("Tick.wav"), NULL, SND_RING);
			giaoDienHuongDanGame4(tudien, lichSu, Arr);
		case 27: //esc

			giaoDien2(tudien, lichSu, Arr);
		default:
			break;
		}

	}

}

//tra cứu từ điển
void traCuuTuDien(TRANSLATELANGUEGE*& tudien, TRANSLATELANGUEGE*& lichSu, string Arr[])
{
	NODEWORD* tuHienTai = NULL;
	string input = ""; // noi dung hien tai cua khung tim kiem
	int keyCode = 0;
	int i = 1;
	int pos = 0; // vi tri cua tu hien tai, vi tri thah sang (highlight)
	int soLuongTu = demSoTu(tudien); // dem so luong tu co trong tu dien
	int demSoLanThemTu = 1;
	//trường hợp chọn sửa từ thì vào sửa luôn 
	//if (key == 50) //so 2
	//	goto goToHere;

	while (true)
	{
		tuHienTai = veGiaoDienChinh(tudien, input, pos);	// ve toan bo giao dien
		keyCode = _getch();
		switch (keyCode)
		{
		case 8: // BACKSPACE
			input = input.substr(0, input.length() - 1); // xoa ky tu cuoi
			break;
		case 49: // 1
			//box2: them 
			for (int i = 1; i <= 3; i++)
			{
				thanh_sang(1, 6 + 3, 20, 2, 207, "", 1, 6 + 3, 0);
				ToMau(1 + 2, 6 + 4, "1. THEM TU MOI", 207);
				Sleep(100);
				thanh_sang(1, 6 + 3, 20, 2, 15, "", 1, 6 + 3, 0);
				ToMau(1 + 2, 6 + 4, "1. THEM TU MOI", 15);
				Sleep(100);
			}
			
			if (demSoLanThemTu <= 1)
			{
				cin.ignore();
				++demSoLanThemTu;
			}
		goToHere://goto tới đây 
			themTuMoi(tudien);
			dataChange = false;
			break;
		case 50: //2. sua
			for (int i = 1; i <= 3; i++)
			{
				thanh_sang(1, 6 + 6, 20, 2, 207, "", 1, 6 + 3, 0);
				ToMau(1 + 2, 6 + 7, "2. SUA TU", 207);
				Sleep(100);
				thanh_sang(1, 6 + 6, 20, 2, 15, "", 1, 6 + 3, 0);
				ToMau(1 + 2, 6 + 7, "2. SUA TU", 15);
				Sleep(100);
			}
			thongBaoSuaTu(tudien, lichSu);
			break;
		case 51: // 3. xoa
			//thong bao
			//cin.ignore();
			for (int i = 1; i <= 3; i++)
			{
				thanh_sang(1, 6 + 9, 20, 2, 207, "", 1, 6 + 3, 0);
				ToMau(1 + 2, 6 + 10, "3. XOA TU", 207);
				Sleep(100);
				thanh_sang(1, 6 + 9, 20, 2, 15, "", 1, 6 + 3, 0);
				ToMau(1 + 2, 6 + 10, "3. XOA TU", 15);
				Sleep(100);
			}

			thongBaoSuaTu(tudien, lichSu);
			break;
		case 52: //4 lich su tra tu
			for (int i = 1; i <= 3; i++)
			{
				thanh_sang(1, 6 + 12, 20, 2, 207, "", 1, 6 + 3, 0);
				ToMau(1 + 2, 6 + 13, "4. LICH SU TRA", 207);
				Sleep(100);
				thanh_sang(1, 6 + 12, 20, 2, 15, "", 1, 6 + 3, 0);
				ToMau(1 + 2, 6 + 13, "4. LICH SU TRA", 15);
				Sleep(100);
			}
			xemLichSu(tudien, lichSu, Arr);
			break;
		case 13: // ENTER
			//check xem từ có trong từ điển chưa
			if (tuHienTai == NULL)
			{
				ToMau(55, 15, "ERORR !", 44);
				Sleep(1000);
				break;//chưa có thì cho nhập lại từ khác 
			}
			//thêm từ đó vào lịch sử tra từ:
			themTuVaoCuoiLichSu(lichSu, tuHienTai);
			// vao man hinh chi tiet tu
			//box(40 + 42, 4, 10, 2, 14, 14, "");
			//ToMau(40 + 42 + 3, 4 + 1, "ENTER", 15);
			thanh_sang(40 + 42, 4, 10, 2, 191, "", 40 + 42, 4, 0);
			ToMau(40 + 42 + 3, 4 + 1, "ENTER", 191);
			Sleep(200);
			veGiaoDienChiTietTu(tudien, tuHienTai);
			int k;
			do {
				k = _getch();
				if (k == 50) { // 2. Xoa tu
					// xoa tu nay
					thanh_sang(37 + 15, 3, 13, 4, 124, "2. XOA TU", 37 + 17, 3 + 2, 124);
					Sleep(200);
					thanh_sang(37 + 15, 3, 13, 4, 71, "2. XOA TU", 37 + 17, 3 + 2, 71);
					Sleep(200);
					setColor_TextAndBackground(0);

					deleteNode_Translate(tudien, tuHienTai->info.tu);
					setColor_TextAndBackground(0);
					input = "";
					pos = 0;
					++demSoLanThemTu;
					dataChange = false;
					break; // ve man hinh chinh
				}
				if (k == 49) //1. Sua
				{
					thanh_sang(37, 3, 13, 4, 71, "1. SUA TU", 37 + 2, 3 + 2, 71);
					Sleep(200);
					thanh_sang(37, 3, 13, 4, 124, "1. SUA TU", 37 + 2, 3 + 2, 124);
					Sleep(200);
					setColor_TextAndBackground(0);

					if (i == 1)
					{
						cin.ignore();
						i++;
					}
					// sua tu nay

					suaTu(tudien, tuHienTai);
					input = ""; pos = 0;
					++demSoLanThemTu;
					dataChange = false;
					break; // ve man hinh chinh
				}
				if (k == 27)
				{ // ESCAPE
					//cin.ignore();
					input = ""; // reset gia tri trong khung tim kiem
					pos = 0;
					break; // ve man hinh chinh
				}
			} while (true);
			break;
		case 27: // ESCAPE
			giaoDien2(tudien, lichSu, Arr);
			exit(0); // thoat chuong trinh
			break;
		case 224:
		{
			int key = _getch();
			//cin.ignore(); 
			if (key == 72)
			{
				pos--;
			} // UP
			if (key == 80)
			{
				pos++;
			} // DOWN
			if (pos < 0)
				pos = 0;
			if (pos > soLuongTu - 1)
				pos = soLuongTu - 1;
			break;
		}
		default:
			if (keyCode >= 97 && keyCode <= 122 || keyCode >= 65 && keyCode <= 90)
			{ // a-z
				input += char(keyCode);
			}
		}
	};
}
// giao diện tra từ điển
NODEWORD* veGiaoDienChinh(TRANSLATELANGUEGE* tudien, string input, int pos)
{
	XoaManHinh();
	box(21 - 10, 1, 80 + 10, 28, 14, 11, "");
	//giao dien phần lựa chọn:
	int X = 1;
	int Y = 6;
	int chieuDaiKhungLuaChon = 20;
	int chieuCaoKhungLuaChon = 2;

	//box2: them 
	box(X, Y + 3, chieuDaiKhungLuaChon, chieuCaoKhungLuaChon, 14, 14, "");
	ToMau(X + 2, Y + 4, "1. THEM TU MOI", 15);

	//box3: sua tu 
	box(X, Y + 6, chieuDaiKhungLuaChon, chieuCaoKhungLuaChon, 14, 14, "");
	ToMau(X + 2, Y + 7, "2. SUA TU", 15);

	//box4: LICH SU 
	box(X, Y + 9, chieuDaiKhungLuaChon, chieuCaoKhungLuaChon, 14, 14, "");
	ToMau(X + 2, Y + 10, "3. XOA TU", 15);

	//box5: xoa
	box(X, Y + 12, chieuDaiKhungLuaChon, chieuCaoKhungLuaChon, 14, 14, "");
	ToMau(X + 2, Y + 13, "4. LICH SU TRA", 15);

	//box6: thoat
	ToMau(45, 28, "Press 'ESC' to exit...", 7);

	//giao diện khung tìm kiếm 
	int X_timKiem = 40;
	int Y_timKiem = 4;

	int dongHienTai = 0;


	box(X_timKiem, Y_timKiem, 40, 2, 14, 14, "");
	ToMau(X_timKiem + 2, Y_timKiem + 1, input, 12);
	//box1: tra nghia
	box(40 + 42, 4, 10, 2, 14, 14, "");
	ToMau(40 + 42 + 3, 4 + 1, "ENTER", 11);

	NODEWORD* tuHienTai = inDanhSachTu(tudien, input, pos);

	// neu dang o man hinh chinh,
	// dua con tro nhap nhay ve lai khung tim kiem
	gotoXY(42 + input.length(), 5);

	return tuHienTai;

}
//giao diện chi tiết 1 từ 
void veGiaoDienChiTietTu(TRANSLATELANGUEGE* tudien, NODEWORD* p)
{
	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");
	int dongHienTai = 0;

	//giao dien lua chon
	int X = 37;
	int Y = 3;
	int chieuDaiKhungLuaChon = 13;
	int chieuCaoKhungLuaChon = 2;

	//box1: sua tu
	//box(X, Y, chieuDaiKhungLuaChon, chieuCaoKhungLuaChon, 71, 71, "1. SUA TU");
	//ToMau(X + 2, Y + 1, "1. SUA TU", 71);
	//thanh_sang(X + 1, Y - 1, chieuDaiKhungLuaChon, 4, 18, "", X + 2, Y + 2, 18);
	thanh_sang(X, Y, chieuDaiKhungLuaChon, 4, 124, "1. SUA TU", X + 2, Y + 2, 124);
	

	//box2: xoa tu
	//box(X + 15, Y , chieuDaiKhungLuaChon, chieuCaoKhungLuaChon, 14, 14, "");
	//ToMau(X + 17, Y + 1, "2. XOA TU", 15);
	thanh_sang(X + 15, Y, chieuDaiKhungLuaChon, 4, 71, "2. XOA TU", X + 17, Y + 2, 71);

	//box3: Thoat
	//box(X, Y+6, chieuDaiKhungLuaChon, chieuCaoKhungLuaChon, 14, 14, "");
	setColor_TextAndBackground(0);
	ToMau(40, 27, "Press 'ESC' to exit !", 8);
	//ToMau(12, 11, "Press Key !", 8);

	//giao dien chi tiet tu:
	int x = 32;
	int y = 9;

	//box1: tu
	string tu = p->info.tu;
	box(x, y, 40, 2, 14, 14, "");
	ToMau(x + 2, y + 1, "Tu:", 7);
	ToMau(x + (40 - tu.length()) / 2, y++ + 1, tu, 11);//X: căn giữa khung tìm kiếm

	//box2: loai
	string loai;
	for (int i = 0; i < size_loaitu; i++)
	{
		if (p->info.loaitu[i] != "")
			loai = p->info.loaitu[i];
	}
	ToMauKiTu(x + 2, y + 3, char(16), 72);
	ToMau(x + 4, y + 3, "Loai tu:", 5);
	ToMau(x + 4 + 10, y + 3, loai, 15);

	//box3: nghia
	NODE* nghia = p->info.nghia;
	y = y + 5;
	ToMauKiTu(x + 2, y, char(16), 72);
	ToMau(x + 4, y++, "Nghia:", 5);
	string sNghia;
	while (nghia != NULL)
	{
		sNghia = nghia->key;
		ToMauKiTu(x + 6, y, char(249), 72);
		ToMau(x + 8, y++, sNghia, 15);
		nghia = nghia->next;
	}

	//box4: vidu
	NODE* vd = p->info.vidu;
	++y;
	cout << endl;
	ToMauKiTu(x + 2, y, char(16), 72);
	ToMau(x + 4, y++, "Vi du: ", 5);
	string vidu;
	while (vd != NULL)
	{
		vidu = vd->key;
		ToMauKiTu(x + 6, y, char(249), 72);
		ToMau(x + 8, y++, vidu, 15);
		vd = vd->next;
	}
	//chuyển con trỏ chuột về sau từ vựng:
	gotoXY(50 + tu.length() + (40 - tu.length()) / 2, 5 + 1);
}
//lich su tra tu
void xemLichSu(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[])
{
	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");

	ToMau(49, 3, "HISTORY", 14);

	int x = 7;
	int y = 7;
	if (lichSu->head == NULL)
	{
		ToMau(43, 15, "List is empty !", 11);
		Sleep(1000);
		return;
	}
	else
	{
		int c = 49;//'1'
		NODEWORD* p = lichSu->head;
		string tu, loaitu;
		NODE* nghia;
		while (p != NULL)
		{
			tu = p->info.tu;
			for (int i = 0; i < size_loaitu; i++)
			{
				if (p->info.loaitu[i] != "")
					loaitu = p->info.loaitu[i];
			}

			ToMauKiTu(x++, y, char(c++), 7);//1
			ToMauKiTu(x++, y, char(46), 7);//.
			ToMau(x++, y, tu, 15);//in từ
			x += tu.length();
			ToMauKiTu(x++, y, char(40), 15);//(
			ToMau(x, y, loaitu, 15);//in loại từ
			x += loaitu.length();
			ToMauKiTu(x++, y, char(41), 15);//)
			ToMauKiTu(x++, y, char(58), 15);//:
			nghia = p->info.nghia;
			++x;
			while (nghia != NULL)
			{
				ToMau(x, y, nghia->key, 15); //in nghĩa 1, 2, 3...
				x += nghia->key.length();
				if (nghia->next == NULL)//nghĩa cuối cùng
					ToMauKiTu(x++, y, char(46), 15);//dấu chấm cuối câu
				else ToMauKiTu(x++, y, char(44), 15);//, <-> còn nghĩa thì cách bởi dấu ,
				ToMauKiTu(x++, y, char(0), 15);//(khoang trang)
				nghia = nghia->next;
			}
			//cập nhật lại x và y
			x = 7; //xuống dòng nên k thay đổi x
			++y;//chỉ tăng y -> xuống 1 dòng
			p = p->nextword;
		}
	}
	ToMau(40, 4, "(Press 'ESC' to exit !)", 8);
	int key = 0;
	while (true)
	{
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case 27://esc
				traCuuTuDien(tudien, lichSu, Arr);
				break;
			default:
				break;
			}
		}
	}
}
//them tu vao Lich Su tra cuu - them node cuoi
void themTuVaoCuoiLichSu(TRANSLATELANGUEGE*& lichSu, NODEWORD* NewWord)
{
	NODEWORD* newNode = taoNodeLichSu(NewWord);
	if (lichSu->head == NULL)//chưa có gía trị trùng -> thì thêm vô thôi
	{
		lichSu->head = newNode;
		lichSu->tail = newNode;
	}
	else//có giá trị trùng nhau -> thì thêm vô sau node cuối của hàng idx đó
	{
		lichSu->tail->nextword = newNode;
		lichSu->tail = newNode;
	}
}
//tạo NODEWORD cho hashtable Lịch Sử:
NODEWORD* taoNodeLichSu(NODEWORD* p)
{
	NODEWORD* nodeHis = new NODEWORD;
	nodeHis->info = p->info;
	nodeHis->nextword = NULL;
	return nodeHis;
}
//them tu moi
void themTuMoi(TRANSLATELANGUEGE*& tudien)
{
	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");


	NODEWORD* p = new NODEWORD();
	//p->info. = NULL;
	p->info.nghia = NULL;
	p->info.vidu = NULL;

	//giao dien 
	//box 1: nhap tu
	int X = 41;
	int Y = 3;
	gotoXY(X, Y);
	SetColor(14);
	text_Animation("ADD NEW VOCABULARY", 4000000);
	X = 5;
	Y = Y + 2;
	ToMauKiTu(5, Y, char(16), 72);
	ToMau(7, Y, "Nhap tu:", 5);

	string tuMoi;

	gotoXY(X + 20, Y++);
	SetColor(15);
	//cin.ignore();
	getline(cin, tuMoi);
	if (tuMoi == "")
	{
		XoaManHinh();
		gotoXY(48, 14);
		SetColor(7);
		text_Animation("fail.......", 20000000);
		PlaySound(TEXT("Khong Thanh Cong.wav"), NULL, SND_SYNC);
		return;
	}//có thể cho pause vài giây trước khi return 
	else
	{
		p->info.tu = tuMoi;
	}

	// nhap loai tu
	ToMauKiTu(5, ++Y, char(16), 72);
	ToMau(7, Y, "Nhap loai tu:", 5);
	string loaiTuMoi;

	gotoXY(X + 20, Y++);
	SetColor(15);
	//cin.ignore();
	getline(cin, loaiTuMoi);
	loaiTuMoi = chuanHoa(loaiTuMoi);
	int idx_LoaiTu = loaiTu(loaiTuMoi);
	for (int i = 0; i < size_loaitu; i++)
	{
		if (i == idx_LoaiTu)
			p->info.loaitu[i] = loaiTuMoi;
		else
			p->info.loaitu[i] = "";
	}

	//nhap nghia
	int dem = 49; //ép kiểu qua char: 49->'1'
	ToMauKiTu(5, ++Y, char(16), 72);
	ToMau(7, Y, "Nhap nghia:", 5);
	ToMau(7 + 13, Y++, "(Press 'ENTER' to skip)", 8);
	while (true)
	{
		string nghiaMoi;
		ToMauKiTu(X + 20, Y, char(dem++), 7);//1
		ToMauKiTu(X + 21, Y, char(46), 7);//'.'
		gotoXY(X + 22, Y++);
		SetColor(15);//set color cho text
		//cin.ignore();
		getline(cin, nghiaMoi);//nhap nghia 
		if (nghiaMoi == "")
			break;
		else
			themNodeMoi(p->info.nghia, nghiaMoi);
	}

	//nhap vidu
	dem = 49; //ép kiểu qua char: 49->'1'
	ToMauKiTu(5, ++Y, char(16), 72);
	ToMau(7, Y, "Nhap vi du:", 5);
	ToMau(7 + 13, Y++, "(Press 'ENTER' to skip)", 8);
	while (true)
	{
		string viduMoi;
		ToMauKiTu(X + 20, Y, char(dem++), 7);//1
		ToMauKiTu(X + 21, Y, char(46), 7);//'.'
		gotoXY(X + 22, Y++);
		SetColor(15);//set color cho text
		//cin.ignore();
		getline(cin, viduMoi);
		if (viduMoi == "")
			break;
		themNodeMoi(p->info.vidu, viduMoi);
	}

	addNewWord(tudien, p);
	dataChange = true;
	if (dataChange)
	{
		XoaManHinh();
		ToMau(45, 13, "Thanh cong !", 11);
		ghiFile(tudien);
		PlaySound(TEXT("correct_2.wav"), NULL, SND_SYNC);
		Sleep(1000);
	}
}
//Sửa từ:
void suaTu(TRANSLATELANGUEGE* tudien, NODEWORD*& word)
{

	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");

	//box 1: tu can sua
	box(25, 6, 50, 2, 14, 14, "");
	int x = 25;
	int y = 7;
	string s1 = "Tu can sua:";
	string tu = word->info.tu;
	ToMau(x + 2, y, s1, 7);
	ToMau(x + (50 - tu.length() / 2) / 2, y, tu, 11);//in tu

	//box2: nhap loai
	ToMauKiTu(x + 2, y + 2, char(16), 72);
	ToMau(x + 4, y + 2, "Nhap loai tu: ", 5);
	gotoXY(x + 25, y + 2);
	SetColor(15);
	string temp = "";
	//cin.ignore();
	getline(cin, temp);

	int key = 0;

	if (temp == "")
	{
		if (!dataChange)
		{
			XoaManHinh();
			ToMau(43, 14, "Khong thanh cong !", 11);
			PlaySound(TEXT("Khong Thanh Cong.wav"), NULL, SND_SYNC);
			Sleep(1000);
		}
		return;
	}
	temp = chuanHoa(temp);
	int idx_LoaiTu = loaiTu(temp);
	for (int i = 0; i < size_loaitu; i++)
	{
		if (idx_LoaiTu == i)
			word->info.loaitu[i] = temp;
		else
			word->info.loaitu[i] = "";
	}

	//box3: nhap nghia
	ToMauKiTu(x + 2, y + 4, char(16), 72);
	ToMau(x + 4, y + 4, "Nhap nghia moi: ", 5);
	ToMau(x + 4 + 16, y++ + 4, "('TAB': Skip - Double 'ENTER': countinue) ", 8);

	NODE* nghia = word->info.nghia;
	int i = 49;//1
	key = 0;
	while (true)
	{
		gotoXY(x + 20, y + 4);
		key = _getch();
		switch (key)
		{
		case 9://TAB
			//cout << "..........";
			goto skipNghia;
			break;
		default:
			if (nghia == NULL) // tu nay chua co nghia nao
			{
				while (true)
				{
					ToMauKiTu(x + 20, y + 4, char(i++), 7);//1
					ToMauKiTu(x++ + 21, y + 4, char(46), 7);//'.'
					gotoXY(++x + 21, y + 4);
					SetColor(15);

					//cin.ignore();
					temp = "";
					key = _getch();
					switch (key)
					{
					case 9://TAB
						//cout << "..........";
						goto skipNghia;
						break;
					default:
						break;
					}
					getline(cin, temp);
					if (temp == "")
					{
						x = 25;
						++y;
						break;
					}
					themNodeMoi(word->info.nghia, temp);
					x = 25;
					++y;
					gotoXY(x, y + 4);
				}
			}
			else
			{
				for (; nghia != NULL; nghia = nghia->next)
				{
					ToMauKiTu(x + 20, y + 4, char(i++), 7);//1
					ToMauKiTu(x++ + 21, y + 4, char(46), 7);//'.'
					gotoXY(++x + 21, y + 4);
					SetColor(15);

					temp = "";
					key = _getch();
					switch (key)
					{
					case 9://TAB
						//cout << "..........";
						goto skipNghia;
						break;
					default:
						break;
					}
					getline(cin, temp);
					if (temp == "")
					{
						x = 25;
						++y;
						break;
					}

					nghia->key = temp;
					//nghia = nghia->next;
					x = 25;
					++y;
					gotoXY(x, y + 4);
				}
			}
			break;
		}

	}

	//sua vidu
skipNghia:

	x = 25;
	++y;
	//box3: nhap nghia
	ToMauKiTu(x + 2, y + 6, char(16), 72);
	ToMau(x + 4, y + 6, "Nhap vi du moi: ", 5);
	ToMau(x + 4 + 16, y++ + 6, "('TAB': Skip - Double 'ENTER': countinue) ", 8);

	NODE* vd = word->info.vidu;
	i = 49;//1

	while (true)
	{
		gotoXY(x + 20, y + 6);
		key = _getch();
		switch (key)
		{
		case 9://TAB
			//cout << "..........";
			goto DuLieuThayDoi;
			break;
		default:
			if (vd == NULL) // tu nay chua co nghia nao
			{
				while (true)
				{
					ToMauKiTu(x + 20, y + 6, char(i++), 7);//1
					ToMauKiTu(x++ + 21, y + 6, char(46), 7);//'.'
					gotoXY(++x + 21, y + 6);
					SetColor(15);

					temp = "";
					key = _getch();
					switch (key)
					{
					case 9://TAB
						//cout << "..........";
						//goto skipViDu;
						return;
						break;
					default:
						break;
					}
					getline(cin, temp);
					if (temp == "")
					{
						x = 25;
						++y;
						break;
					}
					themNodeMoi(word->info.vidu, temp);
					x = 25;
					++y;
					gotoXY(x, y + 6);
				}
			}
			else
			{
				for (; vd != NULL; vd = vd->next)
				{
					ToMauKiTu(x + 20, y + 6, char(i++), 7);//1
					ToMauKiTu(x++ + 21, y + 6, char(46), 7);//'.'
					gotoXY(++x + 21, y + 6);
					SetColor(15);

					temp = "";
					key = _getch();
					switch (key)
					{
					case 9://TAB
						//cout << "..........";
						//goto skipViDu;
						return;
						break;
					default:
						break;
					}
					getline(cin, temp);
					if (temp == "")
					{
						x = 25;
						++y;
						break;
					}
					vd->key = temp;
					x = 25;
					++y;
					gotoXY(x, y + 6);
				}
			}
			break;
		}

	}
DuLieuThayDoi:
	dataChange = true;
	if (dataChange)
	{
		XoaManHinh();
		ghiFile(tudien);
		ToMau(45, 13, "Thanh cong !", 11);
		PlaySound(TEXT("correct_2.wav"), NULL, SND_SYNC);
		Sleep(500);
	}

}
//xóa từ 
void deleteNode_Translate(TRANSLATELANGUEGE*& tudien, string word)
{
	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");;

	NODEWORD* word_del = checkTuVung(tudien, word);//kiem tra xem có trong từ điển chưa 
	if (word_del == NULL)
	{
		ToMau(40, 13, "Khong tim thay !", 11);
		PlaySound(TEXT("Khong Thanh Cong.wav"), NULL, SND_SYNC);
		Sleep(1000);
		return;
	}
	else
	{
		string s1 = "BAN CO CHAC CHAN MUON XOA TU? (Y/N)";
		ToMau(35, 13, s1, 11);
		//ToMau(40, 15, "<< Press 'Y' to YES! >>", 8);
		//ToMau(40, 17, "<< Press 'N' to NO! >>", 8);
		thanh_sang(40, 15, 11, 4, 124, "NO", 45, 17, 124);
		thanh_sang(53, 15, 11, 4, 71, "YES", 57, 17, 71);
		gotoXY(35 + s1.length(), 13);
		char c = _getch();
		if (c != 'y' && c != 'Y')
		{
			thanh_sang(40, 15, 11, 4, 71, "NO", 45, 17, 71);
			Sleep(200);
			thanh_sang(40, 15, 11, 4, 124, "NO", 45, 17, 124);
			Sleep(200);
			PlaySound(TEXT("Khong Thanh Cong.wav"), NULL, SND_SYNC);
			return;
		}
		else
		{
			thanh_sang(53, 15, 11, 4, 124, "YES", 57, 17, 124);
			Sleep(200);
			thanh_sang(53, 15, 11, 4, 71, "YES", 57, 17, 71);
			Sleep(200);
		}
		setColor_TextAndBackground(0);

		int idx = hashFunction(word);//tìm vị trí của từ cần xóa
		NODEWORD* wordDelete = tudien[idx].head;//từ cần xóa
		NODEWORD* bef_wordDelete = new NODEWORD;//node trước từ cần xóa
		int sosanh;//=0 thì bằng nhau

		while (wordDelete != NULL && compareString(wordDelete->info.tu, word) != 0)
		{
			//cập nhật lại 2 node
			bef_wordDelete = wordDelete;
			wordDelete = wordDelete->nextword;
		}

		if (wordDelete == NULL)//khong tim thay node 
			cout << "KHONG TIM THAY TU";
		else if (wordDelete == tudien[idx].head)//node cần xóa là node đầu
			deleteHead(tudien, idx);
		else//node bất kì: xóa sau node q
			delete_BeforeQ(bef_wordDelete);
	}
	dataChange = true;
	if (dataChange)
	{
		XoaManHinh();
		ghiFile(tudien);
		ToMau(41, 13, "Xoa thanh cong !", 11);
		PlaySound(TEXT("correct_2.wav"), NULL, SND_SYNC);
		Sleep(1000);
	}
}
//thong bao sua tu
void thongBaoSuaTu(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu)
{
	XoaManHinh();
	
	ShowCur(0);
	DisableSelection();
	int x = 45;
	int y = 9;
	box(35, y, 29, 10, 4, 9, "");
	ToMau(x, y, "THONG BAO", 12);
	string s1 = "Vui long TRA CUU";
	string s2 = "truoc khi SUA/XOA";
	//box(37, 13, 25, 4, 14, 14, "");
	//ToMau(41, 14, s1, 15);
	//ToMau(41, 16, s2, 15);
	thanh_sang(37, 10, 25, 6, 207, s1, 41, 14, 207);
	thanh_sang(37, 14, 25, 6, 207, s2, 41, 16, 207);
	Sleep(2000);
	setColor_TextAndBackground(0);
	return;

}
//ghi file
void ghiFile(TRANSLATELANGUEGE*& tudien)
{

	ofstream fo;
	fo.open("C:\\Users\\ADMIN\\Downloads\\text2.txt", ios_base::out);
	if (fo.is_open())
	{
		for (int i = 0; i < 26; i++) {
			NODEWORD* p = tudien[i].head;
			if (p == NULL)
				continue;
			while (p != NULL)
			{
				//ghi tu vung
				fo << p->info.tu << "/";

				//ghi loai tu
				string loai = "";
				for (int i = 0; i < size_loaitu; i++)
				{
					loai = p->info.loaitu[i];
					if (loai != "")
						fo << loai << "/";
				}
				

				//ghi nghia
				NODE* nghia = p->info.nghia;
				while (nghia != NULL)
				{
					fo << nghia->key << ";";
					nghia = nghia->next;
				}
				fo << "/";

				//ghi vidu
				NODE* vd = p->info.vidu;
				while (vd != NULL) {
					fo << vd->key << ";";
					vd = vd->next;
				}
				fo << "/\n";
				p = p->nextword;
			}
		}
		fo.close();
	}
	return;
}
//doc file
void docFileTuVung(TRANSLATELANGUEGE*& tudien)
{
	ifstream fileTuDien;
	fileTuDien.open("C:\\Users\\ADMIN\\OneDrive - hcmute.edu.vn\\Máy tính\\TUDIEN_NHOM1_CTDL&GT\\TUDIEN_NHOM1_CTDL&GT\\text2.txt", ios_base::in);
	string docLine;
	if (fileTuDien.fail())
	{
		ToMau(42, 13, "Chua co duong link: Doc File va Ghi File", 10);
		system("pause");
	}
	else
	{
		while (getline(fileTuDien, docLine))
		{
			//xoa ki tu trang thua cuoi chuoi

			if (docLine == "")
				continue;
			NODEWORD* newword = creNodeWord(tudien, docLine);
			addNewWord(tudien, newword);
			//cout << newword->info.tu << endl;
		}
		fileTuDien.close(); // dong tap tin

	}

}


//------------------------------------------GAME 1----------------------------------------------
//giao dien mini game doan chu
void gameDoanChu(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[])
{
	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");

	//luu lich su cau hoi
	TRANSLATELANGUEGE* game = new TRANSLATELANGUEGE;
	game->head = NULL;
	game->tail = NULL;



	NODEWORD* p = new NODEWORD();
	int diemSo = 300;
	int soCauHoi = 5;
	int soLanTraLoi = 3;
	int key = 0;
	int i = 49; //1
	while (true)
	{
		int length;//do dai 1 tu
		bool check;//check xem tu do da xuat hien chua
		string dapAn;//lưu đáp án 
		giaoDienHuongdan(tudien, lichSu);

		key = _getch();
		XoaManHinh();
		box(1, 1, 100, 28, 14, 11, "");

		if (demSoLan_Ignore <= 1)
		{
			cin.ignore();
			++demSoLan_Ignore;
		}

	CauHoiTiepTheo:
		switch (key)
		{
		case 27://esc
			giaoDien3(tudien, lichSu, Arr);
			break;
		case 13://enter
			//cin.ignore();
			ToMau(40, 15, "Dang lua chon cau hoi", 14);
			Sleep(1000);
		RanDomLai:
			p = randomTu(tudien);
			if (p == NULL)
				goto RanDomLai;
			check = checkCauHoi(game, p->info.tu);
			if (p != NULL && check == 0) //p != NULL và chưa xuất hiện trước đó 
			{
				themTuVaoCuoiLichSu(game, p);//luu cau hoi 
				length = p->info.tu.length();
				//key = _getch();


			Replay:

				//box ten gam
				XoaManHinh();
				gotoXY(35, 5);
				SetColor(11);
				text_Animation("M I N I  G A M E  D O A N  C H U", 2000000);

				//box câu
				box(25, 9, 50, 2, 14, 14, "");
				ToMau(45, 8, "Question ", 7);
				ToMauKiTu(54, 8, char(i++), 7);

				//box ĐỀ bài
				box(25, 9, 50, 2, 14, 14, "");
				randomDapAn(p->info.tu);

				//box goi y
				ToMau(40, 13, "Goi y nghia cua tu:", 7);
				ToMauKiTu(49, 14, char(25), 7);
				prinfNghia(p->info.nghia);//in goi y 

				//box tra loi
				ToMau(43, 21, "Moi nhap dap an", 8);
				box(35, 22, 30, 2, 14, 14, "");

				//hien so lan tra loi
				ToMau(66, 23, to_string(soLanTraLoi), 13);

				//diem so
				ToMau(44, 27, "SCORES:", 15);
				ToMau(52, 27, to_string(diemSo), 14);

				//nhap dap an
				gotoXY(36 + ((30 - length) / 2), 23);
				SetColor(11);

				dapAn = "";
				getline(cin, dapAn);

				//cap nhat
				--soLanTraLoi;

				//check dap an
				if (checkDapAn(p->info.tu, dapAn))
				{

					--soCauHoi;
					soLanTraLoi = 3;
					diemSo = diemSo + 100;
					ToMau(45, 18, "CHINH XAC !", 10);
					Sleep(500);
					PlaySound(TEXT("correct.wav"), NULL, SND_SYNC);
					XoaManHinh();
					gotoXY(43, 14);
					SetColor(11);
					text_Animation("dang tai cau hoi", 20000000);
					Sleep(1000);
					//ToMau(45, 14, "ENTER to countinue...", 10);
					if (soCauHoi == 0)
						giaoDienEndGame(tudien, game, lichSu, Arr, diemSo);
					else
						goto CauHoiTiepTheo;
				}
				else
				{
					if (soLanTraLoi == 2)
						diemSo -= 10;
					else if (soLanTraLoi == 1)
						diemSo -= 20;
					else if (soLanTraLoi == 0)
						diemSo -= 30;
					ToMau(42, 18, "KHONG CHINH XAC !", 10);
					--i;//cap nhật hiển thị câu hỏi số i 
					Sleep(400);
					if (soLanTraLoi == 0)
					{
						//chơi hết bộ câu hỏi:
						/*--soCauHoi;
						soLanTraLoi = 3;
						++i;//nếu chơi hết bộ thì không ++i lại
						if (soCauHoi == 0)
							giaoDienEndGame(tudien, game, lichSu, Arr, diemSo);
						goto CauHoiTiepTheo;//pass qua cau tiep theo
						// */

						//chơi sai 3 lần thì dừng:
						giaoDienEndGame(tudien, game, lichSu, Arr, diemSo);
					}
					else
						goto Replay;
				}
			}
		default:
			break;

		}
	}


}
//giao dien huong dan
void giaoDienHuongdan(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu)
{
	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");

	gotoXY(35, 4);
	SetColor(11);
	text_Animation("G U E S S   T H E   W O R D", 6000000);
	PlaySound(TEXT("GUESS THE WORD GAME.wav"), NULL, SND_SYNC);

	int x = 34, y = 7;
	ToMauKiTu(x, y, char(42), 11);
	ToMau(x + 2, y, "Cach choi:", 14);

	ToMau(x + 4, y + 2, "1. ", 15);
	ToMau(x + 7, y + 2, "Tra loi toi da het 10 cau hoi", 15);
	ToMau(x + 4, y + 4, "2. ", 15);
	ToMau(x + 7, y + 4, "Moi cau hoi toi da 3 luot tra loi", 15);

	y = y + 7;
	ToMauKiTu(x, y, char(42), 11);
	ToMau(x + 2, y, "Cach tinh diem:", 14);

	ToMau(x + 4, y + 2, "1. ", 15);
	ToMau(x + 7, y + 2, "Ban se co 300d khoi dong", 15);
	ToMau(x + 4, y + 4, "2. ", 15);
	ToMau(x + 7, y + 4, "Tra loi Dung: +100d", 15);
	ToMau(x + 4, y + 6, "3. ", 15);
	ToMau(x + 7, y + 6, "Tra loi sai lan 1: -10d", 15);
	ToMau(x + 7, y + 8, "Tra loi sai lan 2: -20d", 15);
	ToMau(x + 7, y + 10, "Tra loi sai lan 3: -30d", 15);

	ToMau(5, 27, "< BACK : ESC", 8);
	ToMau(82, 27, "ENTER : START >", 8);
	Sleep(3000);
}
//giao dien EndGame
void giaoDienEndGame(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* game, TRANSLATELANGUEGE* lichSu, string Arr[], int diemSo)
{
	PlaySound(TEXT("beep.wav"), NULL, SND_SYNC);
	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");

	NODEWORD* p = game->head;

	//box điểm số 
	box(42, 4, 15, 2, 14, 14, "");
	ToMau(45, 5, "SCORES: ", 7);
	ToMau(53, 5, to_string(diemSo), 11);

	//xem lai dap an
	ToMau(45, 8, "A N S W E R ", 11);
	int i = 49;//1
	int x = 10;
	int y = 10;
	string tu;
	NODE* nghia = new NODE();
	while (p != NULL)
	{
		tu = p->info.tu;
		nghia = p->info.nghia;
		ToMauKiTu(x++, y, char(i++), 7);//1
		ToMau(x++, y, ". ", 7);//. 

		ToMau(x, y, tu, 11);//tu vung
		ToMau(x++ + tu.length(), y, ":", 7);//:
		x += tu.length();

		while (nghia != NULL)
		{
			ToMau(++x, y, nghia->key, 15);//nghia
			x += nghia->key.length();
			if (nghia->next == NULL)
				ToMau(x++, y++, ".", 15);//.
			else ToMau(x++, y, ",", 15);//,
			nghia = nghia->next;
		}
		p = p->nextword;
		++y;
		x = 10;
		//y = 7;
	}

	ToMau(5, 27, "< BACK : ESC", 8);
	ToMau(82, 27, "ENTER : START >", 8);
	int key = 0;
	while (true)
	{
		key = _getch();
		switch (key)
		{
		case 13: //enter to countinue
			gameDoanChu(tudien, lichSu, Arr);
			break;
		case 27://esc
			giaoDien3(tudien, lichSu, Arr);
			break;
		default:
			break;
		}
	}
	system("pause");

}
//check câu hỏi mới có xuất hiện trước đó hay chưa
bool checkCauHoi(TRANSLATELANGUEGE* game, string s)
{
	NODEWORD* p = new NODEWORD();
	p = game->head;
	string tu;
	while (p != NULL)
	{
		tu = p->info.tu;
		if (compareString(s, tu) == 0) //bang nhau
			return true; //co xuat hien roi
		p = p->nextword;
	}
	return false;//chua xuatt hien
}
//check kqua
bool checkDapAn(string ketQua, string s)
{
	s = chuanHoa(s);
	if (compareString(s, ketQua) == 0)//đúng
		return true;
	return false;
}
//in gọi ý nghĩa của từ
void prinfNghia(NODE* nghia)
{
	string goiY = "";
	for (NODE* p = nghia; p != NULL; p = p->next)
	{
		goiY += p->key;
		if (p->next != NULL)
			goiY += ", ";
	}
	int n = goiY.length();
	ToMau((100 - n) / 2, 15, goiY, 14);

}
//random dap an
void randomDapAn(string da)
{
	int n = da.length();
	srand(time(NULL));
	int idx_rand;
	int doDaiCauHoi = 2 * da.length();
	int x = 27 + (50 - (doDaiCauHoi + (doDaiCauHoi - 1))) / 2;
	int y = 10;
	int count = 1;
	int BOOL[50] = { 0 }; //mảng để ktra trùng hay chưa 
	while (count <= n)
	{
		idx_rand = rand() % n;
		if (BOOL[idx_rand] == 0)//phần từ thứ idx_rand chưa có 
		{
			ToMauKiTu(x, y, da[idx_rand], 11);
			x += 2;
			if (count == n)
				ToMauKiTu(x, y, char(0), 15);
			else ToMauKiTu(x, y, char(47), 15);
			x += 2;
			++count;
			BOOL[idx_rand] = 1;//cap nhat lai là true để biết đã có phần tử này rồi 
		}
	}
}
//random Tu
NODEWORD* randomTu(TRANSLATELANGUEGE* tudien)
{
	//lay chi so hashtable
	srand(time(NULL));
	int idx = rand() % 26;//0-25

	//dem so luong node trong hash[idx]
	NODEWORD* p = tudien[idx].head;
	int count = 0;
	while (p != NULL)
	{
		++count;
		p = p->nextword;
	}
	//cout << count;

	//random 1 node trong hash[idx]:
	NODEWORD* keyNode = new NODEWORD();
	if (count != 0)
	{
		int idx_keyNode = rand() % count + 1;

		//duyet lay node
		p = tudien[idx].head;
		for (; p != NULL; p = p->nextword)
		{
			if (idx_keyNode == 1)
			{
				keyNode = p;
				return keyNode;
			}
			--idx_keyNode;
		}
	}
	return NULL;

}


//------------------------------------------GAME 2----------------------------------------------
//GAME 2: LISTEN - WRITE
void gameNgheViet(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[])
{
	XoaManHinh();

	//tao mang luu cau hoi da ra
	string B[100] = { "" };

	while (true)
	{
		int diemSo = 300;
		int soCauHoi = 5;
		int soLanTraLoi = 3;
		string dapAn = "";
		int i = 49;//1
		int randomQues;
		int key = 0;
		bool checkCauHoi;
		giaoDienHuongDanGame2(tudien);

		key = _getch();
		if (demSoLan_Ignore2 <= 1)
		{
			cin.ignore();
			++demSoLan_Ignore2;
		}

	CauHoiTiepTheo:
		switch (key)
		{
		case 27://esc
			giaoDien3(tudien, lichSu, Arr);
			break;
		case 13://enter
		RanDomLai:
			randomQues = randomCauHoiGame2();
			checkCauHoi = checkCauHoiGame2(B, randomQues); //check xem da co hay chua
			if (checkCauHoi == 1)//neu da co xuat hien roi
				goto RanDomLai;
			if (checkCauHoi == 0 && Arr[randomQues] != "")
			{
				string tu = Arr[randomQues];
				themTuVaoMangKetQua(Arr, randomQues, B);
			Replay:
				XoaManHinh();
				box(1, 1, 100, 28, 14, 11, "");
				//TEN GAME
				gotoXY(35, 5);
				SetColor(11);
				text_Animation("L I S T E N   A N D   W R I T E", 2000000);

				//box câu
				//box(25, 9, 50, 2, 14, 14, "");
				ToMau(45, 8, "Question ", 7);
				ToMauKiTu(54, 8, char(i++), 7);

				//box dien dap an
				box(35, 18, 30, 2, 14, 14, "");

				//diem so
				ToMau(45, 24, "SCORES:", 15);
				ToMau(53, 24, to_string(diemSo), 14);

				if (soLanTraLoi == 3)//chỉ cho nghe lần đầu tiên
				{

					//thong bao dem nguoc
					demNguoc(51, 49, 13);
					Sleep(200);
					//in: listening...
					ToMau(44, 13, "Listening...", 11);
					Sleep(500);

					for (int i = 1; i <= 3; i++)
					{
						playCauHoiGame2(randomQues);//doc tu vung
						Sleep(1000);
					}


					//xoa "listenig...:
					xoaKiTu(44, 13, "Listening....");
					Sleep(200);
				}

				//box tra loi
				ToMau(43, 17, "Moi nhap dap an:", 10);

				//hien so lan tra loi
				ToMau(45, 22, "Con lai: ", 15);
				ToMau(55, 22, to_string(soLanTraLoi), 10);

				//nhap dap an
				gotoXY(36 + ((30 - tu.length()) / 2), 19);
				SetColor(11);
				dapAn = "";
				getline(cin, dapAn);


				//cap nhat
				--soLanTraLoi;

				//check dap an
				if (checkDapAn(Arr[randomQues], dapAn))
				{
					--soCauHoi;
					soLanTraLoi = 3;
					diemSo = diemSo + 100;
					ToMau(45, 13, "CHINH XAC !", 10);
					Sleep(200);
					PlaySound(TEXT("correct.wav"), NULL, SND_SYNC);
					XoaManHinh();
					gotoXY(40, 14);
					SetColor(11);
					text_Animation("dang tai cau hoi", 20000000);
					Sleep(1000);
					//
					if (soCauHoi == 0)
						giaoDienEndGame2(tudien, lichSu, Arr, B, diemSo, soCauHoi);
					else
						goto CauHoiTiepTheo;
				}
				else
				{
					if (soLanTraLoi == 2)
						diemSo -= 10;
					else if (soLanTraLoi == 1)
						diemSo -= 20;
					else if (soLanTraLoi == 0)
						diemSo -= 30;
					ToMau(42, 13, "KHONG CHINH XAC !", 10);
					--i;
					Sleep(400);
					//muốn cho chơi hết 10c hoặc dừng tùy ý
					if (soLanTraLoi == 0)
					{
						//chơi hết 10c :
						/*--soCauHoi;
						if (soCauHoi == 0)
							giaoDienEndGame2(tudien, lichSu, Arr, B, diemSo);
						goto CauHoiTiepTheo;//pass qua cau tiep theo */

						//trả lời sai 3 lần thì stop:
						giaoDienEndGame2(tudien, lichSu, Arr, B, diemSo, soCauHoi);
					}
					else
						goto Replay;
				}

				system("pause");
			}
			break;
		default:
			break;
		}
	}
}
//giao dien EndGame2
void giaoDienEndGame2(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[], string B[], int diemSo, int soCauHoi)
{
	PlaySound(TEXT("beep.wav"), NULL, SND_SYNC);
	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");

	//box điểm số 
	box(42, 4, 15, 2, 14, 14, "");
	ToMau(45, 5, "SCORES: ", 7);
	ToMau(53, 5, to_string(diemSo), 11);

	//xem lai dap an
	ToMau(45, 8, "A N S W E R ", 11);
	int i = 49;//1
	int x = 25;
	int y = 10;
	string tu;
	int idx = 1;

	//lưu các câu hỏi đã ra theo thứ tự từ 1->. Để dùng cho việc nghe lại ở dưới 
	//oử sttDapAn[1] sẽ lưu index ở mảng B[] của từ ra ở câu hỏi đầu tiên 
	//lát nhập sô 1 -> truyền vào playSound(B[1]) là sẽ phát âm thanh của từ đàu tiên
	int sttDapAn[10];
	int k = 1;

	for (; idx <= 50; idx++)
	{
		if (B[idx] != "")
		{
			sttDapAn[k++] = idx;
			if (soCauHoi < soCauHoi / 2)
				x = 40;
			tu = B[idx];
			ToMauKiTu(x + 1, y, char(i++), 7);//1
			ToMau(x + 1 + 2, y, ". ", 7);//. 
			ToMau(x + 3, y, tu, 11);//tu vung


			y += 2;
			--soCauHoi;
		}
	}
	ToMau(37, 27, "(Press 'NUMBER' to repeat)", 10);
	ToMau(5, 27, "< BACK : ESC", 8);
	ToMau(82, 27, "ENTER : START >", 8);
	int key = 0;
	while (true)
	{
		key = _getch();
		switch (key)
		{
		case 13: //enter to countinue
			gameNgheViet(tudien, lichSu, Arr);
			break;
		case 27://esc
			giaoDien2(tudien, lichSu, Arr);
			break;
		default:
			//int idx_Of_Tu_TrongMangB = STT_TuVung(B, int(key) - 48, soCauHoi);
			playCauHoiGame2(sttDapAn[int(key) - 48]);
			break;
		}
	}
	system("pause");
}
//tìm số thứ tự 
int STT_TuVung(string B[], int key, int soCauHoi_DaTraLoi)
{
	int count = 0;
	for (int i = 1; i <= 48; i++)
	{
		if (count == soCauHoi_DaTraLoi)
			break;
		if (B[i] != "")
			++count;
		if (count == key)
			return i;
	}
	return 0;
}
//giao dien huong dan game 2:
void giaoDienHuongDanGame2(TRANSLATELANGUEGE* tudien)
{
	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");

	gotoXY(34, 4);
	SetColor(11);
	text_Animation("L I S T E N   A N D   W R I T E", 6000000);
	PlaySound(TEXT("listen and write.wav"), NULL, SND_SYNC);
	int x = 34, y = 7;
	ToMauKiTu(x, y, char(42), 11);
	ToMau(x + 2, y, "Cach choi:", 14);

	ToMau(x + 4, y + 2, "1. ", 15);
	ToMau(x + 7, y + 2, "Nghe va dien dap an dung (10 cau hoi)", 15);
	ToMau(x + 4, y + 4, "2. ", 15);
	ToMau(x + 7, y + 4, "Moi cau hoi toi da 3 luot tra loi", 15);

	y = y + 7;
	ToMauKiTu(x, y, char(42), 11);
	ToMau(x + 2, y, "Cach tinh diem:", 14);

	ToMau(x + 4, y + 2, "1. ", 15);
	ToMau(x + 7, y + 2, "Ban se co 300d khoi dong", 15);
	ToMau(x + 4, y + 4, "2. ", 15);
	ToMau(x + 7, y + 4, "Tra loi Dung: +100d", 15);
	ToMau(x + 4, y + 6, "3. ", 15);
	ToMau(x + 7, y + 6, "Tra loi sai lan 1: -10d", 15);
	ToMau(x + 7, y + 8, "Tra loi sai lan 2: -20d", 15);
	ToMau(x + 7, y + 10, "Tra loi sai lan 3: -30d", 15);

	ToMau(5, 27, "< BACK : ESC", 8);
	ToMau(82, 27, "ENTER : START >", 8);
}
//them key vao mang ket qua
void themTuVaoMangKetQua(string Arr[], int idx, string B[])
{
	B[idx] = Arr[idx];
}
//dem nguoc thgian
void demNguoc(char tgian, int x, int y)
{
	int demThoiGian = tgian;
	for (char i = 49; i <= tgian; i++)
	{
		//dem tgian tu 1-2-3
		ToMauKiTu(x, y, char(demThoiGian--), 10);
		Sleep(700);
		xoaKiTu(x, y, "00");//"00" la 2 ki tu
		Sleep(500);
	}
}
//ham xoa ki tu s
void xoaKiTu(int x, int y, string s)
{
	int l = s.length();
	for (int i = x; i <= x + l; i++)
	{
		ToMauKiTu(i, y, char(219), 0);
	}
}
//check cau hoi
bool checkCauHoiGame2(string B[], int idx_rand)
{
	return B[idx_rand] != ""; //true: co roi //false: chua co
}
//random cau hoi
int randomCauHoiGame2()
{
	srand(time(NULL));
	int i = rand() % 43 + 1;
	return i;
}
//list cau hoi
void playCauHoiGame2(int i)
{

	switch (i)
	{
	case 1:
		//tu = "apple";
		PlaySound(TEXT("apple.wav"), NULL, SND_SYNC);
		break;
	case 2:
		//tu = "ball";
		PlaySound(TEXT("ball.wav"), NULL, SND_SYNC);
		break;
	case 3:
		//tu = "ball";
		PlaySound(TEXT("about.wav"), NULL, SND_SYNC);
		break;
	case 4:
		//tu = "ball";
		PlaySound(TEXT("add.wav"), NULL, SND_SYNC);
		break;
	case 5:
		//tu = "ball";
		PlaySound(TEXT("bear.wav"), NULL, SND_SYNC);
		break;
	case 6:
		//tu = "ball";
		PlaySound(TEXT("big.wav"), NULL, SND_SYNC);
		break;
	case 7:
		//tu = "ball";
		PlaySound(TEXT("cold.wav"), NULL, SND_SYNC);
		break;
	case 8:
		//tu = "ball";
		PlaySound(TEXT("dad.wav"), NULL, SND_SYNC);
		break;
	case 9:
		//tu = "ball";
		PlaySound(TEXT("education.wav"), NULL, SND_SYNC);
		break;
	case 10:
		//tu = "ball";
		PlaySound(TEXT("family.wav"), NULL, SND_SYNC);
		break;
	case 11:
		//tu = "ball";
		PlaySound(TEXT("father.wav"), NULL, SND_SYNC);
		break;
	case 12:
		//tu = "ball";
		PlaySound(TEXT("girl.wav"), NULL, SND_SYNC);
		break;
	case 13:
		//tu = "ball";
		PlaySound(TEXT("go.wav"), NULL, SND_SYNC);
		break;
	case 14:
		//tu = "ball";
		PlaySound(TEXT("hat.wav"), NULL, SND_SYNC);
		break;
	case 15:
		//tu = "ball";
		PlaySound(TEXT("house.wav"), NULL, SND_SYNC);
		break;
	case 16:
		//tu = "ball";
		PlaySound(TEXT("king.wav"), NULL, SND_SYNC);
		break;
	case 17:
		//tu = "ball";
		PlaySound(TEXT("lemon.wav"), NULL, SND_SYNC);
		break;
	case 18:
		//tu = "ball";
		PlaySound(TEXT("no.wav"), NULL, SND_SYNC);
		break;
	case 19:
		//tu = "ball";
		PlaySound(TEXT("operation.wav"), NULL, SND_SYNC);
		break;
	case 20:
		//tu = "ball";
		PlaySound(TEXT("past.wav"), NULL, SND_SYNC);
		break;
	case 21:
		//tu = "ball";
		PlaySound(TEXT("pig.wav"), NULL, SND_SYNC);
		break;
	case 22:
		//tu = "ball";
		PlaySound(TEXT("quick.wav"), NULL, SND_SYNC);
		break;
	case 23:
		//tu = "ball";
		PlaySound(TEXT("rice.wav"), NULL, SND_SYNC);
		break;
	case 24:
		//tu = "ball";
		PlaySound(TEXT("student.wav"), NULL, SND_SYNC);
		break;
	case 25:
		//tu = "ball";
		PlaySound(TEXT("table.wav"), NULL, SND_SYNC);
		break;
	case 26:
		//tu = "ball";
		PlaySound(TEXT("zone.wav"), NULL, SND_SYNC);
		break;
	case 27:
		//tu = "ball";
		PlaySound(TEXT("army.wav"), NULL, SND_SYNC);
		break;
	case 28:
		//tu = "ball";
		PlaySound(TEXT("boy.wav"), NULL, SND_SYNC);
		break;
	case 29:
		//tu = "ball";
		PlaySound(TEXT("football.wav"), NULL, SND_SYNC);
		break;
	case 30:
		//tu = "ball";
		PlaySound(TEXT("friend.wav"), NULL, SND_SYNC);
		break;
	case 31:
		//tu = "ball";
		PlaySound(TEXT("good.wav"), NULL, SND_SYNC);
		break;
	case 32:
		//tu = "ball";
		PlaySound(TEXT("happy.wav"), NULL, SND_SYNC);
		break;
	case 33:
		//tu = "ball";
		PlaySound(TEXT("language.wav"), NULL, SND_SYNC);
		break;
	case 34:
		//tu = "ball";
		PlaySound(TEXT("nature.wav"), NULL, SND_SYNC);
		break;
	case 35:
		//tu = "ball";
		PlaySound(TEXT("ocean.wav"), NULL, SND_SYNC);
		break;
	case 36:
		//tu = "ball";
		PlaySound(TEXT("open.wav"), NULL, SND_SYNC);
		break;
	case 37:
		//tu = "ball";
		PlaySound(TEXT("radio.wav"), NULL, SND_SYNC);
		break;
	case 38:
		//tu = "ball";
		PlaySound(TEXT("sea.wav"), NULL, SND_SYNC);
		break;
	case 39:
		//tu = "ball";
		PlaySound(TEXT("technology.wav"), NULL, SND_SYNC);
		break;
	case 40:
		//tu = "ball";
		PlaySound(TEXT("today.wav"), NULL, SND_SYNC);
		break;
	case 41:
		//tu = "ball";
		PlaySound(TEXT("tree.wav"), NULL, SND_SYNC);
		break;
	case 42:
		//tu = "ball";
		PlaySound(TEXT("vocabulary.wav"), NULL, SND_SYNC);
		break;
	case 43:
		//tu = "ball";
		PlaySound(TEXT("yes.wav"), NULL, SND_SYNC);
		break;
	default:
		break;
	}
}
//doc file dap an game 2
void docFileDapAnGame2(string Arr[])

{
	ifstream fileGame2;
	fileGame2.open("C:\\Users\\ADMIN\\OneDrive - hcmute.edu.vn\\Máy tính\\TUDIEN_NHOM1_CTDL&GT\\TUDIEN_NHOM1_CTDL&GT\\ListDapAn.txt", ios_base::in);
	string docLine;
	if (fileGame2.fail())
	{
		ToMau(42, 13, "Chua co duong link: Doc File am thanh !", 10);
		system("pause");
	}
	else
	{

		//while (getline(fileGame2, docLine))
		//{

		for (int i = 1; i <= 43; i++)
		{
			getline(fileGame2, docLine);
			if (docLine == "")
				break;

			string tu = docTuGame2(docLine);
			Arr[i] = tu;
			docLine = "";
			//cout << i << "  " << Arr[i] <<endl;
		}

		//}
	}

}
//doc từ ở file đáp án
string docTuGame2(string& s)
{
	string tu = "";
	string temp = "";
	int i = 0;
	while (s[i] != '/')
	{
		temp += s[i++];
	}
	tu = temp;
	return tu;
}


//-------------------------------------GAME 3-------------------------------------------------------
//GAME 3: NOI CHu
void gameNoiChu(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[])
{
	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");

	string C[sizemax] = { "" };
	int iC = 0;

	int lanDauRaCauHoi = 1;
	int key = 0;
	while (true)
	{
		NODEWORD* p = new NODEWORD();
		int diemSo = 0;
		int soCauHoi = 10;
		int soLanTraLoi = 3;
		string dapAn = "";
		int i = 49;//1
		int randomQues;
		int key = 0;
		bool checkCauHoi;
		int length;//do dai 1 tu
		bool check;//check xem tu do da xuat hien chua
		string dapAnRandom = "";
		giaoDienHuongDanGame3(tudien, lichSu, Arr);

		key = _getch();
		XoaManHinh();
		box(1, 1, 100, 28, 14, 11, "");

		if (demSoLan_Ignore3 <= 1)
		{
			cin.ignore();
			++demSoLan_Ignore3;
		}
	CauHoiTiepTheo:
		switch (key)
		{
		case 27://esc
			giaoDien3(tudien, lichSu, Arr);
			break;
		case 13://enter
			ToMau(40, 15, "Dang lua chon cau hoi", 14);
		RanDomLai:
			if (lanDauRaCauHoi == 1)
			{
				p = randomTu(tudien);

			}
			else
			{
				p = randomTuGame3(tudien, lichSu, Arr, dapAn);
			}
			if (p == NULL)
				goto RanDomLai;
			checkCauHoi = checkCauHoiGame3(C, p->info.tu); //check xem da co hay chua
			if (checkCauHoi == 1)//neu da co xuat hien roi
				goto RanDomLai;
			lanDauRaCauHoi++;
			if (checkCauHoi == 0)
			{
				string tu = p->info.tu;
				themTuVaoLuuTru(C, iC, tu);
			Replay:
				XoaManHinh();
				box(1, 1, 100, 28, 14, 11, "");
				//TEN GAME
				gotoXY(37, 5);
				SetColor(11);
				text_Animation("W O R D   L I N K   G A M E", 2000000);

				//box câu
				//box(25, 9, 50, 2, 14, 14, "");
				ToMau(45, 8, "Question ", 7);
				ToMauKiTu(54, 8, char(i++), 7);

				//box cau hoi
				box(25, 9, 50, 2, 14, 14, "");
				ToMau(46, 10, tu, 11);

				//box dien dap an
				box(35, 18, 30, 2, 14, 14, "");


				//diem so
				ToMau(45, 24, "SCORES:", 15);
				ToMau(53, 24, to_string(diemSo), 14);

				/*if (soLanTraLoi == 3)//chỉ cho nghe lần đầu tiên
				{

					//thong bao dem nguoc
					demNguoc(51, 49, 13);
					Sleep(200);
					//in: listening...
					ToMau(44, 13, "Listening...", 11);
					Sleep(500);

					for (int i = 1; i <= 3; i++)
					{
						playCauHoiGame2(randomQues);//doc tu vung
						Sleep(1000);
					}


					//xoa "listenig...:
					xoaKiTu(44, 13, "Listening....");
					Sleep(200);
				} */

				//box tra loi
				ToMau(43, 17, "Moi nhap dap an:", 10);

				//hien so lan tra loi
				ToMau(45, 22, "Con lai: ", 15);
				ToMau(55, 22, to_string(soLanTraLoi), 10);

				//nhap dap an
				gotoXY(36 + ((30 - tu.length()) / 2), 19);
				SetColor(11);
				dapAn = "";
				getline(cin, dapAn);

				//cap nhat
				--soLanTraLoi;

				//check dap an
				if (checkDapAnGame3(p->info.tu, dapAn))
				{
					themTuVaoLuuTru(C, iC, dapAn);
					--soCauHoi;
					soLanTraLoi = 3;
					diemSo = diemSo + 100;
					ToMau(45, 15, "CHINH XAC !", 10);
					Sleep(500);
					PlaySound(TEXT("correct.wav"), NULL, SND_SYNC);
					XoaManHinh();
					gotoXY(45, 14);
					SetColor(11);
					text_Animation("dang tai du lieu", 20000000);
					Sleep(1000);
					//ToMau(45, 14, "ENTER to countinue...", 10);
					if (soCauHoi == 0)
						giaoDienEndGame3(tudien, lichSu, Arr, C, diemSo, soCauHoi);
					else
						goto CauHoiTiepTheo;
				}
				else
				{
					ToMau(45, 15, "KHONG CHINH XAC !", 10);
					--i;//cap nhật hiển thị câu hỏi số i 
					Sleep(400);
					if (soLanTraLoi == 0)
					{
						//chơi hết bộ câu hỏi:
						/*--soCauHoi;
						soLanTraLoi = 3;
						++i;//nếu chơi hết bộ thì không ++i lại
						if (soCauHoi == 0)
							giaoDienEndGame(tudien, game, lichSu, Arr, diemSo);
						goto CauHoiTiepTheo;//pass qua cau tiep theo
						// */

						//chơi sai 3 lần thì dừng:
						giaoDienEndGame3(tudien, lichSu, Arr, C, diemSo, soCauHoi);
					}
					else
						goto Replay;
				}
			}
		}

	}
}
//giao end game 3
void giaoDienEndGame3(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[], string C[], int diemSo, int soCauHoi)
{
	PlaySound(TEXT("beep.wav"), NULL, SND_SYNC);
	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");

	//box điểm số 
	box(42, 4, 15, 2, 14, 14, "");
	ToMau(45, 5, "SCORES: ", 7);
	ToMau(53, 5, to_string(diemSo), 11);

	//xem lai dap an
	ToMau(45, 8, "A N S W E R ", 11);
	int i = 49;//1
	int x = 25;
	int y = 10;
	string tu;
	int idx = 0;

	while (C[idx++] != "")
	{
		if (soCauHoi < soCauHoi / 2)
			x = 40;
		tu = C[idx];
		ToMauKiTu(x + 1, y, char(i++), 7);//1
		ToMau(x + 1 + 2, y, ". ", 7);//. 
		ToMau(x + 5, y, tu, 11);//tu vung
		--soCauHoi;
		y += 2;
	}

	ToMau(5, 27, "< BACK : ESC", 8);
	ToMau(82, 27, "ENTER : START >", 8);
	int key = 0;
	while (true)
	{
		key = _getch();
		switch (key)
		{
		case 13: //enter to countinue
			gameNoiChu(tudien, lichSu, Arr);
			break;
		case 27://esc
			giaoDien3(tudien, lichSu, Arr);
			break;
		default:
			break;
		}
	}
	system("pause");

}
//giao dien huong dan game 3
void giaoDienHuongDanGame3(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[])
{
	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");

	gotoXY(40, 4);
	SetColor(11);
	text_Animation("W O R D   L I N K ", 6000000);
	PlaySound(TEXT("game3.wav"), NULL, SND_SYNC);
	int x = 32, y = 7;
	ToMauKiTu(x, y, char(42), 11);
	ToMau(x + 2, y, "Cach choi:", 14);

	ToMau(x + 4, y + 2, "1. ", 15);
	ToMau(x + 7, y + 2, "Chu cai cuoi cung phai trung voi chu cai dau tien", 15);


	y = y + 7;
	ToMauKiTu(x, y, char(42), 11);
	ToMau(x + 2, y, "Cach tinh diem:", 14);

	ToMau(x + 4, y + 2, "1. ", 15);
	ToMau(x + 7, y + 2, "Ban se co 300d khoi dong", 15);
	ToMau(x + 4, y + 4, "2. ", 15);
	ToMau(x + 7, y + 4, "Tra loi Dung: +100d", 15);

	ToMau(5, 27, "< BACK : ESC", 8);
	ToMau(82, 27, "ENTER : START >", 8);
}
//checkdap an
bool checkDapAnGame3(string deBai, string dapAn)
{
	int l = deBai.length();
	dapAn = chuanHoa(dapAn);
	if (dapAn[0] == deBai[l - 1])
		return true;
	return false;
}
//them tu vao mang dap an
void themTuVaoLuuTru(string C[], int& idx, string s)
{
	C[idx] = s;
	idx++;
}
//check cau hoi game 3
bool checkCauHoiGame3(string C[], string s)
{
	int i = 0;
	while (C[i] != "")
	{
		if (C[i] == s)
			return true;
		++i;
	}
	return false;
}
//random tu
NODEWORD* randomTuGame3(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[], string dapAn)
{
	int l = dapAn.length();
	char c = dapAn[l - 1];
	int idx = c - 97;
	//	string c = to_string(dapAn[l - 1]);
		//dem so luong node trong hash[idx]
	NODEWORD* p = tudien[idx].head;
	int count = 0;
	while (p != NULL)
	{
		++count;
		p = p->nextword;
	}

	//random 1 node trong hash[idx]:
	NODEWORD* keyNode = new NODEWORD();
	if (count != 0)
	{
		int idx_keyNode = rand() % count + 1;

		//duyet lay node
		p = tudien[idx].head;
		for (; p != NULL; p = p->nextword)
		{
			if (idx_keyNode == 1)
			{
				keyNode = p;
				return keyNode;
			}
			--idx_keyNode;
		}
	}
	return NULL;

}


//------------------------------------------GAME 4----------------------------------------

//game 4
void gameChonODung(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[])
{

	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");

	//luu lich su cau hoi
	TRANSLATELANGUEGE* game = new TRANSLATELANGUEGE;
	game->head = NULL;
	game->tail = NULL;

CauHoiTiepTheo:
	ToMau(40, 15, "Dang lua chon cau hoi", 14);
	Sleep(1000);

	int diemSo = 300;
	int soCauHoi = 5;
	int soLanTraLoi = 3;
	int i = 49; //1
	int length;
RanDomLai:
	NODEWORD* p = randomTu(tudien);
	p = randomTu(tudien);
	if (p == NULL)
		goto RanDomLai;
	string key = p->info.tu;
	key = toUpper(key);//in hoa tat ca
	string temp = key;//lưu thêm 1 biết từ tạm -> ktra vị trí chữ cái ở chức năng hiện chữ cái đáp án nếu chọn đúng 

	int ktraCauHoi = checkCauHoi(game, p->info.tu);

	if (p != NULL && ktraCauHoi == 0) //p != NULL và chưa xuất hiện trước đó 
	{
		themTuVaoCuoiLichSu(game, p);//luu cau hoi 
		length = p->info.tu.length();
		//key = _getch();
	Replay:

		//box ten gam
		XoaManHinh();
		gotoXY(26, 3);
		SetColor(11);
		text_Animation("C R O S S  W O R D", 2000000);

		//box câu
		box(67, y_ViTriDau, 20, 2, 14, 14, "");

		ToMau(68 + (20 - length) / 2, y_ViTriDau + 1, key, 10);
		//ToMau(45, 8, "Question ", 7);
		//ToMauKiTu(54, 8, char(i++), 7);


		//box goi y
		int x_GoiY = 67;
		int y_GoiY = y_ViTriDau;
		NODE* nghia = p->info.nghia;
		y_GoiY = y_GoiY + 4;
		ToMauKiTu(x_GoiY + 2, y_GoiY, char(16), 72);
		ToMau(x_GoiY + 4, y_GoiY++, "Nghia:", 5);
		y_GoiY = y_GoiY + 1;
		string sNghia;
		while (nghia != NULL)
		{
			sNghia = nghia->key;
			ToMauKiTu(x_GoiY + 4, y_GoiY, char(249), 72);
			ToMau(x_GoiY + 6, y_GoiY++, sNghia, 15);
			nghia = nghia->next;
			y_GoiY++;
		}

		//lua chon
		ToMau(67, y_ViTriDau + 17, "ENTER: Chon dap an !", 8);
		ToMau(67, y_ViTriDau + 18, "TAB: Xem goi y !", 8);

		//diem so
		ToMau(72, y_ViTriDau + 13, "SCORES:", 15);
		ToMau(72 + 8, y_ViTriDau + 13, to_string(diemSo), 14);

		//box dap an
		int xDapAn = 68 + (20 - length) / 2;
		int yDapAn = y_ViTriDau + 10;
		box(67, y_ViTriDau + 9, 20, 2, 14, 14, "");
		ToMau(xDapAn, yDapAn, key, 8);

		int DapAn[5][5] = {}; //full ki tu rong
		bool CheckDapAn[5][5] = { 0 }; //full false

		randomDapAnGame3(DapAn, CheckDapAn, key);


		hien_BangDapAn(DapAn, CheckDapAn);
		//thong bao dem nguoc
		demNguoc(53, 33, 6);
		Sleep(500);
		//hien so lan tra loi
		ToMau(30, y_ViTriDau - 1, "Con lai :", 7);
		ToMau(30 + 10, y_ViTriDau - 1, to_string(soLanTraLoi), 13);
		an_BangDapAn(DapAn, CheckDapAn);

		int demSoODung = 0;
		int b_color = 121;
		int b_highlight = 75;
		int x = x_viTriDau;
		int y = y_ViTriDau;
		int x_cu = x;
		int y_cu = y;
		bool check = true;//ktra xem người dùng có bấm hay không
		bool checkDapAn = false; //ktra xem ô chọn có đáp án đúng hay không 
		int j = (x - x_viTriDau) / khoangCachNgang;
		int i = (y - y_ViTriDau) / khoangCachDoc;
		int x_ChuCai = x + chieuNgangOChu / 2;
		int y_ChuCai = y + chieuDocOChu / 2;

		while (true)
		{
			if (_kbhit)
			{
				if (check == true)
				{
					j = (x_cu - x_viTriDau) / khoangCachNgang;
					i = (y_cu - y_ViTriDau) / khoangCachDoc;
					x_ChuCai = x_cu + chieuNgangOChu / 2;
					y_ChuCai = y_cu + chieuDocOChu / 2;
					gotoXY(x_cu, y_cu);
					if (CheckDapAn[i][j] == 0)
					{//reset lại màu của ô cũ nếu di chuyển sang ô khác

						thanh_sang(x_cu, y_cu, chieuNgangOChu, chieuDocOChu, b_color, "", 0, 0, 0);//rs thanh sang cu
					}
					else
					{
						thanh_sang(x_cu, y_cu, chieuNgangOChu, chieuDocOChu, 0, "", 0, 0, 0);//rs thanh sang cu
						ToMauKiTu(x_ChuCai, y_ChuCai, char(DapAn[i][j]), 11);
					}
					//cập nhật x, y sang vị trí của ô vừa mới di chuyển đến
					x_cu = x; y_cu = y;
					//hightlight ô vừa di chuyển đến
					thanh_sang(x, y, chieuNgangOChu, chieuDocOChu, b_highlight, "", 0, 0, 0);
					check = false;
				}

				char c = _getch();
				if (c == -32)
				{
					check = true;
					c = _getch();
					if (c == 72)//len
					{
						if (y != y_ViTriDau)
							y = y - khoangCachDoc;
						else
							y = y_ViTriDau + khoangCachDoc * (kichThuocBang - 1);
					}
					else if (c == 80)//xuong
					{
						if (y != y_ViTriDau + khoangCachDoc * (kichThuocBang - 1))
							y = y + khoangCachDoc;
						else
							y = y_ViTriDau;
					}
					else if (c == 75)//trai
					{
						if (x != x_viTriDau)
							x = x - khoangCachNgang;
						else x = x_viTriDau + khoangCachNgang * (kichThuocBang - 1);
					}
					else if (c == 77)//phai
					{
						if (x != x_viTriDau + khoangCachNgang * (kichThuocBang - 1))
							x = x + khoangCachNgang;
						else x = x_viTriDau;
					}
					if (checkDapAn == 1)
					{
						//cập nhật x, y sang vị trí của ô vừa mới di chuyển đến
						x_cu = x; y_cu = y;
						checkDapAn = false;
					}
				}
				if (c == 13)//enter
				{
					//từ vị trí x,y hiện tại -> tìm vị trí chữ cái trong mảng để hiển thị 
					checkDapAn = hienThiLuaChon(DapAn, CheckDapAn, x, y, b_color);

					if (checkDapAn == 0) //SAI
					{
						//cap nhat
						--soLanTraLoi;

						//cap nhat lai so lan tra loi :
						ToMau(30 + 10, y_ViTriDau - 1, to_string(soLanTraLoi), 13);
						if (soLanTraLoi == 0)
						{
							//chơi sai 3 lần thì dừng:
							hien_BangDapAn(DapAn, CheckDapAn);
							Sleep(500);
							giaoDienEndGame4(tudien, game, lichSu, Arr, diemSo);//ket thuc game
						}
						check = true;
					}
					else//DUNG
					{
						++demSoODung;//dap an dung

						j = (x - x_viTriDau) / khoangCachNgang;
						i = (y - y_ViTriDau) / khoangCachDoc;
						hienChuCaiDung(key, temp, char(DapAn[i][j]), xDapAn, yDapAn);
						if (demSoODung == length)
						{
							PlaySound(TEXT("correct.wav"), NULL, SND_SYNC);
							--soCauHoi;//trừ đi 1 câu hỏi 
							diemSo = diemSo + 100;//cập nhật điểm 

							setColor_TextAndBackground(15);
							ToMau(83, y_ViTriDau + 14, "+100", 10);
							Sleep(350);
							xoaKiTu(83, y_ViTriDau + 14, "+100");

							setColor_TextAndBackground(14);
							ToMau(72, y_ViTriDau + 13, "SCORES:", 15);
							ToMau(72 + 8, y_ViTriDau + 13, to_string(diemSo), 14);

							hien_BangDapAn(DapAn, CheckDapAn);
							Sleep(1000);
							//neu tra loi dc full bo cau hoi
							if (soCauHoi == 0)
								giaoDienEndGame4(tudien, game, lichSu, Arr, diemSo);//ket thuc game
							else//chưa trả lời hết bộ câu hỏi thì chơi tiếp
							{
								XoaManHinh();
								gotoXY(43, 14);
								SetColor(11);
								text_Animation("dang tai cau hoi", 20000000);
								Sleep(500);
								goto CauHoiTiepTheo;
							}
						}
					}
				}
				if (c == 9)//TAB xem goi y
				{
					diemSo = diemSo - 50;
					hien_BangDapAn(DapAn, CheckDapAn);
					Sleep(2000);
					an_BangDapAn(DapAn, CheckDapAn);

					setColor_TextAndBackground(15);
					ToMau(83, y_ViTriDau + 14, "-50", 10);
					Sleep(350);
					xoaKiTu(83, y_ViTriDau + 14, "-50");

					setColor_TextAndBackground(15);
					ToMau(72, y_ViTriDau + 13, "SCORES:", 15);
					ToMau(72 + 8, y_ViTriDau + 13, to_string(diemSo), 14);

					j = (x - x_viTriDau) / khoangCachNgang;
					i = (y - y_ViTriDau) / khoangCachDoc;
					if (CheckDapAn[i][j] == false)
						check = true;
				}
			}
		}
	}
}
//giao dien huong dan
void giaoDienHuongDanGame4(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* lichSu, string Arr[])
{
	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");

	gotoXY(40, 4);
	SetColor(11);
	text_Animation("C R O S S  W O R D", 6000000);
	PlaySound(TEXT("Cross word game.wav"), NULL, SND_SYNC);

	int x = 34, y = 7;
	ToMauKiTu(x, y, char(42), 11);
	ToMau(x + 2, y, "Cach choi:", 14);

	ToMau(x + 4, y + 2, "1. ", 15);
	ToMau(x + 7, y + 2, "Chon o chu dung voi tung chu cai cua 'KEY'", 15);
	ToMau(x + 4, y + 4, "2. ", 15);
	ToMau(x + 7, y + 4, "Moi cau hoi toi da 3 luot tra loi sai", 15);

	y = y + 7;
	ToMauKiTu(x, y, char(42), 11);
	ToMau(x + 2, y, "Cach tinh diem:", 14);

	ToMau(x + 4, y + 2, "1. ", 15);
	ToMau(x + 7, y + 2, "Ban se co 300d khoi dong", 15);
	ToMau(x + 4, y + 4, "2. ", 15);
	ToMau(x + 7, y + 4, "Hoan thanh 1 vong choi: +100d", 15);
	ToMau(x + 4, y + 6, "3. ", 15);
	ToMau(x + 7, y + 6, "Su dung goi y: -50d", 15);
	//ToMau(x + 7, y + 8, "Tra loi sai lan 2: -20d", 15);
	//ToMau(x + 7, y + 10, "Tra loi sai lan 3: -30d", 15);

	ToMau(5, 27, "< BACK : ESC", 8);
	ToMau(82, 27, "ENTER : START >", 8);

	while (true)
	{
		if (_kbhit)
		{
			char c = _getch();
			switch (c)
			{
			case 13://Enter
				gameChonODung(tudien, lichSu, Arr);
				break;
			case 27: //esc
				giaoDien3(tudien, lichSu, Arr);
				break;
			default:
				break;
			}
		}
	}
}
//ve khung dap an
void khungDapAn()
{
	int x = x_viTriDau;
	int y = y_ViTriDau;
	for (int i = 1; i <= kichThuocBang; i++)
	{
		for (int j = 1; j <= kichThuocBang; j++)
		{
			box(x, y, chieuNgangOChu, chieuDocOChu, 14, 14, "");
			x = x + khoangCachNgang;
		}
		y = y + khoangCachDoc;//xuống dòng in 5 ô 
		x = x_viTriDau;
	}
}
//ẩn bảng đáp án
void an_BangDapAn(int DapAn[][5], bool CheckDapAn[][5])
{
	khungDapAn();
	//cap nhat lại x, y ban đầu:
	int x = 0;
	int y = 0;
	for (int i = 0; i < kichThuocBang; i++)
	{
		for (int j = 0; j < kichThuocBang; j++)
		{
			if (CheckDapAn[i][j] == 0)
			{

				x = x_viTriDau + (khoangCachNgang * j);
				y = y_ViTriDau + (khoangCachDoc * i);
				thanh_sang(x, y, chieuNgangOChu, chieuDocOChu, 121, "", 0, 0, 0);
				Sleep(50);
				//box(x, y, chieuNgangOChu, chieuDocOChu, 14, 14, "");
				x = x + khoangCachNgang;
			}
			else
			{
				int c = char(DapAn[i][j]);
				x = x_ChuCai_ODauTien + (khoangCachNgang * j);
				y = y_ChuCai_ODauTien + (khoangCachDoc * i);
				setColor_TextAndBackground(11);
				ToMauKiTu(x, y, c, 11);
			}

		}
		y = y + khoangCachDoc;//xuống dòng in 5 ô 
		x = x_viTriDau;
	}
}
//hiện bảng đáp án
void hien_BangDapAn(int DapAn[][5], bool CheckDapAn[][5])
{
	khungDapAn();

	//dựa vào vị trí ở mảng -> tìm vị trí trên bảng:
	//vị trí chữ cái đầu tiên ở ô đầu tiên nếu có

	//tìm vị trí tren bảng đap án
	for (int i = 0; i < kichThuocBang; i++)
	{
		for (int j = 0; j < kichThuocBang; j++)
		{
			int vitriX = x_ChuCai_ODauTien + (j * khoangCachNgang);
			int vitriY = y_ChuCai_ODauTien + (i * khoangCachDoc);
			char c = char(DapAn[i][j]);
			if (c != ' ')
			{
				if (c >= 97 && c <= 122)
				{
					c -= 32;
				}

			} //đưa về chữ in hoa
			ToMauKiTu(vitriX, vitriY, c, 11);
		}
	}

}
//lưu chữ cái của từ vào mảng DapAn 2 chiều 
bool luuVaoMang2Chieu(int DapAn[][5], int chuCai, int i, int j)
{
	char c = DapAn[i][j];
	//in hoa
	if (c != ' ')
	{
		if (c >= 97 && c <= 122)
		{
			c -= 32;
		}

	} //đưa về chữ in hoa	
	if (c >= 97 && c <= 122 || c >= 65 && c <= 90)//ktra vị trí đó đã có chữ cái hay chưa
		return false;//neeus co roi

	DapAn[i][j] = char(chuCai);//nếu chưa
	return true;
}
//random dap an
void randomDapAnGame3(int DapAn[][5], bool CheckDapAn[][5], string da)
{
	int n = da.length();
	srand(time(NULL));

	int chuCai_random;
	int doDaiCauHoi = 2 * da.length();

	int count = 1;//đếm số kí tự chữ cái của từ
	int BOOL[30] = { 0 }; //mảng để ktra trùng hay chưa 
	bool check;
	while (count <= n)//khi nào đủ số chữ cái thì dừng
	{
		chuCai_random = rand() % n;
		if (BOOL[chuCai_random] == 0)//phần từ thứ idx_rand chưa có 
		{
			/*ToMauKiTu(x, y, da[idx_rand], 11);
			x += 2;
			if (count == n)
				ToMauKiTu(x, y, char(0), 15);
			else ToMauKiTu(x, y, char(47), 15);*/
			//random vitri i, j dể lưu vào mảng 2 chiều DapAn[5][5]-> lát check đáp án, dễ thao tác
			do {
				int i_random = rand() % 5;
				int j_random = rand() % 5;
				check = luuVaoMang2Chieu(DapAn, da[chuCai_random], i_random, j_random);//check xem đã lưu đc chưa
			} while (check == 0);

			++count;
			BOOL[chuCai_random] = 1;//cap nhat lai là true để biết đã có phần tử này rồi 
		}
	}

	//
	
}
//hiển thị lụa chọn 
bool hienThiLuaChon(int DapAn[][5], bool CheckDapAn[][5], int x, int y, int b_color)
{

	int j = (x - x_viTriDau) / khoangCachNgang;
	int i = (y - y_ViTriDau) / khoangCachDoc;
	int x_ChuCai = x + chieuNgangOChu / 2;
	int y_ChuCai = y + chieuDocOChu / 2;

	int checkChuCai = DapAn[i][j];
	if (checkChuCai != ' ')
	{
		if (checkChuCai >= 97 && checkChuCai <= 122)
		{
			checkChuCai -= 32;
		}

	} //đưa về chữ in hoa
	thanh_sang(x, y, chieuNgangOChu, chieuDocOChu, 0, "", 0, 0, 0);//rs thanh sang cu
	ToMauKiTu(x_ChuCai, y_ChuCai, char(checkChuCai), 11);
	Sleep(500);

	if (checkChuCai >= 97 && checkChuCai <= 122 || checkChuCai >= 65 && checkChuCai <= 90)
	{
		CheckDapAn[i][j] = true;//Lưu vị trí đó đã chọn đúng để k chọn lại 
		//thong bao dung
		//PlaySound(TEXT("correct.wav"), NULL, SND_SYNC);
		int soLanChopNhay = 3;
		for (int k = 1; k <= 3; k++)
		{
			thanh_sang(x, y, chieuNgangOChu, chieuDocOChu, 185, "", 0, 0, 0);//rs thanh sang cu
			Sleep(100);
			thanh_sang(x, y, chieuNgangOChu, chieuDocOChu, 11, "", 0, 0, 0);//rs thanh sang cu
			Sleep(100);
		}
		thanh_sang(x, y, chieuNgangOChu, chieuDocOChu, 0, "", 0, 0, 0);//rs thanh sang cu
		ToMauKiTu(x_ChuCai, y_ChuCai, char(checkChuCai), 11);
		return true;
	}
	else
	{
		//thong bao sai
		//thanh_sang(x, y, chieuNgangOChu, chieuDocOChu, b_color, "", 0, 0, 0);//rs thanh sang cu
		return false;
	}

}
//giao dien EndGame4
void giaoDienEndGame4(TRANSLATELANGUEGE* tudien, TRANSLATELANGUEGE* game, TRANSLATELANGUEGE* lichSu, string Arr[], int diemSo)
{
	PlaySound(TEXT("beep.wav"), NULL, SND_SYNC);
	XoaManHinh();
	box(1, 1, 100, 28, 14, 11, "");

	NODEWORD* p = game->head;

	//box điểm số 
	box(42, 4, 15, 2, 14, 14, "");
	ToMau(45, 5, "SCORES: ", 7);
	ToMau(53, 5, to_string(diemSo), 11);

	//xem lai dap an
	ToMau(45, 8, "A N S W E R ", 11);
	int i = 49;//1
	int x = 10;
	int y = 10;
	string tu;
	NODE* nghia = new NODE();
	while (p != NULL)
	{
		tu = p->info.tu;
		nghia = p->info.nghia;
		ToMauKiTu(x++, y, char(i++), 7);//1
		ToMau(x++, y, ". ", 7);//. 

		ToMau(x, y, tu, 11);//tu vung
		ToMau(x++ + tu.length(), y, ":", 7);//:
		x += tu.length();

		while (nghia != NULL)
		{
			ToMau(++x, y, nghia->key, 15);//nghia
			x += nghia->key.length();
			if (nghia->next == NULL)
				ToMau(x++, y++, ".", 15);//.
			else ToMau(x++, y, ",", 15);//,
			nghia = nghia->next;
		}
		p = p->nextword;
		++y;
		x = 10;
		//y = 7;
	}

	ToMau(5, 27, "< BACK : ESC", 8);
	ToMau(82, 27, "ENTER : START >", 8);
	int key = 0;
	while (true)
	{
		key = _getch();
		switch (key)
		{
		case 13: //enter to countinue
			giaoDienHuongDanGame4(tudien, lichSu, Arr);
			break;
		case 27://esc
			giaoDien3(tudien, lichSu, Arr);
			break;
		default:
			break;
		}
	}
	system("pause");

}
//hiện chữ cái đúng ra màn hình
void hienChuCaiDung(string key, string& temp, char chuCai, int& x, int y)
{
	int demViTri_ChuCai = 0;//đếm vị trí chữ cái trong từ đó -> vì sẽ có từ trùng các chữ cái
	int l = temp.length();
	for (int i = 0; i < l; i++)
	{
		if (temp[i] == chuCai)
		{
			ToMauKiTu(x + demViTri_ChuCai, y, char(temp[i]), 11);
			temp[i] = '0';//hủy chữ cái đã chọn rồi -> để không bị trùng nếu từ có các chữ cái trùng nhau	
			return;
		}
		++demViTri_ChuCai;
	}
}







