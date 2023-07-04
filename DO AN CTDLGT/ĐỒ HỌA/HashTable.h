#include <iostream>
#include <string>
//#include <io.h>
//#include <fcntl.h>
#include <fstream>
#include "Word.h"
#include "dohoa.h"
using namespace std;
#if 1
#define size 26
#define size_loaitu 9 //có 9 loại từ trong TA
#define CR_KTK 50 // chieu rong khung tim kiem
#define HIEN_THI_TOI_DA 15 // so tu hien thi toi da o man hinh chinh

struct NODE {
	string key;
	NODE* next;
};

struct NODEINFO {
	string tu;
	string loaitu[size_loaitu];
	NODE* nghia;
	NODE* vidu;
};

struct NODEWORD {
	NODEINFO info;
	NODEWORD* nextword;
};//khai báo 1 node trong bảng băm

struct HASHTABLE {
	NODEWORD* head;
	NODEWORD* tail;
};
typedef HASHTABLE TRANSLATELANGUEGE; //khai báo bảng băm


NODEWORD* checkTuVung(TRANSLATELANGUEGE* tudien, string tu);
void docFileTuVung(TRANSLATELANGUEGE*& tudien);
NODEWORD* inDanhSachTu(TRANSLATELANGUEGE* tudien, string input, int pos);
int demSoTu(TRANSLATELANGUEGE* tudien);
void initTranslateLanguege(TRANSLATELANGUEGE*& tudien);
void deleteNode_Translate(TRANSLATELANGUEGE*& tudien, string word);
void deleteHead(TRANSLATELANGUEGE*& tudien, int idx);
void delete_BeforeQ(NODEWORD* bef_nodeDelete);
void addNewWord(TRANSLATELANGUEGE*& tudien, string NewWord);
void themTuVaoCuoi(TRANSLATELANGUEGE*& tudien, int idx, NODEWORD* NewWord);
int hashFunction(string s);
NODEWORD* timKiem(TRANSLATELANGUEGE* tudien, string newWord);
void duyetLinkedList(NODEWORD* nodeFirst);
bool compareInput(NODEWORD* temp, string input);
NODE* creNode(string word);
NODEWORD* creNodeWord(TRANSLATELANGUEGE*& tudien, string line);
void themNodeMoi(NODE*& nodefirst, string str);
NODEINFO creNodeInfo(string dong);
int loaiTu(string s);
void initHistory(TRANSLATELANGUEGE*& lichSu);

//bien toan cuc
bool dataChange = false; // bien ghi nhan du lieu co thay doi hay khong


//-------------------------------------FUNCTIONS---------------------------------------------

//in danh sach tu goi y
NODEWORD* inDanhSachTu(TRANSLATELANGUEGE* tudien, string input, int pos)
{
	// in ra ds cac tu
	NODEWORD* tuHienTai = NULL; // tu dang duoc highlight trong man hinh chinh

	// neu khung tim kiem k co gia tri, thi in het cac tu ra
	int index = -1;
	if (input != "")
		index = hashFunction(input);

	int x = 39;
	int y = 7;

	int count = 0;
	for (int i = 0; i < 26; i++)
	{
		if (tudien[i].head == NULL)
			continue; // tap tu dien nay khong tu nao, bo qua

		NODEWORD* p = tudien[i].head;
		if (index != -1)
			p = timKiem(tudien, input);

		while (true)
		{
			while (pos > 0 && p != NULL)
			{
				pos--;
				p = p->nextword;
			}
			if (p == NULL)
				break;
			if (count == 0)
			{
				tuHienTai = p;
				setColor_TextAndBackground(252);//set màu chữ hightlight
			}
			else
			{
				setColor_TextAndBackground(15);
			}

			gotoXY(x + 2, y++);
			cout << " " << p->info.tu << " ";
			for (int j = 0; j < 32; j++)
			{
				cout << " ";
			}
			count++;
			p = p->nextword;
			if (p == NULL)
			{
				break;
			}
			if (count >= HIEN_THI_TOI_DA)
				break;
		}
		if (index != -1)
			break;
		if (count >= HIEN_THI_TOI_DA)
			break;
	};
	setColor_TextAndBackground(15); //chuyen mau ve binh thuong
	return tuHienTai;
}

