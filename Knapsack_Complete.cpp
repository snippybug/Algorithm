/*
 * 放宽条件：每种物品有无限件可以用
 * Author:	Wang Zonglei
 * Date:	2015.7.9
 * 
 */

// 两个步骤
// 1. 对于满足Ci<=Cj而Wi>=Wj的物品i，j，可以直接去掉j
// 2. 把第i件物品拆成费用为Ci*2^k、价值为Wi*2^k的若干件物品，其中k取遍Ci*2^k<=V的非负数
// 之所以可以这么做，是因为无论第i件物品取多少件，都可以用若干个2^k表示(比如取3件，3=2^0+2^1)

#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

int selectItems(const int *W, const int *C, int **rW, int **rC, const int N);
int cloneItems(const int *W, const int *C, int **rW, int **rC, const int N, const int V);

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

	int *W1, *C1;
	int N1;
	N1=selectItems(W, C, &W1, &C1, N);		// 步骤1
	delete C;
	delete W;
	C = NULL;
	W = NULL;
	
	int *W2, *C2;
	int N2;

	N2 = cloneItems(W1, C1, &W2, &C2, N1, V);	// 步骤2
	delete C1;
	delete W1;
	C1 = NULL;
	W1 = NULL;
	// 现在已将完全背包问题转化为01背包问题，用动态规划即可求解

	int *F;		// 状态数组
	F = new int[V + 1];

	// 初始化数组
	for (int i = 0; i <= V; i++){
		F[i] = 0;
	}

	int row = 0;
	while (row < N2){
		for (int j = V; j >= 0; j--){				// 必须为逆序，因为计算依靠左上的状态
			int value;
			// 对于不同重量的背包，考虑是否放入物品i
			// 如果不能放入，则F[row][j]=F[row-1][j]
			if (j < W2[row]){
				value = F[j];
			}
			else{		// 能放入时，取放入和不放入的较大值
				value = max(F[j], F[j - W2[row]] + C2[row]);
			}
			F[j] = value;
		}
		++row;
	}

	cout << F[V] << '\n';


	delete C2;
	delete W2;
	delete F;
	return 0;
}

struct Item{
	int weight;
	int value;
	Item(int w, int v) :weight(w), value(v){}
	friend bool operator > (const Item&, const Item&);
};

bool operator>(const Item& i1, const Item& i2){
	return i1.weight > i2.weight;
}

// 从已有的物品数中筛出满足Wi<=Wj，Ci>=Cj的物品j
// 函数会为新数组分配内存，将指针存在rW和rC中，要求调用者释放
// 返回剩余的物品数
int selectItems(const int *W, const int *C, int **rW, int **rC, const int N){
	assert(rW && rC);
	priority_queue<Item, vector<Item>, greater<Item>> queue;		// 将所有物品按升序排列
	for (int i = 0; i < N; i++){
		queue.push(Item(W[i], C[i]));
	}
	vector<Item> items;
	while (queue.empty()==false){			// 将priority_queue转化为vector(有没有直接的方法？)
		items.push_back(queue.top());
		queue.pop();
	}
	vector<Item>::iterator it = items.begin();
	while (it != items.end() - 1){			// 对于每一个物品，它的价值都应该比它小的物品大，否则就要被删除
		vector<Item>::iterator jt = it + 1;
		while (jt != items.end()){
			if (it->value >= jt->value){
				jt = items.erase(jt);
			}
			else{
				++jt;
			}
		}
		it++;
	}
	int *tW, *tC;
	int nRem = items.size();
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

// 将每一个物品复制为费用Ci*2^k、价值为Wi*2^k的若干件物品
// 函数不负责释放为rW和rC分配的内存
// 返回物品数
int cloneItems(const int *W, const int *C, int **rW, int **rC, const int N, const int V){
	vector<Item> items;
	for (int i = 0; i < N; i++){
		int n = 0;					// 复制的个数
		while ((W[i] << n) <= V){
			++n;
		}
		for (int j = 0; j < n; j++){
			items.push_back(Item(W[i] << j, C[i] << j));
		}
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
