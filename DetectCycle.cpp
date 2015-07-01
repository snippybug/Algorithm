/*
 * �����ڣ�2015.6.8
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
	Node **nodelist;		// �ڽ�����
	int total;
};

// n��������
Graph::Graph(int n){
	nodelist = new Node*[n];
	int i;
	for (i = 0; i < n; i++){
		nodelist[i] = NULL;
	}
	total = n;
}

// û�����߽��飬Ҳû���ж��ظ���
void Graph::addEdge(int m, int n){
	Node *temp = nodelist[m];
	temp = new Node(n);
	temp->next = nodelist[m];
	nodelist[m] = temp;

	// �ڽ��������������
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

// �ж�ͼ���Ƿ��л�������У���ӡһ��
// ����ֵΪ1ʱ��ʾ���ڣ�0��ʾ������
// �����뷨���ӽ��0��ʼ��������ȱ������н�㣻���һ����㱻������Σ���֤���л�
int Graph::hascycle(){
	int *discovered, *lastdis;
	discovered = new int[total];
	lastdis = new int[total];			// ��¼����discovered�ı�Ľ��
	
	int i;
	for (i = 0; i < total; i++){
		discovered[i] = 0;
		lastdis[i] = -1;
	}
	int layer = 0;
	queue<pair<int, int>> q;			// �����ǰһ����㣬�Ҵ���ǰ���
	vector<pair<int, int>> vec;			// ��������������·��
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
			else{						// �ڽ�����Ĺ�ϵ����ǰ���Ҳ��ָ����һ�����
				if (temp->num != p.first){		// Ϊ�ٱ�ʾ���ָ����һ����㣬�����л�
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