#include <iostream>
#include <algorithm>

#define MAX_DEGREE 100//maximum degree of numbers

/*
 * Function Name:	input_the_info_of_key
 * Function:		check the input of m, a, n, and b, and input them if they are valid
 * Input Parameters:int& m, int& n, std::string& a, std::string& b
 * Return Value:	void
 */
void input_the_info_of_key(int& m, int& n, std::string& a, std::string& b)
{
	//input m and a
	while (true)
	{
		std::cin >> m >> a;
		if (m <= 0 || m > MAX_DEGREE)
		{
			std::cout << "Invalid input for m, please enter again: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		if (static_cast<int>(a.length()) > MAX_DEGREE)
		{
			std::cout << "Invalid input for a, please enter again: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		break;
	}
	//input n and b
	while (true)
	{
		std::cin >> n >>b;
		if (n <= 0 || n > MAX_DEGREE)
		{
			std::cout << "Invalid input for n, please enter again: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		if (static_cast<int>(b.length()) > MAX_DEGREE)
		{
			std::cout << "Invalid input for b, please enter again: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		break;
	}

}

/*
 * Function Name:	plus_two_integers
 * Function:		sum two integers and return the result as a string
 * Input Parameters:string a, string b
 * Return Value:	a string representing the sum of the two integers
 */
std::string plus_two_integers(std::string a,std::string b)
{
	//reverse the string to make the addition process easier
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	//add the two integers
	int carry = 0;
	std::string result;
	int i = 0;
	while (i < a.length() || i < b.length() || carry)
	{
		//add the carry from previous addition
		int sum = carry;
		if (i < a.length())
			sum += a[i] - '0';
		if (i < b.length())
			sum += b[i] - '0';
		//append the sum to the result string
		result.push_back(sum % 10 + '0');
		carry = sum / 10;
		i++;
	}
	reverse(result.begin(), result.end());
	return result;
}
/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main() {
	int m, n;
	std::string a, b, c;
	std::cout<<"Please enter, in order \nthe digit m of integer a, integer a, the digit n of integer b, integer b."<<std::endl;
	std::cout<<"Input Hint: Separated by spaces"<<std::endl;
	input_the_info_of_key(m, n, a, b);
	std::cout<<"The sum of the two integers is: "<<plus_two_integers(a, b)<<std::endl;
	return 0;
}