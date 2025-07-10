#include <iostream>

#define EVEN_NUMBERS_UP_TO_LEN 5
#define PRIME_NUMBERS_UP_TO_LEN 4

/*
 * Function Name:	calculate_number_of_strings_of_numbers
 * Function:		calculate the decimal number of strings of numbers
 * Input Parameters:const int len
 * Return Value:	the decimal number of strings of numbers
 */
long long calculate_number_of_strings_of_numbers(const int len) {
	long long number_of_strings_of_numbers = 1;
	//calculate the number of strings of numbers
	if (len % 2 == 0)//even numbers
	{
		for (int i = 0; i < len / 2; i++)
		{
			number_of_strings_of_numbers *= EVEN_NUMBERS_UP_TO_LEN;
			number_of_strings_of_numbers *= PRIME_NUMBERS_UP_TO_LEN;
		}
	}
	else//odd numbers
	{
		for (int i = 0; i < (len - 1) / 2; i++)
		{
			number_of_strings_of_numbers *= EVEN_NUMBERS_UP_TO_LEN;
			number_of_strings_of_numbers *= PRIME_NUMBERS_UP_TO_LEN;
		}
		number_of_strings_of_numbers *= EVEN_NUMBERS_UP_TO_LEN;
	}
	return number_of_strings_of_numbers;
}

/*
 * Function Name:	input_valid_length
 * Function:		input the length of the Maoge number and ensure the input is valid
 * Input Parameters:int& len_of_maoge_number
 * Return Value:	void
 */
void input_valid_length(int& len_of_maoge_number) {
	//ensure the input is valid
	while (true) {
		std::cin >> len_of_maoge_number;
		if (std::cin.fail() || len_of_maoge_number <= 0) {
			std::cerr << "Invalid input! Please enter another number: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
			break;
	}
}

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main() {
	int len_of_maoge_number;
	std::cout << "Please enter the length of the Maoge number: ";
	//input the length of the Maoge number
	input_valid_length(len_of_maoge_number);
	//calculate the number of strings of numbers
	long long number_of_strings_of_numbers = calculate_number_of_strings_of_numbers(len_of_maoge_number);
	std::cout << "The size of the Maoge number is: " << number_of_strings_of_numbers << std::endl;

	return 0;
}