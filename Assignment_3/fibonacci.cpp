#include <iostream>

/* 1.该版本实现正确
 * 2.特点:递归实现，逻辑清晰，易于理解
 *   主要优点:易于实现与阅读
 *	 适用场景:适用于小规模Fibonacci数计算的快速解决
 * 3.没有不了解的语法和算法细节
 */


 /*
  * @brief Computes the nth Fibonacci number using a recursive approach.
  *
  * This function uses recursion to calculate the Fibonacci number.
  * The time complexity is O(2^n), making it suitable for small-scale Fibonacci number calculations.
  *
  * @param n The index of the Fibonacci number to compute, where n >= 0.
  * @return The nth Fibonacci number.
  */
int fibonacci_recursive(int n) {
	if (n <= 1) return n;
	return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

/* 1.该版本实现正确
 * 2.特点:迭代实现，逻辑清晰，时间复杂度更低
 *   主要优点:易于实现与阅读，效率更高
 *	 适用场景:适用于较大规模Fibonacci数计算的快速解决
 * 3.没有不了解的语法和算法细节
 */

 /*
  * @brief Computes the nth Fibonacci number using an iterative approach.
  *
  * This function uses iteration to calculate the Fibonacci number.
  * The time complexity is O(n), making it efficient for larger Fibonacci number calculations.
  *
  * @param n The index of the Fibonacci number to compute, where n >= 0.
  * @return The nth Fibonacci number.
  */
int fibonacci_iterative(int n) {
	if (n <= 1) return n;
	int a = 0, b = 1, temp;
	for (int i = 2; i <= n; ++i) {
		temp = a + b;
		a = b;
		b = temp;
	}
	return b;
}

/*
 * 1.该版本实现正确
 * 2.特点:动态规划实现，逻辑清晰，时间复杂度更低
 *   主要优点:易于实现与阅读，效率更高
 *	 适用场景:适用于较大规模Fibonacci数计算的快速解决
 * 3.没有不了解的语法和算法细节
 */

 /*
  * @brief Computes the nth Fibonacci number using dynamic programming.
  *
  * This function uses dynamic programming to calculate the Fibonacci number.
  * The time complexity is O(n), making it suitable for larger Fibonacci number calculations.
  *
  * @param n The index of the Fibonacci number to compute, where n >= 0.
  * @return The nth Fibonacci number.
  */
#include<vector>
int fibonacci_dp(int n) {
	if (n <= 1) return n;
	std::vector<int> dp(n + 1, 0);
	dp[1] = 1;
	for (int i = 2; i <= n; ++i) {
		dp[i] = dp[i - 1] + dp[i - 2];
	}
	return dp[n];
}

/*
 * 1.该版本实现正确
 * 2.特点:矩阵乘法实现，时间复杂度更低
 *   主要优点:易于实现与阅读，效率更高
 *	 适用场景:适用于大规模Fibonacci数计算的快速解决
 */

 /*
  * @brief Computes the nth Fibonacci number using matrix multiplication.
  *
  * This function uses matrix multiplication to calculate the Fibonacci number.
  * The time complexity is O(log n) due to the matrix exponentiation method.
  *
  * @param n The index of the Fibonacci number to compute, where n >= 0.
  * @return The nth Fibonacci number.
  */
#include<array>
std::array<std::array<long long, 2>, 2> matrix_multiply(const std::array<std::array<long long, 2>, 2>& a,
	const std::array<std::array<long long, 2>, 2>& b) {
	std::array<std::array<long long, 2>, 2> result = { {0} };
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			for (int k = 0; k < 2; ++k)
				result[i][j] += a[i][k] * b[k][j];
	return result;
}

/*
 *  1.该版本实现正确
 *	2.特点:矩阵快速幂实现，逻辑清晰，时间复杂度更低
 *	  主要优点:易于实现与阅读，效率更高
 *	  适用场景:适用于大规模Fibonacci数计算的快速解决
 *  3.不熟悉的语法点:array库的使用，位运算(与，或，异或，左右移）
 */

 /*
  * @brief Computes the nth Fibonacci number using matrix exponentiation.
  *
  * This function uses matrix exponentiation to calculate the Fibonacci number.
  * The time complexity is O(log n), making it efficient for large Fibonacci number calculations.
  *
  * @param n The index of the Fibonacci number to compute, where n >= 0.
  * @return The nth Fibonacci number.
  */
long long fibonacci_matrix(int n) {
	if (n <= 1) return n;
	std::array<std::array<long long, 2>, 2> base = { { {1, 1}, {1, 0} } };
	std::array<std::array<long long, 2>, 2> result = { {{1, 0}, {0, 1} } };
	n--;
	while (n > 0) {
		if (n & 1) result = matrix_multiply(result, base);
		base = matrix_multiply(base, base);
		n >>= 1;
	}
	return result[0][0];
}



/*
 *  1.该版本实现正确
 *  2.特点:记忆化搜索实现，逻辑清晰，时间复杂度更低
 *    主要优点:易于实现与阅读，效率更高，减少了重复计算
 *    适用场景:适合于计算较大n的Fibonacci数，尤其在需要多次计算Fibonacci数的场景下
 *  3.不熟悉的语法点:unordered_map库的使用
 */

 /*
  * @brief Computes the nth Fibonacci number using memoization.
  *
  * This function uses memoization to reduce redundant calculations in the recursive approach.
  * The time complexity is O(n), making it suitable for calculating Fibonacci numbers with overlapping subproblems.
  *
  * @param n The index of the Fibonacci number to compute, where n >= 0.
  * @param memo A reference to a map used for storing previously computed Fibonacci numbers.
  * @return The nth Fibonacci number.
  */
#include <unordered_map>
long long fibonacci_memoization(int n, std::unordered_map<int, long long>& memo) {
	if (n <= 1) return n;
	if (memo.find(n) != memo.end()) return memo[n];
	memo[n] = fibonacci_memoization(n - 1, memo) + fibonacci_memoization(n - 2, memo);
	return memo[n];
}

/*
 * 1.该版本实现正确
 * 2.特点:处理了无效输入，安全性更高
 *   主要优点:能有效处理无效的输入，提高了程序的健壮性
 *	 适用场景:适合于需要安全处理无效输入的情况
 * 3.不熟悉的语法点:optional库的使用
 */

 /*
  * @brief Computes the nth Fibonacci number with input validation using std::optional.
  *
  * This function safely handles invalid inputs and only computes Fibonacci numbers for non-negative indices.
  * The time complexity is O(n) for valid inputs.
  *
  * @param n The index of the Fibonacci number to compute, can be negative for early exit.
  * @return A std::optional containing the nth Fibonacci number if n >= 0; otherwise, std::nullopt.
  */
#include <optional>
std::optional<long long> fibonacci_safe(int n) {
	if (n < 0) return std::nullopt;
	if (n <= 1) return n;
	long long a = 0, b = 1, temp;
	for (int i = 2; i <= n; ++i) {
		temp = a + b;
		a = b;
		b = temp;
	}
	return b;
}

/*
 *  1.该版本实现正确
 *  2.特点:constexpr实现，逻辑清晰，时间复杂度更低
 *    主要优点:易于实现与阅读，效率更高
 *    适用场景:适合于需要编译期常量的情况，例如模板编程、常量初始值等场景中
 *  3.不熟悉的语法点:constexpr的使用
 */

 /*
  * @brief Computes the nth Fibonacci number at compile time using constexpr.
  *
  * This function allows for compile-time evaluation of Fibonacci numbers.
  * Ideal for scenarios requiring compile-time constants.
  *
  * @param n The index of the Fibonacci number to compute, n >= 0.
  * @return The nth Fibonacci number, computed at compile time.
  */
constexpr long long fibonacci_constexpr(int n) {
	if (n <= 1) return n;
	long long a = 0, b = 1;
	for (int i = 2; i <= n; ++i) {
		long long temp = a + b;
		a = b;
		b = temp;
	}
	return b;
}

/*
 * 1.该版本实现正确
 * 2.特点:并行计算实现，逻辑清晰，时间复杂度更低
 *   主要优点:易于实现与阅读，效率更高
 *	 适用场景:适合于需要并行计算的情况，提高计算效率
 * 3.不熟悉的语法点:async库的使用
 */

 /*
  * @brief Computes the nth Fibonacci number concurrently using std::async.
  *
  * This function utilizes parallel computation to enhance efficiency.
  * It is well-suited for computing Fibonacci numbers in multithreaded environments.
  *
  * @param n The index of the Fibonacci number to compute, where n >= 0.
  * @return The nth Fibonacci number.
  */
#include <future>
long long fibonacci_parallel(int n) {
	if (n <= 1) return n;
	auto future = std::async(std::launch::async, fibonacci_parallel, n - 2);
	long long result = fibonacci_parallel(n - 1);
	return result + future.get();
}

/*
 * 1.该版本实现正确
 * 2.特点:使用了Boost的大整数库 
 *   主要优点:cpp_int允许处理任意大小的整数，这使得程序可以计算更大的Fibonacci数而不会溢出
 *	 适用场景:适合计算非常大的Fibonacci数
 */

 /*
  * @brief Computes the nth Fibonacci number using Boost multiprecision library.
  *
  * This function calculates Fibonacci numbers that may exceed standard integer limits,
  * utilizing the Boost library for big integer support.
  *
  * @param n The index of the Fibonacci number to compute, where n >= 0.
  * @return The nth Fibonacci number as a Boost multiprecision integer.
  */
#include <boost/multiprecision/cpp_int.hpp>
boost::multiprecision::cpp_int fibonacci_bigint(int n) {
	if (n <= 1) return n;
	boost::multiprecision::cpp_int a = 0, b = 1, temp;
	for (int i = 2; i <= n; ++i) {
		temp = a + b;
		a = b;
		b = temp;
	}
	return b;
}

/*
 * 1.该版本实现正确
 * 2.特点:模板递归实现，使用偏特化处理基本情况
 *   主要优点:能够在编译期间计算出结果，减少运行时开销，使用std::enable_if_t 确保模板参数 N 为非负数
 *	 适用场景:适合在编译时期就要确定Fibonacci 数值的情况，例如常量表达式
 */

 /*
  * @brief Computes the nth Fibonacci number at compile time using template specialization.
  *
  * This function calculates Fibonacci numbers at compile time using recursive template instantiation.
  * It ensures that N is a non-negative integer.
  *
  * @tparam N The index of the Fibonacci number to compute, must be non-negative.
  * @return The nth Fibonacci number, computed at compile time.
  */
template<int N, typename = std::enable_if_t<(N >= 0)>>
struct Fibonacci {
	static constexpr long long value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};
template<>
struct Fibonacci<0> {
	static constexpr long long value = 0;
};
template<>
struct Fibonacci<1> {
	static constexpr long long value = 1;
};

#include <boost/multiprecision/cpp_int.hpp>
boost::multiprecision::cpp_int my_fibonacci(int n) {
	if (n < 0)
		return 0;
	if (n <= 1)
		return n;
	boost::multiprecision::cpp_int a = 0, b = 1, temp;
	for (int i = 2; i <= n; ++i) {
		temp = a + b;
		a = b;
		b = temp;
	}
	return b;
}

constexpr std::optional<long long> my_fibonacci(int n, std::unordered_map<int, long long>& memo) {
	if (n < 0)return std::nullopt;
	if (n <= 1) return n;
	if (memo.find(n) != memo.end()) 
		return memo[n];
	memo[n] = my_fibonacci(n - 1, memo).value() + my_fibonacci(n - 2, memo).value();
	return memo[n];
}


int main() {
	return 0;
}