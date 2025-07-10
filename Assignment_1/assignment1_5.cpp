//#include <iostream>
//using namespace std;
//// 计算给定股票价格数组的最大利润。
//// 如果无法获得利润，则返回0。
//int MaxProfit(int prices[], int length) {
//    if (length == 0) {
//        return false;
//    }
//    int min_price = prices[0];  // 初始化最小价格为第一天的价格
//    int max_profit = 0;         // 初始化最大利润为0
//    for (int i = 1; i < length; ++i) {
//        if (prices[i] < min_price) {
//            min_price = prices[i];  // 更新最小价格
//        }
//        else {
//            int profit = prices[i] - min_price;  // 计算当前利润
//            // 更新最大利润
//            max_profit = (profit > max_profit) ? profit : max_profit;
//        }
//    }
//    return max_profit;
//}
//// 从用户那里接收股票价格数组
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
//            length = 0; // 重置长度，表示无效输入
//            return false;
//        }
//    }
//    return true;
//}
//int main() {
//    int prices[100000]; // 定义一个大小为10^5的数组
//    int length = 0;  // 用于存储实际输入的价格数量
//    while (true) {
//        int back = 0;// 接受返回值,返回为true则结束循环
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
            cout << "输入格式错误,请检查输入数据,并重新输入" << endl;
            iss.clear();
            iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            vec.clear();
            return false;
        }
        else if (num < minPrice || num > maxPrice)
        {
            cout << "价格超出范围,请检查输入数据,请重新输入" << endl;
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
        cout << "无效的输入数据,请检查输入数据,并重新输入" << endl;
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
    cout << "请输入每一天股票的价格" << endl;
    cout << "提示:" << endl;
    cout << "(1 <= prices.length <= 10^5,如果超过,将被截断.)" << endl;
    cout << "(0 <= prices[i] <= 10^4,请用空格分隔数据,输入完成后请按 Enter 键)" << endl;
    cout << "例: 1 2 3 4 5" << endl;

    while (!input(0, 10000, 10000, prices))
    {
        continue;
    }

    max_price = maxPrice(prices);

    cout << endl;
    cout << "输出" << endl;
    cout << "最大卖出价格是:" << max_price << endl;
    return 0;
}
