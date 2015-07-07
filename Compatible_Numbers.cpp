/*
 * Description:	Two integers x and y are compatible, if the result of their bitwise "AND" equals zero, that is, a&b = 0. For example, numbers 90(10110102) and 36(1001002) 
 *				are compatible, as 10110102&1001002 = 02, and numbers 3(112) and 6(1102) are not compatible, as 112&1102 = 102.
 *				You are given an array of integers a1, a2, ..., an. Your task is to find the following for each array element: is this element compatible 
 *				with some other element from the given array? If the answer to this question is positive, then you also should find any suitable element.
 * Input:	The first line contains an integer n (1 ≤ n ≤ 10^6) — the number of elements in the given array. 
 *			The second line contains n space-separated integers a1, a2, ..., an (1 ≤ ai ≤ 4·10^6) — the elements of the given array. The numbers in the array can coincide.
 * Output:	Print n integers ansi. If ai isn't compatible with any other element of the given array a1, a2, ..., an, then ansi should be equal to -1. 
 *			Otherwise ansi is any such number, that ai&ansi = 0, and also ansi occurs in the array a1, a2, ..., an.
 * Author:	Wang Zonglei
 * Date:	2015.7.7
 *
 *
 */

#include <cstdio>

using namespace std;

// 如果一个数是0000111001，设与它兼容的数为X，则X=????000??0
// X的反码为： ????111??1，也就是说，依次将原数的每个0变成1，就能得到所有和该数兼容的数
// 因此，建立一个数组dp[x]用来表示能和反码x兼容的数，如果不存在这样的数，dp[x]=0
int main(){
	int N;			// 数组大小
	scanf("%d", &N);
	int *A;
	A = new int[N];
	for (int i = 0; i < N; i++){
		scanf("%d", &A[i]);
	}

	const int mbits = 22;	// 最大的数是4*10^6，因此检查低22位就足够了
	int *dp;				// 状态数组
	dp = new int[1 << mbits];
	for (int i = 0; i < (1 << mbits); i++){
		dp[i] = 0;
	}
	// 首先放入初值
	for (int i = 0; i < N; i++){
		dp[A[i]] = A[i];			// 一个数一定和它的反码兼容
	}
	// 遍历数组dp，每一次只改变数的一个0
	for (int i = 0; i < mbits; i++){
		for (int j = 0; j < (1 << mbits); j++){
			if (dp[j] != 0 && (dp[j] & (1 << i)) == 0){
				dp[j | (1 << i)] = dp[j];
			}
		}
	}
	// 对数组的数取反，然后检查dp
	for (int i = 0; i < N; i++){
		int temp = (~A[i] & ((1 << mbits) - 1));
		if (dp[temp] == 0){
			printf("%d", -1);
		}
		else{
			printf("%d", dp[temp]);
		}
		if (i != N - 1){
			putchar(' ');
		}
	}

	delete dp;
	delete A;
	return 0;
}