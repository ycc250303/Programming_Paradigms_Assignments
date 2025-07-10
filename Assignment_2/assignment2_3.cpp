#include<iostream>
#include<vector>
#include<string>

/*
 * Function Name:	find_number_of_seven
 * Function:		find if the number is divisible by 7 or contains the digit 7
 * Input Parameters:const int num
 * Return Value:	true : the number is divisible by 7 or contains the digit 7
 *					false: the number is not divisible by 7 and does not contain the digit 7
 */
bool find_number_of_seven(const int num)
{
	if(num % 7 == 0|| std::to_string(num).find("7")!= std::string::npos)
		return true;
	return false;
}

/*
 * Function Name:	input_valid_chocolates_num
 * Function:		check if the input is valid and store it in the chocolates_num variable
 * Input Parameters:int &chocolates_num
 * Return Value:	the num of chocolates
 */
void input_valid_chocolates_num(int &chocolates_num)
{
	while (true)
	{
		std::cin >> chocolates_num;
		if (std::cin.fail() || chocolates_num < 1)
		{
			std::cout << "Invalid input, please enter another num: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
			break;
	}
}
 
/*
 * Function Name:	eat_chocolates
 * Function:		calculate the last chocolate that remains after eating chocolates
 * Input Parameters:const int chocolates_num
 * Return Value:	the last chocolate that remains after eating chocolates
 */
int eat_chocolates(const int chocolates_num)
{
	std::vector<bool> chocolates(chocolates_num, true);
	int exisiting_chocolates = chocolates_num;
	int index = 0, count = 1;
	while (exisiting_chocolates > 1)
	{
		if (chocolates[index])//if the chocolate exists
		{
			if (find_number_of_seven(count))
			{
				chocolates[index] = false;
				exisiting_chocolates--;//reduce the number of chocolates
			}
		}
		count++;
		do{
			index = (index + 1) % chocolates_num;
		} while (!chocolates[index]);//if the chocolate is eaten, find the next available chocolate
	}
	for (int i = 0; i < chocolates_num; i++)//find the last chocolate that remains
		if (chocolates[i])
			return i + 1;
	return -1;
}


/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
	std::cout << "Please the number of chocolates: ";
	int chocolates_num;
	//input_the_number_of_chocolates
	input_valid_chocolates_num(chocolates_num);
	int remain_chocolate = eat_chocolates(chocolates_num);
	std::cout << "The last chocolate is " << remain_chocolate << std::endl;

	return 0;
}