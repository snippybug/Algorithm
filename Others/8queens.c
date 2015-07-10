/*
 * Name: Eight Queens Puzzle
 * Author: Wang Zonlei
 * Data: 2015.6.17
 * Question: How to place eight queens on a chessboard so that no queen is in check from any other(i.e., no queens are in the same row, column, or diagonal)
 */

// Result
/*
	注：13及以后不再打印每种方案，只打印总解答数
	棋盘大小	解答数		时间(ms)
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
int chessboard[ROWS][COLS];		// 0表示可用，1表示不可用，2表示皇后的位置
int countedboard[ROWS][COLS];	// 计数，方便置位(set)与重置(reset)
int num;

int main(){
	clock_t start_time = clock();
	recursive_search(0);
	clock_t end_time = clock();
	printf("num of methods=%d\n", num);
	printf("Time elapsed: %dms\n", end_time - start_time);
	return 0;
}

// 遍历当前列所有可用的空间
// 选好位置后，置横、竖、斜线上的棋盘为1，表示不可用，递归调用选择下一列
// 递归返回后，清除之前的置位，重新选择位置
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

// 置相应位置为2，横、竖、斜线为1
void setqueen(int row, int col){
	int i, j;
	chessboard[row][col] = 2;
	// 右上
	i = row - 1;
	j = col + 1;
	while (i >= 0 && j < ROWS){
		if (chessboard[i][j] == 0){		// 空闲
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
	// 右下
	i = row + 1;
	j = col + 1;
	while (i < ROWS && j < ROWS){
		if (chessboard[i][j] == 0){		// 空闲
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
	// 右
	i = row;
	j = col + 1;
	while (j < COLS){
		if (chessboard[i][j] == 0){		// 空闲
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
	// 右上
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
	// 右下
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
	// 右
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