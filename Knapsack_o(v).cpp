/*
* 将背包问题的空间复杂度由O(VN)降至O(V)
* Author:	Wang Zonglei
* Date:	2015.7.8
*
*/

#include <iostream>

using namespace std;

inline int max(int a, int b){
	return a > b ? a : b;
}

// 优化的原理是：递推方程只用到了上一行的状态，因此可以只用数组而不用矩阵来保存状态

int main(){
	int N = 5;		// 物品数
	int V = 8;		// 背包容量
	int *W;			// 物品重量
	W = new int[N + 1];
	W[0] = 0;		// 为了方便访问，物品i的重量就是W[i],i>=1
	W[1] = 1;
	W[2] = 3;
	W[3] = 5;
	W[4] = 3;
	W[5] = 2;
	int *C;			// 物品价值
	C = new int[N + 1];
	C[0] = 0;		// 为了方便访问，物品i的价值就是W[i],i>=1
	C[1] = 3;
	C[2] = 2;
	C[3] = 1;
	C[4] = 5;
	C[5] = 3;

	int *F;		// 状态数组
	F = new int [V + 1];

	// 初始化数组
	for (int i = 0; i <= V; i++){
		F[i] = 0;
	}

	int row = 1;
	while (row <= N){
		for (int j = V; j >= 0;j--){				// 必须为逆序，因为依靠的左上的状态
			int value;
			// 对于不同重量的背包，考虑是否放入物品i
			// 如果不能放入，则F[row][j]=F[row-1][j]
			if (j < W[row]){
				value = F[j];
			}
			else{		// 能放入时，取放入和不放入的较大值
				value = max(F[j], F[j - W[row]] + C[row]);
			}
			F[j] = value;
		}
		++row;
	}

	cout << F[V] << '\n';

	delete F;
	delete C;
	delete W;
	return 0;
}