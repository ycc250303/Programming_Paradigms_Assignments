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
	int indexDiff_ = 0, valueDiff_ = 0;
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
				std::cerr << "���������������,����������:" << std::endl;
				iss.clear();
				iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return false;
			}
			else if (temp < min_num_count || temp > max_num_count) {/*check if the input is out of range*/
				std::cerr << "�������������Χ[" << min_num_count << ',' << max_num_count << "], ����������!" << std::endl;
				iss.clear();
				iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return false;
			}
			else {/*add the number to the vector*/
				nums_.push_back(temp);
			}
			if (nums_.size() >= max_length) {/*check if the vector size is out of range*/
				std::cerr << "���鳤�ȳ���" << max_length << ", ����������!" << std::endl;
				iss.clear();
				iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return false;
			}
		}

		if (nums_.size() < min_length) {/*check if the vector size is less than the minimum length*/
			std::cerr << "����Ԫ�ظ�������" << min_length << "��,����������!" << std::endl;
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
	bool InputIndexDiffandValueDiff(int index_min_count, int value_max_count, int value_min_count) {
		std::cin >> indexDiff_ >> valueDiff_;
		if (indexDiff_ < index_min_count || indexDiff_ > nums_.size()) {/*check if the input is out of range*/
			std::cerr << "�����indexDiffֵ������Χ[" << index_min_count << "," << nums_.size() << "],����������!" << std::endl;
			return false;
		}
		if (valueDiff_ < index_min_count || valueDiff_ > value_max_count) {/*check if the input is out of range*/
			std::cerr << "�����valueDiffֵ������Χ[" << value_min_count << "," << value_max_count << "],����������!" << std::endl;
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
			for (int right = left + 1; right < nums_.size(); right++) {/*check all pairs of numbers*/
				if (std::fabs(left - right) <= indexDiff_ && std::fabs(nums_[left] - nums_[right]) <= valueDiff_) {
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
	std::cout << ">>> ����Ҫ��" << std::endl;
	std::cout << "    [1]����һ����������num��������indexDiff,valueDiff,����������" << std::endl;
	std::cout << "    [2]������������Ϊһ��������,��ͬ����֮���ÿո����" << std::endl;
	std::cout << "    [3]����Ԫ�ش�С��Χ[-10^9,10^9],���鳤�ȷ�Χ[1,10^5],indexDiff��Χ[0,nums.length],valueDiff��Χ[0,10^9]" << std::endl << std::endl;

	/*input the array and check if it is valid*/
	do {
		std::cout << ">>> ��һ������,������һ����������:";
	} while (!nums.InputNumbers(1000000000, -1000000000, 100000, 1));
	do {
		std::cout << ">>> �ڶ�������,������indexDiff��valueDiff��ֵ:";
	} while (!nums.InputIndexDiffandValueDiff(1, 1000000000, 0));

	/*output the result*/
	std::cout << "�������Ƿ�������������Ԫ��:" << (nums.CheckSpecificNums() ? "true" : "false") << std::endl;

	return 0;
}