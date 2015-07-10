/*
 * Description:	The 15-puzzle has been around for over 100 years; even if you don't know it by that name, you've seen it. It is constructed with 15 sliding tiles, each with a
 *				number from 1 to 15 on it, and all packed into a 4 by 4 frame with one tile missing. Let's call the missing tile 'x'; the object of the puzzle is to arrange the tiles so
 *				that they are ordered as:
 *				1	2	3	4
 *				5	6	7	8
 *				9	10	11	12
 *				13	14	15	x
 *				where the only legal operation is to exchange 'x' with one of the tiles with which it shares the edge.
 *				Not all puzzles can be solved; in 1870, a man named Sam Loyd was famous for distributing an unsolvable version of the puzzle, and frustrating many people. In
 *				fact, all you have to do to make a regular puzzle into an unsolved one is to swap two tiles(not counting the missing 'x' tile, of course).
 *				In this problem, you  will write a program for solving the less well-known 8-puzzle, composed of tiles on a three by three arrangement.
 * Input:	You will receive, several description of configuration of the 8 puzzle. One description is just a list of the tiles in their initial positions, with the rows listed
 *			from top to bottom, and the tiles listed from left to right within a row, where the tiles are represented by numbers 1 to 8, plus 'x'. For example, this puzzle
 *			1	2	3
 *			x	4	6
 *			7	5	8
 *			is described by this list:
 *			1 2 3 x 4 6 7 5 8
 * Output:	You will print to standard output either the word "unsolvable", if the puzzle has no solution, or a string consisting entirely of the letters 'r', 'l', 'u' and 'd'
 *			that describes a series of moves that produce a solution('r', 'l', 'u' and 'd' stand for right, left, up and down respectively).
 *			The string should include no spaces and start at the begining of the line. Do not print a blank line between case.
 *
 */
#include <iostream>
#include <queue>
#include <functional>
#include <string>
#include <cassert>

using namespace std;

const int SIZE = 9;
const int EDGE_LEN = 3;


enum Direction{
	UP, DOWN, LEFT, RIGHT
};

bool solvable(int table[SIZE]);
int transition(int s_table[SIZE], int d_table[SIZE], int direction);
string d2s(int direction);
int manhattanD(int base[SIZE], int table[SIZE]);
int factorial(int n);

/**********************************************/
/*                类及成员函数                */
/**********************************************/

struct Status{
	int state;				// 对排列进行康托展开后得到的数值
	string path;			// 从起点到当前状态已经过的路径
	int priority;			// 挑选的优先级
	int level;				// 当前的层级
	Status(int b[SIZE]){
		state = CantorExpansion(b);
	}
	void get_board(int b[SIZE]){
		Cantor_inverse(b, state);
	}
	Status(int s) :state(s){}			// Only for test

	friend bool operator>(const Status&, const Status&);
	friend ostream& operator<<(ostream&, const Status&);
	friend bool operator==(const Status&, const Status&);
private:
	int CantorExpansion(int [SIZE]);
	void Cantor_inverse(int[SIZE], int);
};

// 康托展开
int Status::CantorExpansion(int b[SIZE]){
	int X = 0;
	int n = SIZE-1;
	// 第i个位置上的数，是在其后的所有数中，第t大的数
	for (int i = 0; i < SIZE-1; i++){
		int t = 0;
		for (int j = i + 1; j < SIZE; j++){
			if (b[j]<b[i]){
				t++;
			}
		}
		if (t != 0){
			X += t*factorial(n);
		}
		n--;
	}
	return X;
}

// 康托逆展开
void Status::Cantor_inverse(int b[SIZE], int X){
	int n = SIZE - 1;
	bool flag[SIZE] = { false };		//  flag[i]为true表明i已被取走
	// 辗转相除法
	for (int i = 0; i<SIZE; i++){
		int order;
		if (X == 0){
			order = 0;
		}
		else{
			int temp1 = factorial(n);
			order = X / temp1;
			X = X%temp1;
		}

		for (int j = 0; j < SIZE; j++){
			if (flag[j] == true){
				continue;
			}
			else{
				if (order>0){
					order--;
				}
				else{
					flag[j] = true;
					b[i] = j;
					break;
				}
			}
		}
		n--;
	}
}


bool operator>(const Status& s1, const Status& s2){
	return s1.priority > s2.priority;
}

ostream& operator<<(ostream& out, const Status& s){
	out << s.state;
	return out;
}

bool operator==(const Status& s1, const Status& s2){
	return s1.state == s2.state;
}

/**********************************************/
/*                普通函数                */
/**********************************************/

// 如果将棋盘的9个数字从左到右，从上到下排成一列后，除去空格得到的数列的逆序数为偶数，说明可解
// 否则不可解
// Notice：未证明
bool solvable(int board[SIZE]){
	int inversion = 0;		// 逆序数
	for (int i = 0; i < SIZE - 1; i++){
		for (int j = i + 1; j < SIZE; j++){
			if (board[i] == 0){
				break;
			}
			else{
				if (board[j] == 0){
					continue;
				}
				else{
					if (board[i] > board[j]){
						inversion++;
					}
				}
			}
		}
	}
	//cout << "invsersion=" << inversion << '\n';
	return (inversion % 2 == 0);
}

