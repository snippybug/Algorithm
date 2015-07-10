/*
 * 王宗磊，2015.6.8
 * Topic: Exercise 3.2 from <Algorithm Design>
 *
 * Problem: Give an algorithm to detect whether a given undirected graph contains a cycle. If the graph contains a cycle, then your algorithm should output one.
 *	(It should not output all cycles in the graph, just one of them.) The running time of your algorithm should be O(m+n) for a graph with n nodes and m edges
 *
 */

#include <iostream>
#include <queue>

using namespace std;

class Node{
public:
	Node(int);
	~Node();
	Node *next;
	int num;

};

Node::Node(int t){
	num = t;
	next = NULL;
}

Node::~Node(){

}

class Graph{
public:
	Graph(int n);
	void addEdge(int m, int n);
	void display();
	int hascycle();
	~Graph();
private:
	Node **nodelist;		// 邻接链表
	int total;
};

// n代表结点数
Graph::Graph(int n){
	nodelist = new Node*[n];
	int i;
	for (i = 0; i < n; i++){
		nodelist[i] = NULL;
	}
	total = n;
}

// 没有做边界检查，也没有判断重复性
void Graph::addEdge(int m, int n){
	Node *temp = nodelist[m];
	temp = new Node(n);
	temp->next = nodelist[m];
	nodelist[m] = temp;

	// 邻接链表需添加两次
	temp = nodelist[n];
	temp = new Node(m);
	temp->next = nodelist[n];
	nodelist[n] = temp;
}

Graph::~Graph(){
	int i;
	for (i = 0; i < total; i++){
		Node *t = nodelist[i];
		while (t){
			Node *t2 = t;
			t = t->next;
			delete(t2);
		}
	}
	delete nodelist;
}

void Graph::display(){
	int i;
	for (i = 0; i < total; i++){
		cout << i << ": ";
		Node *t = nodelist[i];
		while (t){
			cout << t->num << " ";
			t = t->next;
		}
		cout << '\n';
	}
}

// FIXME: a very ugly method to backtrace the node
int lastsearch(vector<pair<int, int>> & vec, int val){
	vector<pair<int, int>>::iterator it;
	for (it = vec.begin(); it != vec.end(); it++){
		if ((*it).second == val)
			return (*it).first;
	}
}

// 判断图中是否有环，如果有，打印一个
// 返回值为1时表示存在，0表示不存在
// 基本想法：从结点0开始，广度优先遍历所有结点；如果一个结点被标记两次，则证明有环
int Graph::hascycle(){
	int *discovered, *lastdis;
	discovered = new int[total];
	lastdis = new int[total];			// 记录引起discovered改变的结点
	
	int i;
	for (i = 0; i < total; i++){
		discovered[i] = 0;
		lastdis[i] = -1;
	}
	int layer = 0;
	queue<pair<int, int>> q;			// 左代表前一个结点，右代表当前结点
	vector<pair<int, int>> vec;			// 保存以往的搜索路径
	q.push(pair<int, int>(0, 0));
	discovered[0] = 1;
	while (!q.empty()){
		pair<int, int> p = q.front();
		vec.push_back(p);
		q.pop();
		Node *temp = nodelist[p.second];
		while (temp){
			if (discovered[temp->num] == 0){
				discovered[temp->num] = 1;
				lastdis[temp->num] = p.second;
				q.push(pair<int, int>(p.second, temp->num));
			}
			else{						// 邻接链表的关系，当前结点也会指向上一个结点
				if (temp->num != p.first){		// 为假表示结点指回上一个结点，否则，有环
					cout << "Cycle: " << temp->num << " ";
					int f1 = lastdis[temp->num], f2 = p.second;
					int f11, f22;
					cout << f1 << " " << f2 << " ";
					while ((f11 = lastsearch(vec, f1)) != (f22 = lastsearch(vec, f2))){
						cout << f11 << " " << f22 << " ";
					}
					if (f1 != f11 && f2 !=f11)
						cout << f11;
					cout << '\n';
					return 1;
				}
			}
			temp = temp->next;
		}
	}
	delete discovered;
	return 0;
}

int main(){
	Graph *graph = new Graph(3);
	graph->addEdge(0, 1);
	graph->addEdge(1, 2);
	graph->addEdge(0, 2);
	
	graph->display();
	if (graph->hascycle())
		cout << "graph has cycle\n";
	else
		cout << "graph doesn't have cycle\n";

	delete graph;
}