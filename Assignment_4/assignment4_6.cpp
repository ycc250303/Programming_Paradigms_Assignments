#include <iostream>
#include<algorithm>
#include <string>
#include<sstream>

template<typename T>
struct Rectangle {
	T x, y;
	T multiply()const {
		return x * y;
	}

/*
 * Function name:   operator>>
 * Function:        input a Rectangle object from input stream
 * Input parameter: std::istream& in, Rectangle& rectangle
 * Return value:    std::istream&
 */
    friend std::istream& operator>>(std::istream& in,  Rectangle& rectangle) {
        while (true) {
            char temp;
            in >> rectangle.x >> temp  >> rectangle.y;;
            if (in.fail()||temp!=',') {
                std::cerr << "Error input! Please input again!" << std::endl;
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            break;
        }
      
        return in;
    }
/*
 * Function name:   operator<<
 * Function:        output a Rectangle object to output stream
 * Input parameter: std::ostream& out, const Rectangle& rectangle
 * Return value:    std::ostream&
 */
    friend std::ostream& operator<<(std::ostream& out, const Rectangle& rectangle) {
        out << rectangle.x << "," << rectangle.y;
        return out;
    }
};

/*
 * Function name:   max
 * Function:        return the maximum value of three values
 * Input parameter: T t1, T t2, T t3
 * Return value:    T
 */
template<typename T>
T max(T t1, T t2, T t3) {
    if (t1 >= t2 && t1 >= t3)       return t1;
    else if (t2 >= t1 && t2 >= t3)  return t2;
    else                            return t3;
}

/*
 * Function name:   max
 * Function:        return the maximum length of three strings
 * Input parameter: std::string s1, std::string s2, std::string s3
 * Return value:    std::string
 */
std::string max(std::string s1, std::string s2, std::string s3) {
    if (s1.length() >= s2.length() && s1.length() >= s3.length())       return s1;
    else if (s2.length() >= s1.length() && s2.length() >= s3.length())  return s2;
    else                                                                return s3;
}

/*
 * Function name:   max
 * Function:        return the maximum Rectangle object
 * Input parameter: const Rectangle<T>& r1, const Rectangle<T>& r2, const Rectangle<T>& r3
 * Return value:    Rectangle<T>
 */
template<typename T>
Rectangle<T> max(const Rectangle<T>& r1, const Rectangle<T>& r2, const Rectangle<T>& r3) {
    if (r1.multiply() >= r2.multiply() && r1.multiply() >= r3.multiply())        return r1;
    else if (r2.multiply() >= r1.multiply() && r2.multiply() >= r3.multiply())   return r2;
    else                                                                         return r3;
}

/*
 * Function name:   max
 * Function:        return the maximum Rectangle object pointer 
 * Input parameter: Rectangle<T>* r1, Rectangle<T>* r2, Rectangle<T>* r3
 * Return value:    Rectangle<T>*
 */
template<typename T>
Rectangle<T>* max(Rectangle<T>* r1, Rectangle<T>* r2, Rectangle<T>* r3) {
    return new Rectangle<T>(max(*r1, *r2, *r3));
}


/*
 * Function name:   main
 * Function:        main function
 * Return value:    0
 */
int main() {
    /*test max function for int, double, char, string, Rectangle<int>*/
    int a, b, c;
    std::cout << "请输入三个整数:";
    std::cin >> a >> b >> c;
    std::cout <<"最大的整数是:" << max(a, b, c) << std::endl;

    double d1, d2, d3;
    std::cout << "请输入三个浮点数:";
    std::cin >> d1 >> d2 >> d3;
    std::cout << "最大的浮点数是:" << max(d1, d2, d3) << std::endl;

    char ch1, ch2, ch3;
    std::cout << "请输入三个字符:";
    std::cin >> ch1 >> ch2 >> ch3;
    std::cout << "ASCII码最大的字符是:" << max(ch1, ch2, ch3) << std::endl;

    std::string s1, s2, s3;
    std::cout << "请输入三个字符串:";
    std::cin >> s1 >> s2 >> s3;
    std::cout << "长度最大的字符串是:" << max(s1, s2, s3) << std::endl;

    Rectangle<int> r1, r2, r3;
    std::cout << "请输入三个矩形的值 (格式: x,y ):";
    std::cin >> r1>>r2>>r3;

    Rectangle<int> maxRect = max(r1, r2, r3);
    std::cout << "面积最大的矩形是:" << maxRect << std::endl;


	return 0;
}