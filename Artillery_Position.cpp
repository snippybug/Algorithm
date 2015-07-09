/*
 * Description:	司令部的将军们打算在N*M的网格地图上部署他们的炮兵部队。一个N*M的地图由N行M列组成，地图的每一格可能是山地（用"H" 表示），也可能是平原（用"P"表示）。
 *				在每一格平原地形上最多可以布置一支炮兵部队（山地上不能够部署炮兵部队）；一支炮兵部队在地图上的攻击范围如图中黑色区域所示： 
 *				如果在地图中的灰色所标识的平原上部署一支炮兵部队，则图中的黑色的网格表示它能够攻击到的区域：沿横向左右各两格，沿纵向上下各两格。图上其它白色网格均攻击不到。
 *				从图上可见炮兵的攻击范围不受地形的影响。 现在，将军们规划如何部署炮兵部队，在防止误伤的前提下（保证任何两支炮兵部队之间不能互相攻击，
 *				即任何一支炮兵部队都不在其他支炮兵部队的攻击范围内），在整个地图区域内最多能够摆放多少我军的炮兵部队。
 * Input:	第一行包含两个由空格分割开的正整数，分别表示N和M； 
 *			接下来的N行，每一行含有连续的M个字符('P'或者'H')，中间没有空格。按顺序表示地图中每一行的数据。N <= 100；M <= 10。 
 * Output:	仅一行，包含一个整数K，表示最多能摆放的炮兵部队的数量。 
 *
 * Author:	Wang Zonglei
 * Date:	2015.7.8
 *
 *
 */

#include <cstdio>
#include <cassert>

using namespace std;

bool judge(int status, int n);
inline int count(int status, int n);
int max_line(int *a, int n);
int max_matrix(int **a, int m, int n);

int main(){
	int Rows;			// 行数
	int Cols;			// 列数
	
	Rows = 5;
	Cols = 4;
	int *mask;			// 地形的掩码，0表示山地，1表示平原
	mask = new int[Rows];
	mask[0] = 0xb;
	mask[1] = 0xc;
	mask[2] = 0xf;
	mask[3] = 0xa;
	mask[4] = 0x9;

	// F[i][j][k]表示第i行状态为j，第i-1行状态为k时，最多的炮兵数量
	int nstatus = 1 << Cols;
	int ***F;
	F = new int**[Rows];
	for (int i = 0; i < Rows; i++){
		F[i] = new int*[nstatus];
		for (int j = 0; j < nstatus; j++){
			F[i][j] = new int[nstatus];
		}
	}

	// 初始化第一行
	for (int i = 0; i < nstatus; i++){
		int c;
		if (judge(i, Cols) == false	// 一行内没有冲突
			&& (i&mask[0]) == i)			// 不与地形冲突
			{
			c = count(i, Cols);				// 炮兵的个数
		}
		else{
			c = 0;
		}
		for (int j = 0; j < nstatus; j++){
			F[0][j][j] = c;
		}
	}

	int row = 1;
	while (row < Rows){
		for (int i = 0; i < nstatus; i++){
			if (judge(i, Cols) == false			// 一行内没有冲突
				&& (i&mask[row])==i){			// 不与地形冲突
				int c;
				for (int j = 0; j < nstatus; j++){
					if ((i&j) == 0){				// 不与上一行冲突
						c = count(i, Cols) + max_line(F[row - 1][j], nstatus);
					}
					else{
						c = 0;
					}

					F[row][i][j] = c;
				}
			}
			else{
				for (int j = 0; j < nstatus; j++){
					F[row][i][j] = 0;
				}
			}
		}
		++row;
	}

	int result = max_matrix(F[row - 1], nstatus, nstatus);
	printf("%d", result);

	for (int i = 0; i < Rows; i++){
		for (int j = 0; j < nstatus; j++){
			delete F[i][j];
		}
		delete F[i];
	}
	delete F;
	delete mask;
	return 0;
}

// 判断一行内的炮兵位置是否冲突，"是"返回true，"不是"返回false
// 判断是否有间距<=2的1
bool judge(int status, int n){
	assert(n <= 10);
	int a[5];
	status &= (1 << n) - 1;
	if ((status & 3) == 3){		// 低两位为1
		return true;
	}
	int i = 2;
	do{
		a[2] = status&(1 << i);
		a[1] = status&(1 << (i - 1));
		a[0] = status&(1 << (i - 2));
		a[3] = status&(1 << (i + 1));
		a[4] = status&(1 << (i + 2));
		if (a[2] != 0){
			if (a[0] != 0 || a[1] != 0 || a[3] != 0 || a[4] != 0){
				return true;
			}
		}
		i++;
	} while (i < n);
	return false;
}

// 统计炮兵的数量(即1的个数)
int count(int status, int n){
	int c = 0;
	for (int i = 0; i<n; i++){
		if ((status&(1 << i)) != 0){
			++c;
		}
	}
	return c;
}

int max_line(int *a, int n){
	assert(n > 0);
	int max = a[0];
	for (int i = 0; i<n; i++){
		if (max < a[i]){
			max = a[i];
		}
	}
	return max;
}

int max_matrix(int **a, int m, int n){
	assert(m>0 && n>0);
	int max = a[0][0];
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			if (max < a[i][j]){
				max = a[i][j];
			}
		}
	}
	return max;
}