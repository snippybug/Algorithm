/*
* ����������Ŀռ临�Ӷ���O(VN)����O(V)
*
* �ο��������Ž�V2��
*
* Author:	Wang Zonglei
* Date:	2015.7.8
*
*/

#include <iostream>

using namespace std;

inline int max(int a, int b){
	return a > b ? a : b;
}

// �Ż���ԭ���ǣ����Ʒ���ֻ�õ�����һ�е�״̬����˿���ֻ����������þ���������״̬

int main(){
	int N = 5;		// ��Ʒ��
	int V = 8;		// ��������
	int *W;			// ��Ʒ����
	W = new int[N + 1];
	W[0] = 0;		// Ϊ�˷�����ʣ���Ʒi����������W[i],i>=1
	W[1] = 1;
	W[2] = 3;
	W[3] = 5;
	W[4] = 3;
	W[5] = 2;
	int *C;			// ��Ʒ��ֵ
	C = new int[N + 1];
	C[0] = 0;		// Ϊ�˷�����ʣ���Ʒi�ļ�ֵ����W[i],i>=1
	C[1] = 3;
	C[2] = 2;
	C[3] = 1;
	C[4] = 5;
	C[5] = 3;

	int *F;		// ״̬����
	F = new int [V + 1];

	// ��ʼ������
	for (int i = 0; i <= V; i++){
		F[i] = 0;
	}

	int row = 1;
	while (row <= N){
		for (int j = V; j >= W[row];j--){				// ����Ϊ������Ϊ���������ϵ�״̬
			F[j] = max(F[j], F[j - W[row]] + C[row]);
		}
		++row;
	}

	cout << F[V] << '\n';

	delete F;
	delete C;
	delete W;
	return 0;
}