//dem so tu
int demSoTu(TRANSLATELANGUEGE* tudien) {
	int dem = 0;
	for (int i = 0; i < 26; i++)
	{
		if (tudien[i].head == NULL)
		{
			continue;
		}

		NODEWORD* p = tudien[i].head;
		while (p != NULL)
		{
			++dem;
			p = p->nextword;
		}
	}
	return dem;
}

//xoa đầu:
void deleteHead(TRANSLATELANGUEGE*& tudien, int idx)
{
	if (tudien[idx].head->nextword == NULL)//co 1 phan tu
	{
		tudien[idx].head = NULL;
		tudien[idx].tail = NULL;
	}
	else
	{
		NODEWORD* temp = tudien[idx].head;
		tudien[idx].head = tudien[idx].head->nextword;
		delete temp;
	}
}

//Xóa sau node q
void delete_BeforeQ(NODEWORD* bef_nodeDelete)
{
	NODEWORD* nodeDelete = bef_nodeDelete->nextword;
	if (nodeDelete != NULL)
	{
		bef_nodeDelete->nextword = nodeDelete->nextword;
		delete nodeDelete;
	}
}

//thêm 1 từ vựng vào trong HashTable
void addNewWord(TRANSLATELANGUEGE*& tudien, NODEWORD* NewWord)
{
	string tu = chuanHoa(NewWord->info.tu);
	int idx = hashFunction(tu);//dung hàm băm tìm idx để lưu
	themTuVaoCuoi(tudien, idx, NewWord);//thêm vào idx đó
}
//them node cuoi
void themTuVaoCuoi(TRANSLATELANGUEGE*& tudien, int idx, NODEWORD* NewWord)
{
	//nodeAdd: là node thêm giá trị vô node này
	//nodeTail: là node cuối trong hàng đó
	//newNode: là node mới cần thêm vô
	NODEWORD* newNode = NewWord;
	if (tudien[idx].head == NULL)//chưa có gía trị trùng -> thì thêm vô thôi
	{
		tudien[idx].head = newNode;
		tudien[idx].tail = newNode;
	}
	else//có giá trị trùng nhau -> thì thêm vô sau node cuối của hàng idx đó
	{
		tudien[idx].tail->nextword = newNode;
		tudien[idx].tail = newNode;
	}
}

//hash function
int hashFunction(string s)
{
	return s[0] - 97;
}

//tim kiem 1 từ mới nhập hoàn chỉnh với 1 từ trong idx đó
NODEWORD* checkTuVung(TRANSLATELANGUEGE* tudien, string tu)
{
	string NewWord = chuanHoa(tu);
	int idx = hashFunction(NewWord);

	NODEWORD* temp = tudien[idx].head;
	int sosanh;

	while (temp != NULL)
	{
		sosanh = compareString(temp->info.tu, tu);
		if (sosanh == 0)
			return temp;
		temp = temp->nextword;
	}
	return NULL;
}

//tim kiem input hiện tại có trùng với từ nào không 
NODEWORD* timKiem(TRANSLATELANGUEGE* tudien, string input)
{
	string NewWord = chuanHoa(input);
	int idx = hashFunction(NewWord);

	NODEWORD* temp = tudien[idx].head;
	int sosanh;

	while (temp != NULL)
	{
		if (sosanh = compareInput(temp, NewWord) == 1)
			return temp;
		temp = temp->nextword;
	}
	return NULL;
}

//so sánh input với 1 từ cụ thể (không phải so sánh 1 từ hoàn chỉnh)
bool compareInput(NODEWORD* temp, string input)
{
	//so sánh cái input hiện thời với từng từ trong cái idx đó
	// nếu chỉ cần có 1 kí từ trong input đó không trùng với 1 từ nào trong cái idx đó thì là False 
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] != temp->info.tu[i])
			return 0;
	}
	return 1;
}

//duyệt hashtable:
void Prinf(TRANSLATELANGUEGE* tudien)
{
	cout << "SAP XEP THEO CHU CAI:\n";
	for (int i = 0; i < size; i++)
	{
		duyetLinkedList(tudien[i].head);
		cout << endl;
	}
}
//duyet linked list
void duyetLinkedList(NODEWORD* nodeFirst)
{
	NODEWORD* p = nodeFirst;
	while (p != NULL)
	{
		cout << p->info.tu << "  ";
		p = p->nextword;
	}
}

