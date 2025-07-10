#include <iostream>
#include <string>
using namespace std;

// ���� string*��ָ�룩���޸��ַ���
void modify_string_by_pointer(string* strPtr) {
	if (strPtr != nullptr) {
		*strPtr += " (ͨ��ָ�봫��)";
	}
}

// ���� string&�����ã����޸��ַ���
void modify_string_by_reference(string& strRef) {
	strRef += "��ͨ�����ô��ݣ�";
}

int main() {
	string str;
	cout << "�������ʼ���ַ���: " << endl;
	cin >> str;
	cout << "��ʼ�ַ���: " << str << endl;

	// ͨ��ָ������޸ĺ���
	modify_string_by_pointer(&str);
	cout << "����ָ���޸ĺ���ַ���: " << str << endl;

	// ͨ�����õ����޸ĺ���
	modify_string_by_reference(str);
	cout << "���������޸ĺ���ַ���: " << str << endl;

	return 0;
}

