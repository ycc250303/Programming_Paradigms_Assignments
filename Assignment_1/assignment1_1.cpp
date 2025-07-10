//#include <iostream>
//#include<fstream>
//#include<string>
//#include<algorithm>
//using namespace std;
//
//// 计算指定单词在行中出现的次数
//int count_word_occurrences(const string& line, const string& word)
//{
//	unsigned int pos = line.find(word);
//	int count = 0;
//
//	while (pos != string::npos)
//	{
//		count++;
//		pos = line.find(word, pos + 1); // 从下一个位置继续查找
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
//		// 转换为小写
//		transform(lower_line.begin(), lower_line.end(), lower_line.begin(), ::tolower); // 将每个字符转换为小写
//
//		total_count += count_word_occurrences(lower_line, word);
//	}
//
//	infile.close(); // 关闭文件
//	return total_count;
//}
//
//int main()
//{
//	ifstream infile("example.txt", ios::in);
//	if (!infile.is_open())
//	{
//		cout << "文件打开失败!" << endl;
//		return -1;
//	}
//	else
//		cout << "文件打开成功!" << endl;
//
//	string line;
//	string word = "that";
//	int total_count = read_file(infile, word);
//
//	// 查找 "that" 的出现次数
//	
//
//	cout << "单词"<<word<<"在文件中一共出现了" << total_count << "次" << endl;
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