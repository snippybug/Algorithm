/*
 * Name: Eight Queens Puzzle
 * Author: Wang Zonlei
 * Data: 2015.6.17
 * Question: How to place eight queens on a chessboard so that no queen is in check from any other(i.e., no queens are in the same row, column, or diagonal)
 */

// Result
/*
	ע��13���Ժ��ٴ�ӡÿ�ַ�����ֻ��ӡ�ܽ����
	���̴�С	�����		ʱ��(ms)
	1		1		0
	2		0		0
	3		0		0
	4		2		1
	5		10		1
	6		4		1
	7		40		4
	8		92		13
	9		352		47
	10		724		136
	11		2680		628
	12		14200		3720
	13		73712		6370
	14		365596		35437
	15		2279184		224875
	16		14772512	1570939
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define ROWS 8
#define COLS 8

void recursive_search(int layer);
void setqueen(int row, int col);
void resetqueen(int row, int col);
int chessboard[ROWS][COLS];		// 0��ʾ���ã�1��ʾ�����ã�2��ʾ�ʺ��λ��
int countedboard[ROWS][COLS];	// ������������λ(set)������(reset)
int num;

int main(){
	clock_t start_time = clock();
	recursive_search(0);
	clock_t end_time = clock();
	printf("num of methods=%d\n", num);
	printf("Time elapsed: %dms\n", end_time - start_time);
	return 0;
}

// ������ǰ�����п��õĿռ�
// ѡ��λ�ú��úᡢ����б���ϵ�����Ϊ1����ʾ�����ã��ݹ����ѡ����һ��
// �ݹ鷵�غ����֮ǰ����λ������ѡ��λ��
void recursive_search(int col){
	int i, j;
	if (col == ROWS){
		++num;
		/*
		printf("---------------%d------------------\n", ++num);
		for (i = 0; i < ROWS; i++){
			for (j = 0; j < COLS; j++){
				printf("%d ", chessboard[i][j]);
			}
			putchar('\n');
		}
		*/
		return;
	}
	for (i = 0; i < ROWS; i++){
		if (chessboard[i][col] == 0){
			setqueen(i, col);
			recursive_search(col + 1);
			resetqueen(i, col);
		}
	}
}

// ����Ӧλ��Ϊ2���ᡢ����б��Ϊ1
void setqueen(int row, int col){
	int i, j;
	chessboard[row][col] = 2;
	// ����
	i = row - 1;
	j = col + 1;
	while (i >= 0 && j < ROWS){
		if (chessboard[i][j] == 0){		// ����
			chessboard[i][j] = 1;
			assert(countedboard[i][j] == 0);
		}
		else{
			assert(chessboard[i][j] == 1);
		}
		countedboard[i][j] ++;
		i--;
		j++;
	}
	// ����
	i = row + 1;
	j = col + 1;
	while (i < ROWS && j < ROWS){
		if (chessboard[i][j] == 0){		// ����
			chessboard[i][j] = 1;
			assert(countedboard[i][j] == 0);
		}
		else{
			assert(chessboard[i][j] == 1);
		}
		countedboard[i][j] ++;
		i++;
		j++;
	}
	// ��
	i = row;
	j = col + 1;
	while (j < COLS){
		if (chessboard[i][j] == 0){		// ����
			chessboard[i][j] = 1;
			assert(countedboard[i][j] == 0);
		}
		else{
			assert(chessboard[i][j] == 1);
		}
		countedboard[i][j] ++;
		j++;
	}
}

void resetqueen(int row, int col){
	int i, j;
	chessboard[row][col] = 0;
	// ����
	i = row - 1;
	j = col + 1;
	while (i >= 0 && j < ROWS){
		assert(chessboard[i][j] != 0);
		countedboard[i][j]--;
		if (countedboard[i][j] == 0){
			chessboard[i][j] = 0;
		}
		i--;
		j++;
	}
	// ����
	i = row + 1;
	j = col + 1;
	while (i < ROWS && j < ROWS){
		assert(chessboard[i][j] != 0);
		countedboard[i][j]--;
		if (countedboard[i][j] == 0){
			chessboard[i][j] = 0;
		}
		i++;
		j++;
	}
	// ��
	i = row;
	j = col + 1;
	while (j < COLS){
		assert(chessboard[i][j] != 0);
		countedboard[i][j]--;
		if (countedboard[i][j] == 0){
			chessboard[i][j] = 0;
		}
		j++;
	}
}