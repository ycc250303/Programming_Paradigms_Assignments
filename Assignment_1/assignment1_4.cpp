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
            cout << "输入信息错误，请重新输入学生信息。" << endl;
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
            cout << "输入信息错误，请重新输入学生信息。" << endl;
            continue;
        }
        break;
    }
    return in;
}

ostream& operator<<(ostream& out, stu s) {
    out << "学生姓名：" << s.name << endl;
    out << "学生学号：" << s.number << endl;
    out << "学生年龄：" << s.age << endl;
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

    cout << "请输入学生的姓名、学号、年龄信息，中间用空格隔开：" << endl;
    while ((cin >> stu_initial)) {
        cout << "初始的学生信息如下:" << endl;
        cout << stu_initial;
        break;
    }
 
    cout << "请修改学生的信息" << endl;
    while ((cin >> *sp)) {
        if (check(stu_initial, stu_modify))
        {
            *sp = student();
            cout << "输入信息相同，请重新修改" << endl;
            continue;
        }  
        cout << "修改后的学生信息如下:" << endl;
        cout << stu_modify;
        break;
    }

    return 0;
}