//khởi tạo NODEWORD
NODEWORD* creNodeWord(TRANSLATELANGUEGE*& tudien, string line)
{

	NODEWORD* nodeword = new NODEWORD;
	NODEINFO p = creNodeInfo(line);
	nodeword->info = p;
	nodeword->nextword = NULL;
	return nodeword;
}

//khởi tạo NODEINFO
NODEINFO creNodeInfo(string dong)
{
	NODEINFO p;

	int i = 0;

	// thêm từ
	string tu = "";
	while (dong[i] != '/')
	{
		tu += dong[i++];
	}
	i++;
	p.tu = tu;

	// thêm loại từ
	string loai = "";
	while (dong[i] != '/')
	{
		loai += dong[i++];
	}
	i++;
	int idx_LoaiTu = loaiTu(loai);
	for (int i = 0; i < size_loaitu; i++)
	{
		if (i == idx_LoaiTu)
			p.loaitu[i] = loai;
		else p.loaitu[i] = "";
	}


	// thêm nghĩa
	p.nghia = NULL;
	string nghia = ""; //pos = 0;
	while (dong[i] != '/') {
		nghia += dong[i++];
		// nghia moi
		if (dong[i] == ';')
		{
			//thêm nghĩa mới vào dslk
			themNodeMoi(p.nghia, nghia);
			//p->info.nghia[pos++] = nghia;
			nghia = "";
			i++;
		}
	}
	i++;

	
	// tach vi du
	p.vidu = NULL;
	string vidu = "";
	if (i >= dong.length())
	{
		themNodeMoi(p.vidu, vidu);
		return p;
	}

	while (dong[i] != '/')
	{
		vidu += dong[i++];
		if (dong[i] == ';') 
		{
			themNodeMoi(p.vidu, vidu);
			vidu = "";
			i++;
		}
	}

	return p;
}

//thêm node mới vào đầu danh sách liên kết của NGHĨA và VÍ DỤ
void themNodeMoi(NODE*& nodefirst, string str)
{


	NODE* p = creNode(str);

	if (nodefirst == NULL)//chưa có node 
	{
		nodefirst = p;
	}
	else //đã có node 
	{
		p->next = nodefirst;
		nodefirst = p;
	}
}

//khởi tạo NODE
NODE* creNode(string word)
{
	NODE* p = new NODE();
	p->key = word;
	p->next = NULL;
	return p;
}

//sap xep cac loai tu
int loaiTu(string s)
{
	//0. Danh từ (Noun)
	//1. Đại từ(Pronoun)
	//2. Tính từ(Adjective)
	//3. Động Từ(Verb)
	//4. Trạng Từ(Adverb)
	//5. Từ hạn định(Determiner)
	//6. Giới từ(Preposition)
	//7. Liên từ(Conjunction)
	//8. Thán từ(Interjection)
	string sChuanHoa = chuanHoa(s);
	if (sChuanHoa == "danh tu")
		return 0;
	else if (sChuanHoa == "dai tu")
		return 1;
	else if (sChuanHoa == "tinh tu")
		return 2;
	else if (sChuanHoa == "dong tu")
		return 3;
	else if (sChuanHoa == "trang tu")
		return 4;
	else if (sChuanHoa == "tu han dinh")
		return 5;
	else if (sChuanHoa == "gioi tu")
		return 6;
	else if (sChuanHoa == "lien tu")
		return 7;
	else if (sChuanHoa == "than tu")
		return 8;
	return -1;
}

//khởi tạo các node trong bảng băm
void initTranslateLanguege(TRANSLATELANGUEGE*& tudien)
{
	for (int i = 0; i < size; i++)
	{
		tudien[i].head = NULL;
		tudien[i].tail = NULL;
	}
}

//khởi tạo hash lưu Lịch sử tra từ
void initHistory(TRANSLATELANGUEGE*& lichSu)
{
	lichSu->head = NULL;
	lichSu->tail = NULL;
}
#endif

