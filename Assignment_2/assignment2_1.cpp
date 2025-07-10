#include <iostream>

/*
 * Function Name:    is_palindrome
 * Function:         check a string is palindrome or not
 * Input Parameters: const std::string str
 * Return Value:     true : the input string is palindrome
 *                   false: the input string is not palindrome
 */
bool is_palindrome(const std::string str) {
	int len = static_cast<int>(str.length());
	for (int i = 0; i < len / 2; i++) {
		if (str[i] != str[len - 1 - i]) {
			return false;
		}
	}
	return true;
}

/*
 * Function Name:    is_palindrome_after_remove_a_char
 * Function:         check a string is palindrome or not after removing a character
 * Input Parameters: const std::string str
 * Return Value:     true : the input string is palindrome after removing a character
 *                   false: the input string is not palindrome after removing a character
 */
bool is_palindrome_after_remove_a_char(const std::string str){
	for (int i = 0; i < str.length(); i++)
	{
		std::string temp_str;
		//remove a character 
		if (i == 0)
			temp_str = str.substr(1, str.length() - 1);
		else
			temp_str = str.substr(0, i) + str.substr(i + 1, str.length() - i - 1);
		//check the removed string is palindrome or not
		if (is_palindrome(temp_str))
			return true;
	}
	return false;
}

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main() {
	std::string str1,str2;
	std::cout << "Please enter a string: ";
	std::cin >> str1;
	//check the string is palindrome or not after removing a character
	if(is_palindrome_after_remove_a_char(str1))
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;

	return 0;
}