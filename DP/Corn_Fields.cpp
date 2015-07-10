/*
* Description:	Farmer John has purchased a lush new rectangular pasture composed of M by N (1 ≤ M ≤ 12; 1 ≤ N ≤ 12) square parcels. He wants to grow 
*				some yummy corn for the cows on a number of squares. Regrettably, some of the squares are infertile and can't be planted. Canny FJ knows that the cows 
*				dislike eating close to each other, so when choosing which squares to plant, he avoids choosing squares that are adjacent; no two chosen squares 
*				share an edge. He has not yet made the final choice as to which squares to plant. Being a very open-minded man, Farmer John wants to consider all 
*				possible options for how to choose the squares for planting. He is so open-minded that he considers choosing no squares as a valid option!
*				Please help Farmer John determine the number of ways he can choose the squares to plant.
*
* Input:	Line 1: Two space-separated integers: M and N
*			Lines 2.. M+1: Line i+1 describes row i of the pasture with N space-separated integers indicating whether a square is fertile (1 for fertile, 0 for infertile) 
* Output:	Line 1: One integer: the number of ways that FJ can choose the squares modulo 100,000,000. 
* Author:	Wang Zonglei
* Date:	2015.7.7
*
*/

#include <cstdio>
#include <cmath>
#include <cassert>

using namespace std;

bool judge(const int status, const int n);

// 用动态规划求解
// 递推方程为：dp[i][status] = sigma { dp[i-1][和status不冲突的i-1行的状态] }
int main(){
	int M;			// 牧场的行数
	int N;			// 牧场的列数
	scanf("%d%d", &M, &N);
	int *mask;			// 每一行形成一个掩码，0代表可用，1代表不可用
	mask = new int[M];
	// 读入掩码
	for (int i = 0; i < M; i++){
		mask[i] = 0;
		int k;
		for (int j = 0; j < N; j++){
			mask[i] <<= 1;
			scanf("%d", &k);
			if (k == 1){
				mask[i] |= 1;
			}
		}
	}
	int **dp;			// dp[i][status]表示第1行放status状态的牛的方法数
	dp = new int*[M];
	int nstatus = 1 << N;		// 总的状态数
	for (int i = 0; i < M; i++){
		dp[i] = new int[nstatus];
	}
	// 设置边界条件
	dp[0][0] = 1;
	for (int i = 1; i < nstatus; i++){		// assert(nstatus>=2)
		if (judge(i, N)==false			// 判断i是否有两个相邻的1
			&& (i&mask[0]) == i){
			dp[0][i] = 1;
		}
		else{
			dp[0][i] = 0;
		}
	}

	int row = 1;
	while (row < M){
		// 初始化
		for (int j = 0; j < nstatus; j++){
			dp[row][j] = 0;
		}

		// status=0时，任何状态都兼容
		for (int j = 0; j < nstatus; j++){
				dp[row][0] += dp[row - 1][j];
		}
		// status!=0时，需要考虑上一行的状态
		for (int j = 1; j < nstatus; j++){
			if (judge(j, N) == true
				|| (j&mask[row]) != j){		// 如果该状态有两个相邻的1或者与牧场不兼容，直接为0
				dp[row][j] = 0;
			}
			else{							// 否则，计算上一行与之不冲突的状态的方法数之和
				for (int k = 0; k < nstatus; k++){
					if ((j & k) == 0){
						dp[row][j] += dp[row - 1][k];
					}
				}
			}
		}
		row++;
	}

	// 最终的结果是最后一行的方法数之和
	int result = 0;
	for (int i = 0; i < nstatus; i++){
		result += dp[M - 1][i];
	}
	printf("%d\n", result);

	for (int i = 0; i < M; i++){
		delete dp[i];
	}
	delete dp;
	delete mask;
	return 0;
}

// 判断status的低n位是否有两个连续的1
// 有则返回true，否则返回false
bool judge(const int status, const int n){
	assert(n < 32);
	assert(n > 0);
	for (int i = 0; i < n - 1; i++){
		int a = status >> i & 1;
		int b = status >> (i + 1) & 1;
		if ((a&b) == 1){
			return true;
		}
	}
	return false;
}