#include <iostream>
#include <string>
using namespace std;

int compareString(string s1, string s2);
string chuanHoa(string& temp);
void In_Hoa_Ki_Tu_Dau_Moi_Tu(string& str);
string toUpper(string& s);


string chuanHoa(string& temp)
{

	//chuyen ki tu hoa thanh ki tu thuong
	int n = temp.size();
	for (int i = 0; i < n; i++)
	{
		if (temp[i] >= 'A' && temp[i] <= 'Z')
			temp[i] = temp[i] + 32;

	}
	// xoa ki tu trang thua dau chuoi
	for (int i = 0; i < n; i++) {
		if (temp[i] == ' ') {
			for (int j = i; j < n - 1; j++) {
				temp[j] = temp[j + 1];
			}
			temp[n - 1] = NULL;
			i--;
			n--;
		}
		else break;
	}
	//xoa ki tu trang thua cuoi chuoi
	for (int i = n - 1; i >= 0; i--) {
		if (temp[i] == ' ') {
			temp[i] = NULL;
			n--;
		}
		else break;
	}
	//xoa ki tu thua trang khong hop le
	for (int i = 0; i < temp.length(); i++)
	{
		// nếu 2 kí tự liên tiếp nhau mà là khoảng trắng ==> xóa đi 1 kí tự
		if (temp[i] == ' ' && temp[i + 1] == ' ')
		{
			temp.erase(temp.begin() + i);
			i--;
		}
	}
	/*for (int i = 1; i < n - 1; i++)
	{
		if (temp[i] == temp[i + 1]) {
			for (int j = i; j < n - 1; j++) {
				temp[j] = temp[j + 1];
			}
			temp[n - 1] = NULL;
			i--;
			n--;
		}
	}*/
	return temp;
}
//so sanh 2 chuoi
int compareString(string s1, string s2)
{
	return s1.compare(s2);
	//return 0: nếu 2 chuỗi bằng nhau
	//return -1 | +1: 2 chuỗi không bằng nhau
}

// hàm viết hoa kí tự đầu của mỗi từ
void In_Hoa_Ki_Tu_Dau_Moi_Tu(string& str)
{
	if (str[0] != ' ')
	{
		if (str[0] >= 97 && str[0] <= 122)
		{
			str[0] -= 32;
		}

	}
	// kí tự tại vị trí i là khoảng trắng, i + i khác khoảng trắng thì kí tự tại vị trí i + 1 chính là kí tự đầu tiên của mỗi từ
	for (int i = 0; i < str.length() - 1; i++)
	{
		if (str[i] == ' ' && str[i + 1] != ' ')
		{
			// A: 65
			// B: 66
			// Z: 90
			// a: 97
			// b: 98
			// c: 99
			// z: 122
			if (str[i + 1] >= 97 && str[i + 1] <= 122)
			{
				// - 32 là chuyển kí tự in thường về in hoa
				str[i + 1] -= 32; // <=> str[i + 1] = str[i + 1] - 32;
			}
		}
	}
}

//in hoa 
string toUpper(string& s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] != ' ')
		{
			if (s[i] >= 97 && s[i] <= 122)
			{
				s[i] -= 32;
			}

		} //đưa về chữ in hoa	
	}
	return s;
}