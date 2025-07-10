#include <iostream>
#include <string>
using namespace std;

// 接受 string*（指针）并修改字符串
void modify_string_by_pointer(string* strPtr) {
	if (strPtr != nullptr) {
		*strPtr += " (通过指针传递)";
	}
}

// 接受 string&（引用）并修改字符串
void modify_string_by_reference(string& strRef) {
	strRef += "（通过引用传递）";
}

int main() {
	string str;
	cout << "请输入初始的字符串: " << endl;
	cin >> str;
	cout << "初始字符串: " << str << endl;

	// 通过指针调用修改函数
	modify_string_by_pointer(&str);
	cout << "经过指针修改后的字符串: " << str << endl;

	// 通过引用调用修改函数
	modify_string_by_reference(str);
	cout << "经过引用修改后的字符串: " << str << endl;

	return 0;
}

