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

vector<Edge> E[2000];	// �߱�������ʾ��
int N = 7;		// �����
int K = 5;		// ��Ч����
bool *scaned;	// scaned[i]==true��ʾ���i�ѱ�ɨ�裬�൱���Ѵ�����ɾ��

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

	int num = r_countPairs(0);		// Ĭ�ϴӽ��0��ʼ,offset==0
	printf("num=%d\n", num);
	
	delete scaned;
	return 0;
}

// ����������nodeΪ������������Ч�����	
// ����Ѱ�����������ģ��������е㵽���ĵľ���
// �������С��K�ĵ�������ټ�ȥ����������С��k�ĵ����
// Ȼ�����������������һ������
// Global: E, N, scaned
int r_countPairs(const int node, const int offset){
	int center = findCenter(node);		//	����������
	scaned[center] = true;
	int *distance;						//	������������㵽���ĵľ���
	distance = new int[N];
	for (int i = 0; i < N; i++){
		distance[i] = -1;
	}
	distance[center] = 0;
	r_calcDistance(center, distance, 0);		// parent==-1
	int n = 0;
	for (int i = 0; i < N; i++){		// ͳ���ж��ٸ�-1
		if (distance[i] == -1){
			n++;
		}
	}
	int count = 0;
	if (n == N - 1){			// ˵��ֻ��һ�����
		goto end;
	}

	// ��distance����ѡ������
	for (int i = 0; i < N-1; i++){
		for (int j = i + 1; j < N; j++){
			if (distance[j]<distance[i]){
				int temp = distance[j];
				distance[j] = distance[i];
				distance[i] = temp;
			}
		}
	}
	// ����ƫ����
	for (int i = n; i < N; i++){
		distance[i] += offset;
	}

	// ͳ�����з���Ҫ��ĵ��(<K)
	for (int i = n; i < N-1; i++){
		for (int j = i + 1; j < N; j++){
			if (distance[i] + distance[j] < K){
				++count;
			}
		}
	}
	// ����ͳ�Ƶĵ�����������
	// ���ĵ�������㣬�����ڽ��(�ȵ������ٻص�����)�����Ӽ���
	// �ڶ�������Ƿ�����Ҫ��ȥ�ⲿ�ֵ������
	for (vector<Edge>::iterator it = E[center].begin(); it != E[center].end(); it++){
		if (scaned[it->to] == false){
			count -= r_countPairs(it->to, it->len+offset);
		}
	}

	// ����ټ��Ϻ����ڲ��ĵ����
	for (vector<Edge>::iterator it = E[center].begin(); it != E[center].end(); it++){
		if (scaned[it->to] == false){
			count += r_countPairs(it->to, offset);			// offset==0
		}
	}

end:
	if (offset != 0){			// ˵���Ǹ��ڵ�ȥ�ص��ã������ñ�־λ
		scaned[center] = false;
	}
	
	delete distance;
	return count;
}

// ������nodeΪ���ĵ������ڣ�������㵽���ĵľ���
// accumָ��ǰ��㵽���ĵľ���
// ����ֵ������
int r_calcDistance(const int node, int *distance, int accum, const int parent){
	for (vector<Edge>::iterator it = E[node].begin(); it != E[node].end(); it++){
		if (it->to != parent&&scaned[it->to] == false){
			distance[it->to] = accum + it->len;
			r_calcDistance(it->to, distance, distance[it->to], node);
		}
	}
	return 0;
}

// ����ʹ�ö�̬�滮������������(�������������ֵ��С�ĸ�)
// ��������
// 1. ʹ��DFS�ҵ���node(��������)Ϊ�������������Ĵ�С������cdsize��
// 2. ʹ��DFS�ҵ���������Ϊ���������������ֵ������rtsize
// 3. ��rtsize��Ѱ����Сֵ
// Global: N
int findCenter(const int node){
	int *cbsize;
	cbsize = new int[N];		// ����Ҫ��cbsize���г�ʼ������Ϊ��r_dfs_rtsizeM�з���ʱ������ͨ�����ĸ��ӹ�ϵ���ʵ�
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


// ������nodeΪ����������С(������)������cbsize�У�������
// Notice�������Ҷ��㣬size+=...����ִ�У�ֱ�ӷ���size(0)
// Global��E, scaned
int r_dfs_cbsize(int *cbsize, const int node, const int parent){
	int size = 1;		// �������ҲҪ����
	for (vector<Edge>::iterator it = E[node].begin(); it != E[node].end(); it++){
		if (scaned[it->to]==false && it->to != parent){
			size += r_dfs_cbsize(cbsize, it->to, node);
		}
	}
	cbsize[node] = size;
	return size;
}

// ������nodeΪ�����������������ֵ
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
				r_dfs_rtsizeM(rtsizeM, cbsize, it->to, oldroot, node);		// �ݹ�����ӽ�����ֵ
			}
			if (size > max){
				max = size;
			}
		}
	}
	rtsizeM[node] = max;
	return 0;
}