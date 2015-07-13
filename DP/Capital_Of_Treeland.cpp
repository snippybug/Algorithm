/*
 * Description:	The country Treeland consists of n cities, some pairs of them are connected with unidirectional roads. Overall there are n - 1 roads in the country. 
 *				We know that if we don't take the direction of the roads into consideration, we can get from any city to any other one.
 *				The council of the elders has recently decided to choose the capital of Treeland. Of course it should be a city of this country. The council is supposed 
 *				to meet in the capital and regularly move from the capital to other cities (at this stage nobody is thinking about getting back to the capital from 
 *				these cities). For that reason if city a is chosen a capital, then all roads must be oriented so that if we move along them, we can get from city a 
 *				to any other city. For that some roads may have to be inversed.
 *				Help the elders to choose the capital so that they have to inverse the minimum number of roads in the country.
 *
 * Input:	The first input line contains integer n (2 ≤ n ≤ 2*10^5) — the number of cities in Treeland. Next n - 1 lines contain the descriptions of the roads, 
 *			one road per line. A road is described by a pair of integers si, ti (1 ≤ si, ti ≤ n; si ≠ ti) — the numbers of cities, connected by that road. 
 *			The i-th road is oriented from city si to city ti. You can consider cities in Treeland indexed from 1 to n.
 *
 * Output:	In the first line print the minimum number of roads to be inversed if the capital is chosen optimally. In the second line print all possible ways 
 *			to choose the capital — a sequence of indexes of cities in the increasing order.
 *
 * Author:	Wang Zonglei
 * Date:	2015.7.10
 *
 *
 */

#include <vector>

using namespace std;

struct Edge{
	int to;				// 相连的顶点
	bool pn;			// 为true表示正向边，false表示逆向边
	Edge(int _t, bool _pn) :to(_t), pn(_pn){}
};

// 用边表表示一棵树
vector<Edge> E[200005];		// E[i]表示顶点i的所有边，如果pn=true，则是出边，否则是入边

int recursive_count_rev(int, int **, int, int, int);

void addEdge(int u, int v){
	E[u].push_back(Edge(v, true));
	E[v].push_back(Edge(u, false));
}


// 算法基本思路是：设dp[x]表示以结点x为根的子树逆向边的条数，设最初选定的根为结点x0，用递归算出这棵树的dp[x]
// 对于每个顶点，以它为根的逆向边的条数等于dp[x0]+{x0到这个顶点的正向边数}-{x0到这个顶点的逆向边数}
// 原理是因为dp[x]与该顶点为根的逆向边有部分重叠
int main(){
	int N;		// 顶点数
	scanf("%d", &N);
	for (int i = 0; i < N-1; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(a, b);
	}

	int **pprevs;				// pprevs[x][0]表示起始点到x的正向边数，pprevs[x][1]表示起始点到x的逆向边数
	pprevs = new int*[N + 1];
	for (int i = 0; i <= N; i++){
		pprevs[i] = new int[2];
	}

	int *revs;			// revs[x]表示以结点revs为根的树的逆向边数
	revs = new int[N + 1];		// revs[0]冗余
	revs[0] = -1;
	revs[1] = recursive_count_rev(1, pprevs, 0, 0, -1);			// 结点1为初始根
	for (int i = 2; i <= N; i++){
		revs[i] = revs[1] + pprevs[i][0] - pprevs[i][1];
	}

	// 寻找逆向边最少的根
	int min = revs[1];
	for (int i = 2; i <= N; i++){
		if (min > revs[i]){
			min = revs[i];
		}
	}
	printf("%d\n", min);
	vector<int> vtmp;								// Stupid---
	for (int i = 1; i <= N; i++){
		if (revs[i] == min){
			vtmp.push_back(i);
		}
	}
	int i = 0;
	while (i < vtmp.size() - 1){
		printf("%d ", vtmp[i]);
		i++;
	}
	printf("%d", vtmp[i]);

	delete revs;
	for (int i = 0; i <= N; i++){
		delete pprevs[i];
	}
	delete pprevs;
	return 0;
}

// 每一个结点的逆向边数=到子结点的逆向边数+子结点的逆向边数
// num表示结点号, pprevs用于保存正逆边数，forward是根结点到num的正向边数，reverse是根节点到num的逆向边数
// parent代表父节点
int recursive_count_rev(int num, int **pprevs, int forward, int reverse, int parent){
	pprevs[num][0] = forward;
	pprevs[num][1] = reverse;

	if (E[num].size() == 1 && parent != -1){			// 只有叶节点才有1条边，根结点可能有1条边，但parent==-1
		return 0;
	}
	int accum = 0;

	for (vector<Edge>::iterator it = E[num].begin(); it != E[num].end(); it++){
		if (it->to == parent){			// 跳过父节点
			continue;
		}
		if (it->pn == false){
			accum++;
			accum += recursive_count_rev(it->to, pprevs, forward, 1 + reverse, num);
		}
		else{
			accum += recursive_count_rev(it->to, pprevs, forward + 1, reverse, num);
		}
		
	}
	return accum;
}