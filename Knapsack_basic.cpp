/*
 * Description:	��N����Ʒ��һ������ΪV�ı�������i����Ʒ������Ϊw[i]����ֵ��c[i]������Щ��Ʒװ�뱳����ʹ��ֵ�ܺ����
 * Input:	��һ�и�����Ʒ���ͱ������������ڶ��и�����Ʒ�������������и�����Ʒ�ļ�ֵ
 * Output:	�������ܼ�ֵ
 * Author:	Wang Zonglei
 * Date:	2015.7.8
 *
 */

#include <iostream>

using namespace std;

inline int max(int a, int b){
	return a > b ? a : b;
}

// ʹ�ö�̬�滮���������
// ���Ʒ���ΪF[i][v] = max{ F[i-1][v], F[i-1][v-wi]+c[i] };
// ����F[i][w]��ʾǰi����Ʒ��������Ϊv�ı������ܵõ�������ֵ
int main(){
	int N = 5;		// ��Ʒ��
	int V = 8;		// ��������
	int *W;			// ��Ʒ����
	W = new int[N+1];
	W[0] = 0;		// Ϊ�˷�����ʣ���Ʒi����������W[i],i>=1
	W[1] = 1;
	W[2] = 3;
	W[3] = 5;
	W[4] = 3;
	W[5] = 2;
	int *C;			// ��Ʒ��ֵ
	C = new int[N+1];
	C[0] = 0;		// Ϊ�˷�����ʣ���Ʒi�ļ�ֵ����W[i],i>=1
	C[1] = 3;
	C[2] = 2;
	C[3] = 1;
	C[4] = 5;
	C[5] = 3;

	int **F;		// ״̬����
	F = new int*[N+1];
	for (int i = 0; i <= N; i++){
		F[i] = new int[V + 1];
	}

	// ��ʼ����һ��
	for (int i = 0; i <= N; i++){
		F[i][0] = 0;			// ����������Ϊ0ʱ���޷������κ���Ʒ
	}
	for (int i = 1; i <= V; i++){
		F[0][i] = 0;
	}
	
	int row = 1;
	while (row <= N){
		for (int j = 1; j <= V; j++){
			int value;
			// ���ڲ�ͬ�����ı����������Ƿ������Ʒi
			// ������ܷ��룬��F[row][j]=F[row-1][j]
			if (j < W[row]){
				value = F[row - 1][j];
			}
			else{		// �ܷ���ʱ��ȡ����Ͳ�����Ľϴ�ֵ
				value = max(F[row - 1][j], F[row - 1][j - W[row]] + C[row]);
			}
			F[row][j] = value;
		}
		++row;
	}
	
	cout << F[N][V]<<'\n';

	for (int i = 0; i <= N; i++){
		delete F[i];
	}
	delete F;
	delete C;
	delete W;
	return 0;
}