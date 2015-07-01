/*
 * Description: You have two jugs, A and B, and an infinite supply of water. There are three types of actions that you can use: (1) you can fill a jug. (2) you can empty a
 *				jug, and (3) you can pour from one jug to the other. Pouring from one jug to the other stops when the first jug is empty or the second jug is full, whichever
 *				comes first. For example, if A has 5 gallons and B has 6 gallons and a capacity of 8, then pouring from A to B leaves B full and 3 gallons in A.
 *				A problem is given by a triple (Ca, Cb, N), where Ca and Cb are the capacities of the jugs A and B, respectively, and N is the goal. You may assume that the
 *				input you are given does have a solution.
 * Input:	Input to your program consists of a series of input lines each defining one puzzle. Input for each puzzle is a single line of three positive integers: Ca, Cb and
 *			N. Ca and Cb are the capacities of jugs A and B, and N is the goal. You can assume 0 < Ca <= Cb and N <= Cb <= 1000 and that A and B are relatively prime to one
 *			another.
 * Output:	Output from your program will consist of a series of instructions from the list of the potiential output lines which will result in either of the jugs containing 
 *			exactily N gallons of water. The last line of output for each puzzle should be the line "success". Output lines start in column 1 and there should be no empty lines
 *			nor any trailing spaces.
 * Author:	Wang Zonglei
 * Date:	2015.7.1
 *
 */

#include <iostream>
#include <vector>

using namespace std;

#define MIN(a, b) ((a>b?b:a))

enum Action{
	EMPTYA, EMPTYB,
	FILLA, FILLB,
	POURAB, POURBA,
	NACTION
};

vector<int> actions;			// ��¼��ǰ�Ķ���
int Ca, Cb, N;				// Ca����A��������Cb����B��������N����Ŀ��ˮ��

int recursive_search(int a, int b);
int transtion(int a, int b, int *pna, int *pnb, int action);
void print_action();
int **marks;

int main(){

	cin >> Ca >> Cb >> N;
	marks = new int*[Ca+1];
	for (int i = 0; i <= Ca; i++){
		marks[i] = new int[Cb+1];
		for (int j = 0; j <= Cb; j++){
			marks[i][j] = 0;
		}
	}

	if (recursive_search(0, 0) == 1){
		print_action();
		cout << "success\n";
	}else{
		cout << "No solution!!!\n";
	}
	
	for (int i = 0; i <= Ca; i++){
		delete marks[i];
		marks[i] = NULL;
	}
	delete marks;
	marks = NULL;
	return 0;
}

// ��ˮ��Ϊa��b��ʼ���ң����a��b�ѱ����ң�ֱ�ӷ���0
// �������Ҫ�󣬷���1
// ��������ѡ��8����������������������������
// ����ҵ�Ŀ��ֵ�򷵻�1
// ���򽫶���ȡ������
// ���û��һ�������ܷ���1�� �򷵻�0

int recursive_search(int a, int b){
	if (marks[a][b] == 1){
		return 0;
	}
	if (a == N || b == N){
		return 1;
	}
	marks[a][b] = 1;
	for (int action = 0; action < NACTION; action++){
		actions.push_back(action);
		int na, nb;
		transtion(a, b, &na, &nb, action);
		if (recursive_search(na, nb) == 1){
			return 1;
		}
		else{
			actions.pop_back();
		}
	}
	return 0;
}

int transtion(int a, int b, int *pna, int *pnb, int action){
	int ret = -1;
	switch (action){
	case EMPTYA:
		*pna = 0;
		*pnb = b;
		ret = 0;
		break;
	case EMPTYB:
		*pna = a;
		*pnb = 0;
		ret = 0;
		break;
	case FILLA:
		*pna = Ca;
		*pnb = b;
		ret = 0;
		break;
	case FILLB:
		*pna = a;
		*pnb = Cb;
		ret = 0;
		break;
	case POURAB:
		ret = MIN(a, Cb - b);		// ��ʱ����ret
		*pna = a - ret;
		*pnb = b + ret;
		ret = 0;
		break;
	case POURBA:
		ret = MIN(b, Ca - a);		// ��ʱ����ret
		*pna = a + ret;
		*pnb = b - ret;
		ret = 0;
		break;
	default:
		cout << "Warning: transtion, Unknown action\n";
	}
	return ret;
}

void print_action(){
	for (vector<int>::iterator it = actions.begin(); it != actions.end(); it++){
		switch (*it){
		case EMPTYA:
			cout << "empty A\n";
			break;
		case EMPTYB:
			cout << "empty B\n";
			break;
		case FILLA:
			cout << "fill A\n";
			break;
		case FILLB:
			cout << "fill B\n";
			break;
		case POURAB:
			cout << "pour A B\n";
			break;
		case POURBA:
			cout << "pour B A\n";
			break;
		default:
			cout << "Warning: print_action, Unknown action\n";
		}
	}
}