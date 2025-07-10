#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

istream& operator>>(istream& iss, vector<float>& v)
{
    float num;
    // ȷ���������������Ϊ 25
    while (v.size() < 25)
    {
        cout << "������һ�������������뵽25��ʱֹͣ����ǰ��������: " << v.size() << "����" << endl;
        iss >> num;

        // ��������Ƿ���Ч
        if (cin.fail())
        {
            cout << "��Ч���룬������һ����������" << endl;
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
 
    // ����˷�ǰ��ֵ
    vector<float>::iterator it;
    cout << "���г˷�ǰ��" << endl;
    cout << v << endl;

    // ���г˷�����
    v = multiple_vector(v);


    // ����˷����ֵ
    cout << "���г˷���" << endl;
    cout << v << endl;
    return 0;
}
