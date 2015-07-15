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
 * Date:	2015.7.14, 7.15
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
int N = 7;		// 结点数
int K = 5;		// 有效距离
bool *scaned;	// scaned[i]==true表示结点i已被扫描，相当于已从树中删除

int r_dfs_cbsize(int *, const int, const int parent=-1);
int r_dfs_rtsizeM(int *, int *, const int, const int, const int parent=-1);

void addEdge(const int a, const int b, const int l){
	E[a].push_back(Edge(b, l));
	E[b].push_back(Edge(a, l));
}

int r_countPairs(const int node, const int offset = 0);
int r_calcDistance(const int node, int *distance, int accum, const int parent = -1);
int findCenter(const int node);

int main(){

	addEdge(0, 1, 2);
	addEdge(0, 2, 4);
	addEdge(0, 3, 3);
	addEdge(1, 5, 1);
	addEdge(2, 4, 2);
	addEdge(5, 6, 1);

	scaned = new bool[N];
	for (int i = 0; i < N; i++){
		scaned[i] = false;
	}

	int num = r_countPairs(0);		// 默认从结点0开始,offset==0
	printf("num=%d\n", num);
	
	delete scaned;
	return 0;
}

// 函数返回以node为根的子树的有效点对数	
// 首先寻找子树的中心，计算所有点到中心的距离
// 算出距离小于K的点对数后，再减去各子树里面小于k的点对数
// 然后对它的子树进行下一步操作
// Global: E, N, scaned
int r_countPairs(const int node, const int offset){
	int center = findCenter(node);		//	子树的中心
	scaned[center] = true;
	int *distance;						//	子树内其他结点到中心的距离
	distance = new int[N];
	for (int i = 0; i < N; i++){
		distance[i] = -1;
	}
	distance[center] = 0;
	r_calcDistance(center, distance, 0);		// parent==-1
	int n = 0;
	for (int i = 0; i < N; i++){		// 统计有多少个-1
		if (distance[i] == -1){
			n++;
		}
	}
	int count = 0;
	if (n == N - 1){			// 说明只有一个结点
		goto end;
	}

	// 对distance进行选择排序
	for (int i = 0; i < N-1; i++){
		for (int j = i + 1; j < N; j++){
			if (distance[j]<distance[i]){
				int temp = distance[j];
				distance[j] = distance[i];
				distance[i] = temp;
			}
		}
	}
	// 补上偏移量
	for (int i = n; i < N; i++){
		distance[i] += offset;
	}

	// 统计所有符合要求的点对(<K)
	for (int i = n; i < N-1; i++){
		for (int j = i + 1; j < N; j++){
			if (distance[i] + distance[j] < K){
				++count;
			}
		}
	}
	// 这样统计的点对有三种情况
	// 中心到其他结点，孩子内结点(先到中心再回到孩子)，孩子间结点
	// 第二种情况非法，需要减去这部分点对数。
	for (vector<Edge>::iterator it = E[center].begin(); it != E[center].end(); it++){
		if (scaned[it->to] == false){
			count -= r_countPairs(it->to, it->len+offset);
		}
	}

	// 最后再加上孩子内部的点对数
	for (vector<Edge>::iterator it = E[center].begin(); it != E[center].end(); it++){
		if (scaned[it->to] == false){
			count += r_countPairs(it->to, offset);			// offset==0
		}
	}

end:
	if (offset != 0){			// 说明是父节点去重调用，需重置标志位
		scaned[center] = false;
	}
	
	delete distance;
	return count;
}

// 计算以node为中心的子树内，其他结点到中心的距离
// accum指当前结点到中心的距离
// 返回值无意义
int r_calcDistance(const int node, int *distance, int accum, const int parent){
	for (vector<Edge>::iterator it = E[node].begin(); it != E[node].end(); it++){
		if (it->to != parent&&scaned[it->to] == false){
			distance[it->to] = accum + it->len;
			r_calcDistance(it->to, distance, distance[it->to], node);
		}
	}
	return 0;
}

// 函数使用动态规划返回树的中心(子树结点个数最大值最小的根)
// 分三步：
// 1. 使用DFS找到以node(或任意结点)为根的所有子树的大小，存于cdsize中
// 2. 使用DFS找到以任意结点为根的树的子树最大值，存于rtsize
// 3. 在rtsize中寻找最小值
// Global: N
int findCenter(const int node){
	int *cbsize;
	cbsize = new int[N];		// 不需要对cbsize进行初始化，因为在r_dfs_rtsizeM中访问时，都是通过树的父子关系访问的
	int *rtsizeM;
	rtsizeM = new int[N];
	for (int i = 0; i < N; i++){
		rtsizeM[i] = INT_MAX;
	}
	r_dfs_cbsize(cbsize, node);			// parent==-1
	r_dfs_rtsizeM(rtsizeM, cbsize, node, node);		// parent==-1
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
// Global：E, scaned
int r_dfs_cbsize(int *cbsize, const int node, const int parent){
	int size = 1;		// 结点自身也要计数
	for (vector<Edge>::iterator it = E[node].begin(); it != E[node].end(); it++){
		if (scaned[it->to]==false && it->to != parent){
			size += r_dfs_cbsize(cbsize, it->to, node);
		}
	}
	cbsize[node] = size;
	return size;
}

// 计算以node为根的树的子树的最大值
// Global: E, scaned
int r_dfs_rtsizeM(int *rtsizeM, int *cbsize, const int node, const int oldroot, const int parent){
	int max = -1;
	for (vector<Edge>::iterator it = E[node].begin(); it != E[node].end(); it++){
		int size;
		if (scaned[it->to] == false){
			if (it->to == parent){
				size = cbsize[oldroot] - cbsize[node];
			}
			else{
				size = cbsize[it->to];
				r_dfs_rtsizeM(rtsizeM, cbsize, it->to, oldroot, node);		// 递归计算子结点的数值
			}
			if (size > max){
				max = size;
			}
		}
	}
	rtsizeM[node] = max;
	return 0;
}