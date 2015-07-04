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

using namespace std;

const int SIZE = 9;


enum Direction{
	UP, DOWN, LEFT, RIGHT
};

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

int Status::CantorExpansion(int b[SIZE]){
	cout << "Not implemented\n";
	return 0;
}

void Status::Cantor_inverse(int b[SIZE], int s){
	cout << "Not implemented\n";
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

bool solvable(int table[SIZE]);
int transition(int s_table[SIZE], int d_table[SIZE], int direction);
string d2s(int direction);
int manhattanD(int table[SIZE], int base[SIZE]);

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
	cout << "Not implemented\n";
	return 0;
}

int main(){
	int board[SIZE] = { 1, 2, 3, 4, 5, 0, 7, 8, 6 };		//  ���̣�0�����λ
	int obj_board[SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };		// Ŀ������
	bool total_state[362880] = { false };		// 362880=9!
	if (solvable(board) == false){
		cout << "unsolvable\n";
	}
	Status init(board);		// ��ʼ״̬
	init.path = "";
	init.level = 0;
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
					new_state.priority = new_state.level + manhattanD(d_table);
					queue.push(new_state);
				}
			}
		}
	}
	if (s == goal){			// �ҵ�Ŀ��
		cout << s.path << '\n';
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
		ret = "";
	}
	return ret;
}

// ���������پ���
int manhattanD(int table[SIZE]){
	cout << "Not implemented\n";
	return 0;
}