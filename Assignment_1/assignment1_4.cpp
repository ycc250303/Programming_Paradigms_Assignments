#include <iostream>
#include <string> 
using namespace std;

typedef struct student {
    string name;
    string number;
    int age = 0;
}stu;


istream& operator>>(istream& in, stu &s) {
    while (true)
    {
        in >> s.name >> s.number >> s.age;
        if (in.fail()) {
            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n');
            s = student();
            cout << "������Ϣ��������������ѧ����Ϣ��" << endl;
            continue;
        }
        break;
    }
    return in;
}

istream& operator>>(istream& in, stu* s) {
    while (true)
    {
        in >> s->name >> s->number >> s->age;
        if (in.fail()) {
            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n');
            *s = student();
            cout << "������Ϣ��������������ѧ����Ϣ��" << endl;
            continue;
        }
        break;
    }
    return in;
}

ostream& operator<<(ostream& out, stu s) {
    out << "ѧ��������" << s.name << endl;
    out << "ѧ��ѧ�ţ�" << s.number << endl;
    out << "ѧ�����䣺" << s.age << endl;
    return out;
}

bool check(student s1, student s2)
{
    if((s1.name == s2.name) && (s1.number == s2.number) && (s1.age == s2.age))
        return true;
    else
        return false;
}

int main() {
    stu stu_initial, * sp;
    stu stu_modify = stu_initial;
    sp = &stu_modify;

    cout << "������ѧ����������ѧ�š�������Ϣ���м��ÿո������" << endl;
    while ((cin >> stu_initial)) {
        cout << "��ʼ��ѧ����Ϣ����:" << endl;
        cout << stu_initial;
        break;
    }
 
    cout << "���޸�ѧ������Ϣ" << endl;
    while ((cin >> *sp)) {
        if (check(stu_initial, stu_modify))
        {
            *sp = student();
            cout << "������Ϣ��ͬ���������޸�" << endl;
            continue;
        }  
        cout << "�޸ĺ��ѧ����Ϣ����:" << endl;
        cout << stu_modify;
        break;
    }

    return 0;
}
