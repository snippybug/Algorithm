/*
*	2015.5.28
*	������
*
*	Gale-Shapley Algorithm
*	
*/

// #define NDEBUG

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define N 2000

void group(int **, int **, int *);
void randomList(int, int *);

void main(){
	// ����ط��и���Ȥ��bug
	int **mplist;	// ������ƫ���б�
	int **wplist;	// Ů����ƫ���б�
	int i;

	mplist = malloc(N*sizeof(int*));
	wplist = malloc(N*sizeof(int*));
	for (i = 0; i < N; i++){
		mplist[i] = malloc(N*sizeof(int));
		wplist[i] = malloc(N*sizeof(int));
	}
	clock_t start_time = clock();
	for (i = 0; i < N; i++){
		randomList(N, mplist[i]);	// �������0~N-1��������
		randomList(N, wplist[i]);
	}
	clock_t end_time = clock();
	printf("Time elapsed for randomList: %d ms\n", end_time - start_time);
	int pairs[N];	// ������0��1��2...ƥ���Ů��
	for (i = 0; i < N; i++){
		pairs[i] = -1;
	}
	start_time = clock();
	group(mplist, wplist, pairs);
	end_time = clock();
	printf("Time elapsed for grouping: %d ms\n", end_time - start_time);
	/*printf("Result:\n");
	for (i = 0; i < N; i++){
		printf("(%d, %d)\n", i, pairs[i]);
	}*/

	for (i = 0; i < N; i++){
		free(mplist[i]);
		free(wplist[i]);
	}
	free(mplist);
	free(wplist);
}

void group(int **mplist, int **wplist, int *pairs){
	int wpairs[N];		// Ů����ƥ���
	int *mpairs = pairs;	// ������ƥ���
	int proposed[N];	// �����ĵ���һ��������

	int i;
	for (i = 0; i < N; i++){
		wpairs[i] = -1;
		proposed[i] = 0;
	}

	while (1){
		for (i = 0; i < N; i++){
			if (mpairs[i] == -1		// ���ӵ���
				&& proposed[i] != N		// ������δ������Ů�����
				)
				break;
		}
		if (i == N)
			break;
		// i�����ŵ������ӵı��
		int w =  mplist[i][proposed[i]++];	// Let w be the highest-ranked woman in m's preference list to whom m has not yet proposed
		if (wpairs[w] == -1){		// if w is free
			mpairs[i] = w;
			wpairs[w] = i;
		}
		else{
			int mm = wpairs[w];	// w is currently engaged to m'
			int j;
			for (j = 0; j < N; j++){
				if (wplist[w][j] == mm
					|| wplist[w][j] == i)
					break;
			}
			if (wplist[w][j] == i){	// w prefers m to m'
				mpairs[wpairs[w]] = -1;		// m' becomes free
				mpairs[i] = w;
				wpairs[w] = i;
			}
		}
	}
}

void randomList(int n, int *list){
	int i;
	int *mark = malloc(n*sizeof(int));		// mark[i]==1��ʾ����i�ѳ�����list��
	static unsigned int count = 0;			// Ϊ�˲��������������
	int oldi1, oldi2;
	assert(list);
	srand(time(NULL) + count);
	count++;
	for (i = 0; i < n; i++)
		mark[i] = 0;
	oldi1 = 0;
	oldi2 = n - 1;
	for (i = 0; i < n; i++){
		int j, start, length;
		assert(list[i]);
		// ɨ�����飬�ҳ������ж�
		if (i % 2 == 0){	// ��ǰ����
			for (j = oldi1; j < n; j++){
				if (mark[j] == 0)
					break;
			}
			oldi1 = j;
			start = j;
			for (j = j + 1; j < n; j++){
				if (mark[j] == 1)
					break;
			}
			length = j - start;
		}
		else{				// �Ӻ���ǰ
			for (j = oldi2; j >= 0; j--){
				if (mark[j] == 0)
					break;
			}
			oldi2 = j;
			for (start = j; start >= 0; start--){
				if (mark[start] == 1)
					break;
			}
			start++;
			length = j - start + 1;
		}
		list[i] = start + rand() % length;
		mark[list[i]] = 1;
	}
	free(mark);
}