/*
* Description:	Farmer John has purchased a lush new rectangular pasture composed of M by N (1 �� M �� 12; 1 �� N �� 12) square parcels. He wants to grow 
*				some yummy corn for the cows on a number of squares. Regrettably, some of the squares are infertile and can't be planted. Canny FJ knows that the cows 
*				dislike eating close to each other, so when choosing which squares to plant, he avoids choosing squares that are adjacent; no two chosen squares 
*				share an edge. He has not yet made the final choice as to which squares to plant. Being a very open-minded man, Farmer John wants to consider all 
*				possible options for how to choose the squares for planting. He is so open-minded that he considers choosing no squares as a valid option!
*				Please help Farmer John determine the number of ways he can choose the squares to plant.
*
* Input:	Line 1: Two space-separated integers: M and N
*			Lines 2.. M+1: Line i+1 describes row i of the pasture with N space-separated integers indicating whether a square is fertile (1 for fertile, 0 for infertile) 
* Output:	Line 1: One integer: the number of ways that FJ can choose the squares modulo 100,000,000. 
* Author:	Wang Zonglei
* Date:	2015.7.7
*
*/

#include <cstdio>
#include <cmath>
#include <cassert>

using namespace std;

bool judge(const int status, const int n);

// �ö�̬�滮���
// ���Ʒ���Ϊ��dp[i][status] = sigma { dp[i-1][��status����ͻ��i-1�е�״̬] }
int main(){
	int M;			// ����������
	int N;			// ����������
	scanf("%d%d", &M, &N);
	int *mask;			// ÿһ���γ�һ�����룬0������ã�1��������
	mask = new int[M];
	// ��������
	for (int i = 0; i < M; i++){
		mask[i] = 0;
		int k;
		for (int j = 0; j < N; j++){
			mask[i] <<= 1;
			scanf("%d", &k);
			if (k == 1){
				mask[i] |= 1;
			}
		}
	}
	int **dp;			// dp[i][status]��ʾ��1�з�status״̬��ţ�ķ�����
	dp = new int*[M];
	int nstatus = 1 << N;		// �ܵ�״̬��
	for (int i = 0; i < M; i++){
		dp[i] = new int[nstatus];
	}
	// ���ñ߽�����
	dp[0][0] = 1;
	for (int i = 1; i < nstatus; i++){		// assert(nstatus>=2)
		if (judge(i, N)==false			// �ж�i�Ƿ����������ڵ�1
			&& (i&mask[0]) == i){
			dp[0][i] = 1;
		}
		else{
			dp[0][i] = 0;
		}
	}

	int row = 1;
	while (row < M){
		// ��ʼ��
		for (int j = 0; j < nstatus; j++){
			dp[row][j] = 0;
		}

		// status=0ʱ���κ�״̬������
		for (int j = 0; j < nstatus; j++){
				dp[row][0] += dp[row - 1][j];
		}
		// status!=0ʱ����Ҫ������һ�е�״̬
		for (int j = 1; j < nstatus; j++){
			if (judge(j, N) == true
				|| (j&mask[row]) != j){		// �����״̬���������ڵ�1���������������ݣ�ֱ��Ϊ0
				dp[row][j] = 0;
			}
			else{							// ���򣬼�����һ����֮����ͻ��״̬�ķ�����֮��
				for (int k = 0; k < nstatus; k++){
					if ((j & k) == 0){
						dp[row][j] += dp[row - 1][k];
					}
				}
			}
		}
		row++;
	}

	// ���յĽ�������һ�еķ�����֮��
	int result = 0;
	for (int i = 0; i < nstatus; i++){
		result += dp[M - 1][i];
	}
	printf("%d\n", result);

	for (int i = 0; i < M; i++){
		delete dp[i];
	}
	delete dp;
	delete mask;
	return 0;
}

// �ж�status�ĵ�nλ�Ƿ�������������1
// ���򷵻�true�����򷵻�false
bool judge(const int status, const int n){
	assert(n < 32);
	assert(n > 0);
	for (int i = 0; i < n - 1; i++){
		int a = status >> i & 1;
		int b = status >> (i + 1) & 1;
		if ((a&b) == 1){
			return true;
		}
	}
	return false;
}