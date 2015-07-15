/*
 * Description:	Give a tree with n vertices,each edge has a length(positive integer less than 1001). 
 *				Define dist(u,v)=The min distance between node u and v. 
 *				Give an integer k,for every pair (u,v) of vertices is called valid if and only if dist(u,v) not exceed k. 
 *				Write a program that will count how many pairs which are valid for a given tree. 
 *
 * Input:	The input contains several test cases. The first line of each test case contains two integers n, k. (n<=10000) The following n-1 lines each *
 *			contains three integers u,v,l, which means there is an edge between node u and v of length l. The last test case is followed by two zeros. 
 *
 * Output:	For each test case output the answer on a single line. 
 *
 * Author:	Wang Zonglei
 * Date:	2015.7.14
 *
 */

#include <vector>

using namespace std;

struct Edge{
	int to;
	int len;
	Edge(const int _t, const int _l) :to(_t), len(_l){}
};

vector<Edge> E[2000];	// 边表，用来表示树
int N = 6;		// 结点数
int K = 3;		// 有效距离

int r_dfs_cbsize(int *, const int, const int parent=-1);
int r_dfs_rtsizeM(int *, int *, const int, const int, const int parent=-1);

void addEdge(const int a, const int b, const int l){
	E[a].push_back(Edge(b, l));
	E[b].push_back(Edge(a, l));
}

int getCenter();

int main(){

	addEdge(0, 1, 2);
	addEdge(0, 2, 4);
	addEdge(0, 3, 3);
	addEdge(1, 5, 1);
	addEdge(2, 4, 2);

	int **distance;		// 所有结点间的距离
	distance = new int*[N];
	for (int i = 0; i < N; i++){
		distance[i] = new int[N];
	}

	int center = getCenter();
	printf("center=%d\n", center);

	for (int i = 0; i < N; i++){
		delete distance[i];
	}
	delete distance;
	return 0;
}

// 函数使用动态规划返回树的中心(子树结点个数最大值最小的根)
// 分三步：
// 1. 使用DFS找到以0(或任意结点)为根的所有子树的大小，存于cdsize中
// 2. 使用DFS找到以任意结点为根的树的子树最大值，存于rtsize
// 3. 在rtsize中寻找最小值
// Global: N
int getCenter(){
	int *cbsize;
	cbsize = new int[N];
	int *rtsizeM;
	rtsizeM = new int[N];

	r_dfs_cbsize(cbsize, 0);		// 默认以0为根
	r_dfs_rtsizeM(rtsizeM, cbsize, 0, 0);		// 之前以0为根
	int min = rtsizeM[0];
	int index = 0;
	for (int i = 0; i < N; i++){
		if (rtsizeM[i] < min){
			min = rtsizeM[i];
			index = i;
		}
	}
	delete rtsizeM;
	delete cbsize;
	return index;
}

// 计算以node为根的子树大小(结点个数)，存在cbsize中，并返回
// Notice：如果是叶结点，size+=...不会执行，直接返回size(0)
// Global：E
int r_dfs_cbsize(int *cbsize, const int node, const int parent){
	int size = 1;		// 结点自身也要计数
	for (vector<Edge>::iterator it = E[node].begin(); it != E[node].end(); it++){
		if (it->to != parent){
			size += r_dfs_cbsize(cbsize, it->to, node);
		}
	}
	cbsize[node] = size;
	return size;
}

// 计算以node为根的树的子树的最大值
// Global: E
int r_dfs_rtsizeM(int *rtsizeM, int *cbsize, const int node, const int oldroot, const int parent){
	int max = -1;
	for (vector<Edge>::iterator it = E[node].begin(); it != E[node].end(); it++){
		int size;
		if (it->to == parent){
			size = cbsize[oldroot] - cbsize[node];
		}
		else{
			size = cbsize[it->to];
			r_dfs_rtsizeM(rtsizeM, cbsize, it->to, oldroot, node);		// 只是顺便
		}
		if (size > max){
			max = size;
		}
	}
	rtsizeM[node] = max;
	return 0;
}