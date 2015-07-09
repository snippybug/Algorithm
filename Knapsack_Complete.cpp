/*
 * �ſ�������ÿ����Ʒ�����޼�������
 * Author:	Wang Zonglei
 * Date:	2015.7.9
 * 
 */

// ��������
// 1. ��������Ci<=Cj��Wi>=Wj����Ʒi��j������ֱ��ȥ��j
// 2. �ѵ�i����Ʒ��ɷ���ΪCi*2^k����ֵΪWi*2^k�����ɼ���Ʒ������kȡ��Ci*2^k<=V�ķǸ���
// ֮���Կ�����ô��������Ϊ���۵�i����Ʒȡ���ټ��������������ɸ�2^k��ʾ(����ȡ3����3=2^0+2^1)

#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

int selectItems(const int *W, const int *C, int **rW, int **rC, const int N);
int cloneItems(const int *W, const int *C, int **rW, int **rC, const int N, const int V);

int main(){
	int N = 5;		// ��Ʒ��
	int V = 8;		// ��������
	int *W;			// ��Ʒ����
	W = new int[N];
	W[0] = 1;
	W[1] = 3;
	W[2] = 5;
	W[3] = 3;
	W[4] = 2;
	int *C;			// ��Ʒ��ֵ
	C = new int[N];
	C[0] = 3;
	C[1] = 2;
	C[2] = 1;
	C[3] = 5;
	C[4] = 3;

	int *W1, *C1;
	int N1;
	N1=selectItems(W, C, &W1, &C1, N);		// ����1
	delete C;
	delete W;
	C = NULL;
	W = NULL;
	
	int *W2, *C2;
	int N2;

	N2 = cloneItems(W1, C1, &W2, &C2, N1, V);	// ����2
	delete C1;
	delete W1;
	C1 = NULL;
	W1 = NULL;
	// �����ѽ���ȫ��������ת��Ϊ01�������⣬�ö�̬�滮�������

	int *F;		// ״̬����
	F = new int[V + 1];

	// ��ʼ������
	for (int i = 0; i <= V; i++){
		F[i] = 0;
	}

	int row = 0;
	while (row < N2){
		for (int j = V; j >= 0; j--){				// ����Ϊ������Ϊ�����������ϵ�״̬
			int value;
			// ���ڲ�ͬ�����ı����������Ƿ������Ʒi
			// ������ܷ��룬��F[row][j]=F[row-1][j]
			if (j < W2[row]){
				value = F[j];
			}
			else{		// �ܷ���ʱ��ȡ����Ͳ�����Ľϴ�ֵ
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

// �����е���Ʒ����ɸ������Wi<=Wj��Ci>=Cj����Ʒj
// ������Ϊ����������ڴ棬��ָ�����rW��rC�У�Ҫ��������ͷ�
// ����ʣ�����Ʒ��
int selectItems(const int *W, const int *C, int **rW, int **rC, const int N){
	assert(rW && rC);
	priority_queue<Item, vector<Item>, greater<Item>> queue;		// ��������Ʒ����������
	for (int i = 0; i < N; i++){
		queue.push(Item(W[i], C[i]));
	}
	vector<Item> items;
	while (queue.empty()==false){			// ��priority_queueת��Ϊvector(��û��ֱ�ӵķ�����)
		items.push_back(queue.top());
		queue.pop();
	}
	vector<Item>::iterator it = items.begin();
	while (it != items.end() - 1){			// ����ÿһ����Ʒ�����ļ�ֵ��Ӧ�ñ���С����Ʒ�󣬷����Ҫ��ɾ��
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

// ��ÿһ����Ʒ����Ϊ����Ci*2^k����ֵΪWi*2^k�����ɼ���Ʒ
// �����������ͷ�ΪrW��rC������ڴ�
// ������Ʒ��
int cloneItems(const int *W, const int *C, int **rW, int **rC, const int N, const int V){
	vector<Item> items;
	for (int i = 0; i < N; i++){
		int n = 0;					// ���Ƶĸ���
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
