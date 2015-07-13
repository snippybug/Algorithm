/*
 * Description:	This problem is based on an exercise of David Hilbert, who pedagogically suggested that one study the theory of 4n+1 numbers. Here, we do only a bit of that. 
 *				An H-number is a positive number which is one more than a multiple of four: 1, 5, 9, 13, 17, 21,... are the H-numbers. For this problem we pretend that 
 *				these are the only numbers. The H-numbers are closed under multiplication. As with regular integers, we partition the H-numbers into units, H-primes, 
 *				and H-composites. 1 is the only unit. An H-number h is H-prime if it is not the unit, and is the product of two H-numbers in only one way: 1 × h. The 
 *				rest of the numbers are H-composite. For examples, the first few H-composites are: 5 × 5 = 25, 5 × 9 = 45, 5 × 13 = 65, 9 × 9 = 81, 5 × 17 = 85. 
 *				Your task is to count the number of H-semi-primes. An H-semi-prime is an H-number which is the product of exactly two H-primes. The two H-primes may 
 *				be equal or different. In the example above, all five numbers are H-semi-primes. 125 = 5 × 5 × 5 is not an H-semi-prime, because it's the product 
 *				of three H-primes.
 *
 * Input:	Each line of input contains an H-number ≤ 1,000,001. The last line of input contains 0 and this line should not be processed. 
 *
 * Output:	For each inputted H-number h, print a line stating h and the number of H-semi-primes between 1 and h inclusive, separated by one space in the format shown 
 *			in the sample. 
 *
 * Author:	Wang Zonglei
 * Date:	2015.7.13
 *
 */

#include <vector>

using namespace std;

// 基本思路：筛法
// 普通筛法在遇到一个质数p时会将其倍数(p*i, i=2...)筛出，若此时i是质数，便得到了一个半质数
// 普通筛法有冗余的操作，例如12会被2和3同时标记，因此，可以规定任意合数只能被其最小的质因数筛出，例如12=2*2*3，会在
// 外层循环运行到6时，*2后筛出。这样得到的算法是一个线性的算法
int main(){
	int N;			// H数的上界
	N = 21;
	vector<int> prime;			// 质数表
	int count = 0;			// H半质数的个数(程序目标)
	int *state;				// state[i]=0说明i未被扫描，1说明是质数，2说明是合数

	state = new int[(N - 1) / 4 + 1];		// state[0]是冗余位，因为0*4+1=1是特殊数字

	// 初始化isP
	for (int i = 0; i <= (N - 1) / 4; i++){
		state[i] = 0;
	}

	for (int i = 1; i <= (N - 1) / 4; i++){
		int num = i * 4 + 1;		// 序号i对应的质数
		if (state[i] == 0){		// 发现质数
			state[i] = 1;
			prime.push_back(num);
			for (vector<int>::iterator it = prime.begin(); it != prime.end(); it++){
				// 如果乘积在给定范围内
				if (*it * num <= N){

				}
			}
		}
	}

	delete state;
	return 0;
}