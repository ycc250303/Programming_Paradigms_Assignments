#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

istream& operator>>(istream& iss, vector<float>& v)
{
    float num;
    // 确保输入的数据数量为 25
    while (v.size() < 25)
    {
        cout << "请输入一个浮点数，输入到25个时停止（当前输入数量: " << v.size() << "）：" << endl;
        iss >> num;

        // 检查输入是否有效
        if (cin.fail())
        {
            cout << "无效输入，请输入一个浮点数。" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        v.push_back(num);
    }
    return iss;
}

ostream& operator<<(ostream& oss, const vector<float>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        oss << v[i] << " ";
    }
    return oss;
}

vector<float> multiple_vector(const vector<float>& v)
{
    vector<float> result(v.size());
    for (int i = 0; i < v.size(); i++)
    {
       result[i] = v[i] * v[i];
    }
    return result;
}

int main()
{
    vector<float> v;

    cin >> v;
 
    // 输出乘法前的值
    vector<float>::iterator it;
    cout << "进行乘法前：" << endl;
    cout << v << endl;

    // 进行乘法操作
    v = multiple_vector(v);


    // 输出乘法后的值
    cout << "进行乘法后：" << endl;
    cout << v << endl;
    return 0;
}
