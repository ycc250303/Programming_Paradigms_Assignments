#include <iostream>

/* 1.�ð汾ʵ����ȷ
 * 2.�ص�:�ݹ�ʵ�֣��߼��������������
 *   ��Ҫ�ŵ�:����ʵ�����Ķ�
 *	 ���ó���:������С��ģFibonacci������Ŀ��ٽ��
 * 3.û�в��˽���﷨���㷨ϸ��
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

/* 1.�ð汾ʵ����ȷ
 * 2.�ص�:����ʵ�֣��߼�������ʱ�临�Ӷȸ���
 *   ��Ҫ�ŵ�:����ʵ�����Ķ���Ч�ʸ���
 *	 ���ó���:�����ڽϴ��ģFibonacci������Ŀ��ٽ��
 * 3.û�в��˽���﷨���㷨ϸ��
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
 * 1.�ð汾ʵ����ȷ
 * 2.�ص�:��̬�滮ʵ�֣��߼�������ʱ�临�Ӷȸ���
 *   ��Ҫ�ŵ�:����ʵ�����Ķ���Ч�ʸ���
 *	 ���ó���:�����ڽϴ��ģFibonacci������Ŀ��ٽ��
 * 3.û�в��˽���﷨���㷨ϸ��
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
 * 1.�ð汾ʵ����ȷ
 * 2.�ص�:����˷�ʵ�֣�ʱ�临�Ӷȸ���
 *   ��Ҫ�ŵ�:����ʵ�����Ķ���Ч�ʸ���
 *	 ���ó���:�����ڴ��ģFibonacci������Ŀ��ٽ��
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
 *  1.�ð汾ʵ����ȷ
 *	2.�ص�:���������ʵ�֣��߼�������ʱ�临�Ӷȸ���
 *	  ��Ҫ�ŵ�:����ʵ�����Ķ���Ч�ʸ���
 *	  ���ó���:�����ڴ��ģFibonacci������Ŀ��ٽ��
 *  3.����Ϥ���﷨��:array���ʹ�ã�λ����(�룬����������ƣ�
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
 *  1.�ð汾ʵ����ȷ
 *  2.�ص�:���仯����ʵ�֣��߼�������ʱ�临�Ӷȸ���
 *    ��Ҫ�ŵ�:����ʵ�����Ķ���Ч�ʸ��ߣ��������ظ�����
 *    ���ó���:�ʺ��ڼ���ϴ�n��Fibonacci������������Ҫ��μ���Fibonacci���ĳ�����
 *  3.����Ϥ���﷨��:unordered_map���ʹ��
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
 * 1.�ð汾ʵ����ȷ
 * 2.�ص�:��������Ч���룬��ȫ�Ը���
 *   ��Ҫ�ŵ�:����Ч������Ч�����룬����˳���Ľ�׳��
 *	 ���ó���:�ʺ�����Ҫ��ȫ������Ч��������
 * 3.����Ϥ���﷨��:optional���ʹ��
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
 *  1.�ð汾ʵ����ȷ
 *  2.�ص�:constexprʵ�֣��߼�������ʱ�临�Ӷȸ���
 *    ��Ҫ�ŵ�:����ʵ�����Ķ���Ч�ʸ���
 *    ���ó���:�ʺ�����Ҫ�����ڳ��������������ģ���̡�������ʼֵ�ȳ�����
 *  3.����Ϥ���﷨��:constexpr��ʹ��
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
 * 1.�ð汾ʵ����ȷ
 * 2.�ص�:���м���ʵ�֣��߼�������ʱ�临�Ӷȸ���
 *   ��Ҫ�ŵ�:����ʵ�����Ķ���Ч�ʸ���
 *	 ���ó���:�ʺ�����Ҫ���м�����������߼���Ч��
 * 3.����Ϥ���﷨��:async���ʹ��
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
 * 1.�ð汾ʵ����ȷ
 * 2.�ص�:ʹ����Boost�Ĵ������� 
 *   ��Ҫ�ŵ�:cpp_int�����������С����������ʹ�ó�����Լ�������Fibonacci�����������
 *	 ���ó���:�ʺϼ���ǳ����Fibonacci��
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
 * 1.�ð汾ʵ����ȷ
 * 2.�ص�:ģ��ݹ�ʵ�֣�ʹ��ƫ�ػ�����������
 *   ��Ҫ�ŵ�:�ܹ��ڱ����ڼ������������������ʱ������ʹ��std::enable_if_t ȷ��ģ����� N Ϊ�Ǹ���
 *	 ���ó���:�ʺ��ڱ���ʱ�ھ�Ҫȷ��Fibonacci ��ֵ����������糣�����ʽ
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