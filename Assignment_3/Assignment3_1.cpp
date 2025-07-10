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
	bool InputNumbers(T max_num_count,T min_num_count,unsigned int max_length,unsigned int min_length) {

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
				std::cerr << "�������������Χ["<<min_num_count<<','<< max_num_count <<"], ����������!" << std::endl;
				iss.clear();
				iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return false;
			}
			else {/*add the number to the vector*/
				nums_.push_back(temp);
			}
			if (nums_.size() >= max_length){/*check if the vector size is out of range*/
				std::cerr << "���鳤�ȳ���"<< max_length <<", ����������!" << std::endl;
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
	* Function Name:	checkSpecificNums
	* Function:			check if there are same numbers in the array
	* Input Parameters:	void
	* Return Value:		true: there are same numbers in the array
	*					false: there are no same numbers in the array
	*/
	bool CheckSpecificNums() {
		/*sort the numsCopy vector*/
		std::vector<T>nums_copy = nums_;
		std::sort(nums_copy.begin(), nums_copy.end());

		/*check if there are same numbers in the array*/
		for (int count = 0; count < nums_copy.size()-1; count++) {
			if (nums_copy[count] == nums_copy[count + 1])
				return true;
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
	std::cout << ">>> ����Ҫ��"<<std::endl;
	std::cout<<"    [1]����һ����������num"<<std::endl;
	std::cout<<"    [2]����Ϊһ��������,��ͬ����֮���ÿո����"<<std::endl;
	std::cout<<"    [3]����Ԫ�ش�С��Χ[-10^9,10^9],���鳤�ȷ�Χ[1,10^5]"<<std::endl<<std::endl;

	/*input the array and check if it is valid*/
	do {
		std::cout << ">>> ������һ����������:";
	} while (!nums.InputNumbers(1000000000, -1000000000, 100000, 1));

	/*output the result*/
	std::cout << "�������Ƿ�������������Ԫ��:"<<(nums.CheckSpecificNums()?"true":"false")<<std::endl;

	return 0;
}