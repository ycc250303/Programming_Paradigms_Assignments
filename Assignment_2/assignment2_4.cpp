#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>

/*
 * Function Name:	calculate_decimal_number
 * Function:		calculate the decimal number of a digit string
 * Input Parameters:const std::string k
 * Return Value:    the decimal number of the digit string k
 */
int calculate_decimal_number(const std::string k)
{
	int decimal_number = 0;
	int len = static_cast<int>(k.length());
	for (int i = len-1; i >=0; i--)
		decimal_number += (k[i] - '0') * static_cast<int>(pow(6, len-i-1));
	return decimal_number;
}

/*
 * Function Name:	input_vaild_decimal_number_and_digit_string
 * Function:		check the input of m and k is valid or not
 * Input Parameters:int& m, std::string& k
 * Return Value:	ture: valid input
 *					false: invalid input
 */
void input_vaild_decimal_number_and_digit_string(int& m,std::string& k)
{
	// input m
	while (true)
	{
		std::cin >> m;
		if (!(2 <= m && m <= 20))
		{
			std::cout << "Invalid input for m, please enter a number between 2 and 20." << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		else
			break;
	}
	// input k
	while (true)
	{
		std::cin >> k;
		for (int i = 0; i < static_cast<int>(k.length()); i++)
		{
			if (!(k[i] >= '0' && k[i] <= '5'))
			{
				std::cout << "Invalid input for k, please enter a string of 0-6 characters." << std::endl;
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				k.clear();
				continue;
			}
		}
		// check the value of k
		if (calculate_decimal_number(k) >= 1000000)
		{
			std::cout<<"The value of K exceeds the input limit, please enter a smaller value."<<std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			k.clear();
			continue;
		}
		break;
	}
}

/*
 * Function Name:	calculate_the_cryptographic_key
 * Function:		calculate the cryptographic key by m and n
 * Input Parameters:const int m, const int n
 * Return Value:	a string of the cryptographic key
 */
std::string calculate_the_cryptographic_key(const int m, const int n)
{
	//special case
	if (n == 0)
		return "0";
	//calculate the key
	std::string key = "";
	int remainder = n;
	while (remainder > 0)
	{
		int charactor = remainder % m;
		remainder = remainder / m;
		if (0 <= charactor && charactor <= 9)
			key += charactor + '0';
		else if (10 <= charactor && charactor <= 19)
			key += charactor - 10 + 'A';
	}
	//reverse the key
	reverse(key.begin(), key.end());
	return key;
}

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
	// input m and k
	std::cout << "Please enter m for the decimal number and k for the digit string."<<std::endl;
	std::cout << "Input hint: 2 <= m <= 20, 0 <= n <= 10^6, k is the hex representation of n."<<std::endl;
	int m;
	std::string k;
	input_vaild_decimal_number_and_digit_string(m, k);
	// calculate the cryptographic key
	std::cout << "The cryptographic key is: " << calculate_the_cryptographic_key(m, calculate_decimal_number(k)) << std::endl;
	return 0;
}