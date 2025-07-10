#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <algorithm>


/*
 * Function Name:
 * Function:
 * Input Parameters:
 * Return Value:
 */

 /*create a class to handle the input and check the specific numbers in the array*/
template<typename T>
class Nums {
private:
	std::vector<T> nums_;
	int k_ = 0;
public:
	/*
	 * Function Name:    inputNumbers
	 * Function:         Input data
	 * Input Parameters: T maxNumCount:the maximum number of input data, if exceeded, it will be prompted to input again
	 *                   T minNumCount:the minimum number of input data, if not reached, it will be prompted to input again
	 *                   unsigned int maxLength: the maximum length of input data, if exceeded, it will be prompted to input again
	 *                   unsigned int minLength: the minimum length of input data, if not reached, it will be prompted to input again
	 * Return Value:     true: input data is valid
	 *                   false: input data is invalid
	 */
	bool InputNumbers(T max_num_count, T min_num_count, unsigned int max_length, unsigned int min_length) {

		/*read input data from the user*/
		std::string input;
		std::getline(std::cin, input);

		/*transform the input string to a vector of numbers*/
		std::istringstream iss(input);
		int temp;
		std::cin.clear();
		/*check if the input is valid*/
		while (iss >> temp) {
			if (iss.fail()) {/*check if the input is not a number*/
				std::cerr << "输入的数不是数字,请重新输入:" << std::endl;
				iss.clear();
				iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return false;
			}
			else if (temp < min_num_count || temp > max_num_count) {/*check if the input is out of range*/
				std::cerr << "输入的数超出范围[" << min_num_count << ',' << max_num_count << "], 请重新输入!" << std::endl;
				iss.clear();
				iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return false;
			}
			else {/*add the number to the vector*/
				nums_.push_back(temp);
			}
			if (nums_.size() >= max_length) {/*check if the vector size is out of range*/
				std::cerr << "数组长度超过" << max_length << ", 请重新输入!" << std::endl;
				iss.clear();
				iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return false;
			}
		}

		if (nums_.size() < min_length) {/*check if the vector size is less than the minimum length*/
			std::cerr << "数组元素个数少于" << min_length << "个,请重新输入!" << std::endl;
			iss.clear();
			iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return false;
		}
		return true;
	}

	/*
	* Function Name:	inputK
	* Function:			input K value
	* Input Parameters:	int maxCount:the maximum K value, if exceeded, it will be prompted to input again
	*                   int minCount:the minimum K value, if not reached, it will be prompted to input again
	* Return Value:		true: input K value is valid
	*                   false: input K value is invalid
	*/
	bool InputK(int max_count, int min_count) {
		std::cin >> k_;
		if (k_ < min_count || k_ > max_count) {/*check if the input is out of range*/
			std::cerr << "输入的K值超出范围[" << min_count << "," << max_count << "],请重新输入!" << std::endl;
			return false;
		}
		return true;
	}

	/*
	* Function Name:	checkSpecificNums
	* Function:			check if the array has specific numbers
	* Input Parameters:	void
	* Return Value:		true: the array has specific numbers
	*					false: the array does not have specific numbers
	*/
	bool CheckSpecificNums() {
		int left = 0, right = 0;
		for (int left = 0; left < nums_.size(); left++) {
			for (int right = left + 1; right < nums_.size(); right++) {/*find all pairs of numbers that are within k distance*/
				if (nums_[left] == nums_[right] && std::fabs(left - right) <= k_) {
					return true;
				}
			}
		}
		return false;
	}
};


/*
 * Function Name:	main
 * Function:		main function
 * Return Value:	0
 */
int main() {
	/*create a Nums object to handle the input and check the specific numbers in the array*/
	Nums<int> nums;

	/*output the input requirements*/
	std::cout << ">>> 输入要求" << std::endl;
	std::cout << "    [1]输入一个整数数组num和一个整数k,分两次输入" << std::endl;
	std::cout << "    [2]数组输入输入为一行正整数,不同数字之间用空格隔开" << std::endl;
	std::cout << "    [3]数组元素大小范围[-10^9,10^9],数组长度范围[1,10^5],K范围[0,10^5]" << std::endl << std::endl;

	/*input the array and check if it is valid*/
	do {
		std::cout << ">>> 第一次输入,请输入一个整数数组:";
	} while (!nums.InputNumbers(1000000000, -1000000000, 100000, 1));
	do {
		std::cout << ">>> 第二次输入,请输入K的值:";
	} while (!nums.InputK(100000, 0));
	/*output the result*/
	std::cout << "数组中是否有满足条件的元素:" << (nums.CheckSpecificNums() ? "true" : "false") << std::endl;

	return 0;
}