// 棋盘的状态转换(0的移动)
// 返回0时表示转换成功，返回1表示失败(0可能越界)
int transition(int start[SIZE], int end[SIZE], int direction){
	int x = -1, y = -1;			// x代表行数，y代表列数
	int nx, ny;	// newX,newY
	// 首先找到start中0的坐标
	for (int i = 0; i < EDGE_LEN; i++){
		for (int j = 0; j < EDGE_LEN; j++){
			if (start[i*EDGE_LEN + j] == 0){
				x = i;
				y = j;
				break;
			}
		}
	}
	if (x == -1){
		cout << "Warning: transition--array 'start' doesn't have number '0'\n";
		return 1;
	}
	switch (direction){
	case UP:
		nx = x - 1;
		ny = y;
		break;
	case DOWN:
		nx = x + 1;
		ny = y;
		break;
	case LEFT:
		nx = x;
		ny = y - 1;
		break;
	case RIGHT:
		nx = x;
		ny = y + 1;
		break;
	default:
		cout << "Warning: transtion--Unkown direction\n";
	}
	if (nx >= EDGE_LEN || ny >= EDGE_LEN || nx < 0 || ny < 0){
		return 1;
	}
	for (int i = 0; i < SIZE; i++){
		end[i] = start[i];
	}
	int temp2 = end[x*EDGE_LEN + y];
	end[x*EDGE_LEN + y] = end[nx*EDGE_LEN + ny];
	end[nx*EDGE_LEN + ny] = temp2;

	return 0;
}

int main(){
	int board[SIZE] = { -1 };		//  棋盘，0代表空位
	for (int i = 0; i < SIZE; i++){
		char temp3[4];				// 即使只想读取一个字符，系统也会在将其对齐为4个字节，例如'a'会变成'a'\0\0\0。为了防止栈溢出，需要4个字节的空间
		scanf("%ls", temp3);
		if (temp3[0] >= '0' && temp3[0] <= '9'){
			board[i] = temp3[0] - '0';
		}
		else{
			board[i] = 0;
		}
	}

	int obj_board[SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };		// 目标棋盘
	static bool total_state[362880] = { false };		// 362880=9!
	if (solvable(board) == false){
		printf("unsolvable\n");
		return 0;
	}
	Status init(board);		// 初始状态
	init.path = "";
	init.level = 0;
	init.priority = 0;
	Status goal(obj_board);
	priority_queue<Status, vector<Status>, greater<Status>> queue;		// 默认的第三个参数(比较器)是less，但这样就会构造一个最大堆，
																		// 我需要一个最小堆来挑选代价最小的结点，因此换成greater，相应地，需要重载Status的>操作符
	queue.push(init);
	Status s(0);
	while (queue.empty() == false){
		// 从队列中取出代价最小的结点
		// 置total_state的标志位
		// 判断其是否为目标结点，如果是，跳出循环;如果不是，
		// 根据当前状态，得出下一步可能的状态，然后用total_state判断是否已被访问，如果是，放弃操作，否则
		// 创建Status对象并将其放入队列
		s = queue.top();
		queue.pop();
		total_state[s.state] = true;
		if (s == goal){
			break;
		}
		int s_table[SIZE];
		s.get_board(s_table);
		for (int d = UP; d <= RIGHT; d++){
			int d_table[SIZE];
			if (transition(s_table, d_table, d) == 0){			// 转换成功
				Status new_state(d_table);
				if (total_state[new_state.state] == false){		// 未被访问
					new_state.path = s.path + d2s(d);
					new_state.level = s.level + 1;
					new_state.priority = new_state.level + manhattanD(obj_board, d_table);
					queue.push(new_state);
				}
			}
		}
	}
	if (s == goal){			// 找到目标
		printf("%s\n", s.path.c_str());
	}
	else{
		cout << "Can't find legal path\n";
	}
}

string d2s(int d){
	string ret;
	switch (d){
	case UP:
		ret = "u";
		break;
	case DOWN:
		ret = "d";
		break;
	case LEFT:
		ret = "l";
		break;
	case RIGHT:
		ret = "r";
		break;
	default:
		cout << "Warning: d2s, Unkown direction\n";
		ret = "";
	}
	return ret;
}

// 计算曼哈顿距离
int manhattanD(int base[SIZE], int table[SIZE]){
	int d = 0;
	for (int i = 0; i < EDGE_LEN; i++){
		for (int j = 0; j < EDGE_LEN; j++){
			// 计算base中每一个点距其在table中的位置的曼哈顿距离
			for (int ti = 0; ti < EDGE_LEN; ti++){
				for (int tj = 0; tj < EDGE_LEN; tj++){
					if (table[ti*EDGE_LEN + tj] == base[i*EDGE_LEN + j]){	// 找到目标
						d = d + abs(ti - i) + abs(tj - j);
					}
				}
			}
		}
	}
	return d;
}

// 循环计算阶乘
int factorial(int n){
	assert(n >= 0);
	int ret = 1;
	for (int i = 1; i <= n; i++){
		ret *= i;
	}
	return ret;
}