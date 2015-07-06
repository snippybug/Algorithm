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
/*                �༰��Ա����                */
/**********************************************/

struct Status{
	int state;				// �����н��п���չ����õ�����ֵ
	string path;			// ����㵽��ǰ״̬�Ѿ�����·��
	int priority;			// ��ѡ�����ȼ�
	int level;				// ��ǰ�Ĳ㼶
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

// ����չ��
int Status::CantorExpansion(int b[SIZE]){
	int X = 0;
	int n = SIZE-1;
	// ��i��λ���ϵ��������������������У���t�����
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

// ������չ��
void Status::Cantor_inverse(int b[SIZE], int X){
	int n = SIZE - 1;
	bool flag[SIZE] = { false };		//  flag[i]Ϊtrue����i�ѱ�ȡ��
	// շת�����
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
/*                ��ͨ����                */
/**********************************************/

// ��������̵�9�����ִ����ң����ϵ����ų�һ�к󣬳�ȥ�ո�õ������е�������Ϊż����˵���ɽ�
// ���򲻿ɽ�
// Notice��δ֤��
bool solvable(int board[SIZE]){
	int inversion = 0;		// ������
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

// ���̵�״̬ת��(0���ƶ�)
// ����0ʱ��ʾת���ɹ�������1��ʾʧ��(0����Խ��)
int transition(int start[SIZE], int end[SIZE], int direction){
	int x = -1, y = -1;			// x����������y��������
	int nx, ny;	// newX,newY
	// �����ҵ�start��0������
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
	int board[SIZE] = { -1 };		//  ���̣�0�����λ
	for (int i = 0; i < SIZE; i++){
		char temp3[4];				// ��ʹֻ���ȡһ���ַ���ϵͳҲ���ڽ������Ϊ4���ֽڣ�����'a'����'a'\0\0\0��Ϊ�˷�ֹջ�������Ҫ4���ֽڵĿռ�
		scanf("%ls", temp3);
		if (temp3[0] >= '0' && temp3[0] <= '9'){
			board[i] = temp3[0] - '0';
		}
		else{
			board[i] = 0;
		}
	}

	int obj_board[SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };		// Ŀ������
	static bool total_state[362880] = { false };		// 362880=9!
	if (solvable(board) == false){
		printf("unsolvable\n");
		return 0;
	}
	Status init(board);		// ��ʼ״̬
	init.path = "";
	init.level = 0;
	init.priority = 0;
	Status goal(obj_board);
	priority_queue<Status, vector<Status>, greater<Status>> queue;		// Ĭ�ϵĵ���������(�Ƚ���)��less���������ͻṹ��һ�����ѣ�
																		// ����Ҫһ����С������ѡ������С�Ľ�㣬��˻���greater����Ӧ�أ���Ҫ����Status��>������
	queue.push(init);
	Status s(0);
	while (queue.empty() == false){
		// �Ӷ�����ȡ��������С�Ľ��
		// ��total_state�ı�־λ
		// �ж����Ƿ�ΪĿ���㣬����ǣ�����ѭ��;������ǣ�
		// ���ݵ�ǰ״̬���ó���һ�����ܵ�״̬��Ȼ����total_state�ж��Ƿ��ѱ����ʣ�����ǣ���������������
		// ����Status���󲢽���������
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
			if (transition(s_table, d_table, d) == 0){			// ת���ɹ�
				Status new_state(d_table);
				if (total_state[new_state.state] == false){		// δ������
					new_state.path = s.path + d2s(d);
					new_state.level = s.level + 1;
					new_state.priority = new_state.level + manhattanD(obj_board, d_table);
					queue.push(new_state);
				}
			}
		}
	}
	if (s == goal){			// �ҵ�Ŀ��
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

// ���������پ���
int manhattanD(int base[SIZE], int table[SIZE]){
	int d = 0;
	for (int i = 0; i < EDGE_LEN; i++){
		for (int j = 0; j < EDGE_LEN; j++){
			// ����base��ÿһ���������table�е�λ�õ������پ���
			for (int ti = 0; ti < EDGE_LEN; ti++){
				for (int tj = 0; tj < EDGE_LEN; tj++){
					if (table[ti*EDGE_LEN + tj] == base[i*EDGE_LEN + j]){	// �ҵ�Ŀ��
						d = d + abs(ti - i) + abs(tj - j);
					}
				}
			}
		}
	}
	return d;
}

// ѭ������׳�
int factorial(int n){
	assert(n >= 0);
	int ret = 1;
	for (int i = 1; i <= n; i++){
		ret *= i;
	}
	return ret;
}