//#include <iostream>
//using namespace std;
//// ���������Ʊ�۸�������������
//// ����޷���������򷵻�0��
//int MaxProfit(int prices[], int length) {
//    if (length == 0) {
//        return false;
//    }
//    int min_price = prices[0];  // ��ʼ����С�۸�Ϊ��һ��ļ۸�
//    int max_profit = 0;         // ��ʼ���������Ϊ0
//    for (int i = 1; i < length; ++i) {
//        if (prices[i] < min_price) {
//            min_price = prices[i];  // ������С�۸�
//        }
//        else {
//            int profit = prices[i] - min_price;  // ���㵱ǰ����
//            // �����������
//            max_profit = (profit > max_profit) ? profit : max_profit;
//        }
//    }
//    return max_profit;
//}
//// ���û�������չ�Ʊ�۸�����
//int ReadPrices(int prices[], int& length) {
//    cout << "Enter the number of prices (up to 10^5): ";
//    cin >> length;
//    if (length <= 0 || length > 1e5) {
//        cout << "Error number of prices.Enter numbers between 1 and 10^5." << endl;
//        length = 0;
//        return false;
//    }
//    cout << "Enter the prices (each less than 10^4): ";
//    for (int i = 0; i < length; ++i) {
//        cin >> prices[i];
//        if (prices[i] < 0 || prices[i] > 1e4) {
//            cout << "Error price. Please enter a price between 0 and 10^4." << endl;
//            length = 0; // ���ó��ȣ���ʾ��Ч����
//            return false;
//        }
//    }
//    return true;
//}
//int main() {
//    int prices[100000]; // ����һ����СΪ10^5������
//    int length = 0;  // ���ڴ洢ʵ������ļ۸�����
//    while (true) {
//        int back = 0;// ���ܷ���ֵ,����Ϊtrue�����ѭ��
//        back = ReadPrices(prices, length);
//        cin.ignore(1024, '\n');
//        if (back) {
//            break;
//        }
//    }
//    if (length > 0) {
//        int profit = MaxProfit(prices, length);
//        cout << "The maximum profit is: " << profit << endl;
//    }
//    else {
//        cout << "Error prices were entered." << endl;
//    }
//    return 0;
//}

#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
#include <iterator>
using namespace std;

template <typename T>
bool input(T minPrice, T maxPrice, unsigned int maxLength, std::vector<T>& vec)
{
    string str;
    getline(cin, str);

    istringstream iss(str);
    T num;

    while (true)
    {
        iss >> num;
        if (iss.fail())
        {
            cout << "�����ʽ����,������������,����������" << endl;
            iss.clear();
            iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            vec.clear();
            return false;
        }
        else if (num < minPrice || num > maxPrice)
        {
            cout << "�۸񳬳���Χ,������������,����������" << endl;
            iss.clear();
            iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            vec.clear();
            return false;
        }
        else
        {
            vec.push_back(num);
        }
        if (iss.eof() || vec.size() >= maxLength)
        {
            break;
        }
    }
    if (vec.size() <= 0)
    {
        cout << "��Ч����������,������������,����������" << endl;
        iss.clear();
        iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        vec.clear();
        return false;
    }
    return true;
}

template <typename T>
T maxPrice(const vector<T>& vec)
{
    int max_price = 0;
    for (int i = 0; i < static_cast<int>(vec.size()); i++)
    {
        for (int j = i + 1; j < static_cast<int>(vec.size()); j++)
        {
            if (vec[j] - vec[i] > max_price)
            {
                max_price = vec[j] - vec[i];
            }
        }
    }
    return max_price;
}

int main() {

    vector<int> prices;
    int max_price = 0;
    cout << "������ÿһ���Ʊ�ļ۸�" << endl;
    cout << "��ʾ:" << endl;
    cout << "(1 <= prices.length <= 10^5,�������,�����ض�.)" << endl;
    cout << "(0 <= prices[i] <= 10^4,���ÿո�ָ�����,������ɺ��밴 Enter ��)" << endl;
    cout << "��: 1 2 3 4 5" << endl;

    while (!input(0, 10000, 10000, prices))
    {
        continue;
    }

    max_price = maxPrice(prices);

    cout << endl;
    cout << "���" << endl;
    cout << "��������۸���:" << max_price << endl;
    return 0;
}
