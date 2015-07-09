/*
 * Description:	有N件物品和一个容量为V的背包。第i件物品的重量为w[i]，价值是c[i]。将哪些物品装入背包可使价值总和最大
 * Input:	第一行给定物品数和背包的容量，第二行给出物品的重量，第三行给出物品的价值
 * Output:	背包的总价值
 * Author:	Wang Zonglei
 * Date:	2015.7.8
 *
 */

#include <iostream>

using namespace std;

inline int max(int a, int b){
	return a > b ? a : b;
}

// 使用动态规划解决该问题
// 递推方程为F[i][v] = max{ F[i-1][v], F[i-1][v-wi]+c[i] };
// 其中F[i][w]表示前i个物品放在重量为v的背包内能得到的最大价值
int main(){
	int N = 5;		// 物品数
	int V = 8;		// 背包容量
	int *W;			// 物品重量
	W = new int[N+1];
	W[0] = 0;		// 为了方便访问，物品i的重量就是W[i],i>=1
	W[1] = 1;
	W[2] = 3;
	W[3] = 5;
	W[4] = 3;
	W[5] = 2;
	int *C;			// 物品价值
	C = new int[N+1];
	C[0] = 0;		// 为了方便访问，物品i的价值就是W[i],i>=1
	C[1] = 3;
	C[2] = 2;
	C[3] = 1;
	C[4] = 5;
	C[5] = 3;

	int **F;		// 状态矩阵
	F = new int*[N+1];
	for (int i = 0; i <= N; i++){
		F[i] = new int[V + 1];
	}

	// 初始化第一列
	for (int i = 0; i <= N; i++){
		F[i][0] = 0;			// 当背包重量为0时，无法放入任何物品
	}
	for (int i = 1; i <= V; i++){
		F[0][i] = 0;
	}
	
	int row = 1;
	while (row <= N){
		for (int j = 1; j <= V; j++){
			int value;
			// 对于不同重量的背包，考虑是否放入物品i
			// 如果不能放入，则F[row][j]=F[row-1][j]
			if (j < W[row]){
				value = F[row - 1][j];
			}
			else{		// 能放入时，取放入和不放入的较大值
				value = max(F[row - 1][j], F[row - 1][j - W[row]] + C[row]);
			}
			F[row][j] = value;
		}
		++row;
	}
	
	cout << F[N][V]<<'\n';

	for (int i = 0; i <= N; i++){
		delete F[i];
	}
	delete F;
	delete C;
	delete W;
	return 0;
}