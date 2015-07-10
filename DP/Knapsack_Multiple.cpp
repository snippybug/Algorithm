/*
 * ���ر�������
 * ����ȫ�����Ļ����ϣ�������Ʒi������ΪMi
 *
 * �ο��������Ž�V2��
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

// ����˼·������ת����01�������⣬���ö�̬�滮���
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
	int *M;			// ��Ʒ����
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

	int *F;		// ״̬����
	F = new int[V + 1];

	// ��ʼ������
	for (int i = 0; i <= V; i++){
		F[i] = 0;
	}

	int row = 0;
	while (row < N1){
		for (int j = V; j >= W1[row]; j--){				// ����Ϊ������Ϊ�����������ϵ�״̬
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

// ����ȫ����������ͬ�����ǽ���i����Ʒ������������Ʒ��ʹ��ԭ�����е�i����Ʒ��ȡ��ÿ�ֲ��ԡ���ȡ0..Mi���������������µķ�������
// ���ң�����Mi����Ʒ�������ܳ���
int cloneItems(const int *W, const int *C, const int *M, int **rW, int **rC, const int N, const int V){
	vector<Item> items;
	for (int i = 0; i < N; i++){
		int n = 0;					// ���Ƶĸ���n����Mi-2^n+1>=0
		int upper;
		if ((M[i] * W[i]) > V){			// ������������������ʱ������ȫ��������ȼ�
			upper = V;
		}
		else{
			upper = M[i] + 1;
		}
		while ((1 << n) < upper){
			++n;
		}
		if (n>0){					
			--n;					// ������
		}
		else{						// ���n==0��˵��M[i]=0�������������Ʒ
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