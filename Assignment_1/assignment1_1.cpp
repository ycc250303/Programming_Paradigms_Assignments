//#include <iostream>
//#include<fstream>
//#include<string>
//#include<algorithm>
//using namespace std;
//
//// ����ָ�����������г��ֵĴ���
//int count_word_occurrences(const string& line, const string& word)
//{
//	unsigned int pos = line.find(word);
//	int count = 0;
//
//	while (pos != string::npos)
//	{
//		count++;
//		pos = line.find(word, pos + 1); // ����һ��λ�ü�������
//	}
//
//	return count;
//}
//
//int read_file(ifstream& infile,string word)
//{
//	string line;
//	int total_count = 0;
//	while (getline(infile,line ))
//	{
//		string lower_line = line;
//		// ת��ΪСд
//		transform(lower_line.begin(), lower_line.end(), lower_line.begin(), ::tolower); // ��ÿ���ַ�ת��ΪСд
//
//		total_count += count_word_occurrences(lower_line, word);
//	}
//
//	infile.close(); // �ر��ļ�
//	return total_count;
//}
//
//int main()
//{
//	ifstream infile("example.txt", ios::in);
//	if (!infile.is_open())
//	{
//		cout << "�ļ���ʧ��!" << endl;
//		return -1;
//	}
//	else
//		cout << "�ļ��򿪳ɹ�!" << endl;
//
//	string line;
//	string word = "that";
//	int total_count = read_file(infile, word);
//
//	// ���� "that" �ĳ��ִ���
//	
//
//	cout << "����"<<word<<"���ļ���һ��������" << total_count << "��" << endl;
//
//	return 0;
//}

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

/*
Problem 2:
Create a vector<float> and put 25 numbers into it. Then square each number and put
the result back into the same location in the vector. Display the vector before and after the
multiplications.
*/

const int NUM = 25;

void PrintVector(const vector<float>& vec, const string& prompt)
{
    cout << prompt << ": ";
    for (int i = 0; i < NUM; i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

int main()
{
    vector<float> numbers;

    //Initialize
    for (int i = 0; i < NUM; i++) {
        numbers.push_back(static_cast<float>(i + 1));
    }

    PrintVector(numbers, "Original numbers");

    //Square
    for (int i = 0; i < NUM; i++) {
        numbers[i] = pow(numbers[i], 2);
    }

    PrintVector(numbers, "Squared numbers");

    return 0;
}