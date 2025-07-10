#include <iostream>
#include <sstream>
#include <vector>

#define CALCULATE_ERROR -1

/*create the Matrix class*/
class Matrix {
private:
	std::vector<std::vector<float>> data;
public:

	Matrix();
	Matrix(float array[16]);
	Matrix operator + (Matrix otherMatrix);
	Matrix operator += (Matrix otherMatrix);
	Matrix operator * (Matrix otherMatrix);
	float operator()(int row, int column);
	float operator()(int row, int column) const;
	friend std::ostream &operator <<(std::ostream& out, const Matrix &matrix);
};


/*
 * Function name		:Matrix
 * Function				:Matrix constructor
 * Input parameters		:void
 * Return value			:void
 */
Matrix::Matrix() : data(4, std::vector<float>(4, 0.0f)) {
	//std::cout << "Please input the num of the float matrix" << std::endl;
	//for (int row = 0; row < 4; row++) {
	//	for (int col = 0; col < 4; col++) {
	//		while (true) {
	//	//std::cout << "Please the num of matrix[" << row + 1 << "][" << col + 1 << "]:";
	//			std::cin >> data[row][col];
	//			if (std::cin.fail()) {
	//				std::cerr << "Input error,please try again!" << std::endl;
	//				std::cin.clear();
	//				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//			}
	//			else
	//				break;
	//		}
	//	}
	//}
}

/*
 * Function name		:Matrix
 * Function				:Matrix constructor
 * Input parameters		:float array[16]
 * Return value			:void
 */
Matrix::Matrix(float array[16]) :data(4, std::vector<float>(4, 0.0f)) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			data[row][col] = array[row * 4 + col];
		}
	}
}

/*
 * Function name		:operator+
 * Function				:Matrix addition operator
 * Input parameters		:Matrix otherMatrix
 * Return value			:Matrix
 */
Matrix Matrix::operator+(Matrix otherMatrix) {
	Matrix copyMatrix;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			copyMatrix.data[row][col] = 0;
		}
	}
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			copyMatrix.data[row][col] = data[row][col] + otherMatrix.data[row][col];
		}
	}
	return copyMatrix;
}

/*
 * Function name		:operator+=
 * Function				:Matrix addition and assignment operator
 * Input parameters		:Matrix otherMatrix
 * Return value			:Matrix
 */
Matrix Matrix::operator+=(Matrix otherMatrix) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			data[row][col] += otherMatrix.data[row][col];
		}
	}
	return *this;
}

/*
 * Function name		:operator*
 * Function				:Matrix multiplication operator
 * Input parameters		:Matrix otherMatrix
 * Return value			:Matrix
 */
Matrix Matrix::operator*(Matrix otherMatrix) {
	Matrix copyMatrix;

	if (data[0].size() != otherMatrix.data.size()) {
		std::cerr << "Error: matrix size not match!" << std::endl;
		exit(CALCULATE_ERROR);
	}
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			copyMatrix.data[row][col] = 0;
		}
	}
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			for (int count = 0; count < 4; count++) {
				copyMatrix.data[row][col] += data[row][count]* otherMatrix.data[count][col];
			}
		}
	}
	return copyMatrix;
}

/*
 * Function name		:operator()
 * Function				:Matrix element access operator
 * Input parameters		:int row, int column
 * Return value			:float
 */
float Matrix::operator()(int row, int column) {
	return this->data[row][column];
}

/*
 * Function name		:operator()
 * Function				:Matrix element access operator
 * Input parameters		:int row, int column
 * Return value			:float const
 */
float Matrix::operator()(int row, int column) const{
	return this->data[row][column];
}


/*
 * Function name		:operator<<
 * Function				:Matrix output operator
 * Input parameters		:std::ostream& out, const Matrix& matrix
 * Return value			:std::ostream&	
 */
std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
	std::cout << "Matrix = ";
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			if (row == 0 && col == 0)
				std::cout << "[";
			else if (col == 0)
				std::cout << "          ";
			std::cout << matrix.data[row][col];
			if (col != 3)
				std::cout << ",";
			if (row == 3 && col == 3)
				std::cout << "]";
		}
		std::cout << std::endl;
		
	}
	return out;
}

int main() {
	// 测试用例：初始化矩阵并验证
	float array1[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
	Matrix matrix1(array1);

	if (matrix1(0, 0) != 1.0f) {
		std::cerr << "矩阵元素访问测试失败!" << std::endl;
	}

	// 验证加法运算
	float array2[] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	Matrix matrix2(array2);
	Matrix resultAdd = matrix1 + matrix2;

	// 验证结果
	bool addResult = true;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (resultAdd(i, j) != (matrix1(i, j) + matrix2(i, j))) {
				addResult = false;
			}
		}
	}
	if (!addResult) {
		std::cerr << "加法运算测试失败!" << std::endl;
	}

	// 测试累加运算符
	matrix1 += matrix2;
	bool addAssignResult = true;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (matrix1(i, j) != (array1[4 * i + j] + 1)) { // 应该是每个元素加1
				addAssignResult = false;
			}
		}
	}
	if (!addAssignResult) {
		std::cerr << "累加运算符测试失败!" << std::endl;
	}

	// 测试乘法运算
	Matrix resultMul = matrix1 * matrix1; // 自乘
	// 验证相乘的结果
	bool mulResult = true;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			float expectedValue = 0.0f;
			for (int k = 0; k < 4; ++k) {
				expectedValue += matrix1(i, k) * matrix1(k, j);
			}
			if (resultMul(i, j) != expectedValue) {
				mulResult = false;
			}
		}
	}
	if (!mulResult) {
		std::cerr << "乘法运算测试失败!" << std::endl;
	}

	// 边界用例：测试空矩阵相加（初始化为全0）
	float arrayZero[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	Matrix matrixZero(arrayZero);
	Matrix resultZeroAdd = matrixZero + matrixZero;

	// 验证结果
	bool zeroAddResult = true;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (resultZeroAdd(i, j) != 0.0f) {
				zeroAddResult = false;
			}
		}
	}
	if (!zeroAddResult) {
		std::cerr << "空矩阵相加测试失败!" << std::endl;
	}

	std::cout<<matrix1<<std::endl;
	


	// 打印测试成功信息
	std::cout << "所有测试用例通过！" << std::endl;
	return 0;
}