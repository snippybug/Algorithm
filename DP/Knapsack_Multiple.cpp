/*
 * 多重背包问题
 * 在完全背包的基础上，限制物品i的数量为Mi
 *
 * 参考《背包九讲V2》
 * 
 * Author:	Wang Zonglei
 * Date:	2015.7.9
 *
 */

#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

int cloneItems(const int *W, const int *C, const int* M, int **rW, int **rC, const int N, const int V);

inline int max(int a, int b){
	return a > b ? a : b;
}

struct Item{
	int weight;
	int value;
	Item(int w, int v) :weight(w), value(v){}
};

// 基本思路仍是先转化成01背包问题，再用动态规划求解
int main(){
	int N = 5;		// 物品数
	int V = 8;		// 背包容量
	int *W;			// 物品重量
	W = new int[N];
	W[0] = 1;
	W[1] = 3;
	W[2] = 5;
	W[3] = 3;
	W[4] = 2;
	int *C;			// 物品价值
	C = new int[N];
	C[0] = 3;
	C[1] = 2;
	C[2] = 1;
	C[3] = 5;
	C[4] = 3;
	int *M;			// 物品个数
	M = new int[N];
	M[0] = 3;
	M[1] = 2;
	M[2] = 2;
	M[3] = 1;
	M[4] = 2;

	int *W1, *C1;
	int N1;
	N1 = cloneItems(W, C, M, &W1, &C1, N, V);
	delete W;
	W = NULL;
	delete C;
	C = NULL;

	int *F;		// 状态数组
	F = new int[V + 1];

	// 初始化数组
	for (int i = 0; i <= V; i++){
		F[i] = 0;
	}

	int row = 0;
	while (row < N1){
		for (int j = V; j >= W1[row]; j--){				// 必须为逆序，因为计算依靠左上的状态
			F[j] = max(F[j], F[j - W1[row]] + C1[row]);
		}
		++row;
	}

	cout << F[V] << '\n';

	delete F;
	delete M;
	delete C1;
	delete W1;

	return 0;
}

// 与完全背包问题相同，考虑将第i种物品换成若干种物品，使得原问题中第i种物品可取的每种策略——取0..Mi件——都可以用新的方案代替
// 而且，大于Mi的物品数决不能出现
int cloneItems(const int *W, const int *C, const int *M, int **rW, int **rC, const int N, const int V){
	vector<Item> items;
	for (int i = 0; i < N; i++){
		int n = 0;					// 复制的个数n满足Mi-2^n+1>=0
		int upper;
		if ((M[i] * W[i]) > V){			// 总容量超过背包容量时，与完全背包问题等价
			upper = V;
		}
		else{
			upper = M[i] + 1;
		}
		while ((1 << n) < upper){
			++n;
		}
		if (n>0){					
			--n;					// 求上限
		}
		else{						// 如果n==0，说明M[i]=0，不允许放入物品
			continue;
		}
		int j = 0;
		while (j < n){
			items.push_back(Item(W[i] << j, C[i] << j));
			j++;
		}
		int temp;
		temp = upper - (1 << n);
		assert(temp>0);
		items.push_back(Item(W[i] * temp, C[i] * temp));
	}
	int nRem = items.size();
	int *tW, *tC;
	tW = new int[nRem];
	tC = new int[nRem];
	for (int i = 0; i < nRem; i++){
		tW[i] = items[i].weight;
		tC[i] = items[i].value;
	}
	*rW = tW;
	*rC = tC;
	return nRem;
}