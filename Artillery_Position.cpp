/*
 * Description:	˾��Ľ����Ǵ�����N*M�������ͼ�ϲ������ǵ��ڱ����ӡ�һ��N*M�ĵ�ͼ��N��M����ɣ���ͼ��ÿһ�������ɽ�أ���"H" ��ʾ����Ҳ������ƽԭ����"P"��ʾ����
 *				��ÿһ��ƽԭ�����������Բ���һ֧�ڱ����ӣ�ɽ���ϲ��ܹ������ڱ����ӣ���һ֧�ڱ������ڵ�ͼ�ϵĹ�����Χ��ͼ�к�ɫ������ʾ�� 
 *				����ڵ�ͼ�еĻ�ɫ����ʶ��ƽԭ�ϲ���һ֧�ڱ����ӣ���ͼ�еĺ�ɫ�������ʾ���ܹ��������������غ������Ҹ��������������¸�����ͼ��������ɫ���������������
 *				��ͼ�Ͽɼ��ڱ��Ĺ�����Χ���ܵ��ε�Ӱ�졣 ���ڣ������ǹ滮��β����ڱ����ӣ��ڷ�ֹ���˵�ǰ���£���֤�κ���֧�ڱ�����֮�䲻�ܻ��๥����
 *				���κ�һ֧�ڱ����Ӷ���������֧�ڱ����ӵĹ�����Χ�ڣ�����������ͼ����������ܹ��ڷŶ����Ҿ����ڱ����ӡ�
 * Input:	��һ�а��������ɿո�ָ�����������ֱ��ʾN��M�� 
 *			��������N�У�ÿһ�к���������M���ַ�('P'����'H')���м�û�пո񡣰�˳���ʾ��ͼ��ÿһ�е����ݡ�N <= 100��M <= 10�� 
 * Output:	��һ�У�����һ������K����ʾ����ܰڷŵ��ڱ����ӵ������� 
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
	int Rows;			// ����
	int Cols;			// ����
	
	Rows = 5;
	Cols = 4;
	int *mask;			// ���ε����룬0��ʾɽ�أ�1��ʾƽԭ
	mask = new int[Rows];
	mask[0] = 0xb;
	mask[1] = 0xc;
	mask[2] = 0xf;
	mask[3] = 0xa;
	mask[4] = 0x9;

	// F[i][j][k]��ʾ��i��״̬Ϊj����i-1��״̬Ϊkʱ�������ڱ�����
	int nstatus = 1 << Cols;
	int ***F;
	F = new int**[Rows];
	for (int i = 0; i < Rows; i++){
		F[i] = new int*[nstatus];
		for (int j = 0; j < nstatus; j++){
			F[i][j] = new int[nstatus];
		}
	}

	// ��ʼ����һ��
	for (int i = 0; i < nstatus; i++){
		int c;
		if (judge(i, Cols) == false	// һ����û�г�ͻ
			&& (i&mask[0]) == i)			// ������γ�ͻ
			{
			c = count(i, Cols);				// �ڱ��ĸ���
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
			if (judge(i, Cols) == false			// һ����û�г�ͻ
				&& (i&mask[row])==i){			// ������γ�ͻ
				int c;
				for (int j = 0; j < nstatus; j++){
					if ((i&j) == 0){				// ������һ�г�ͻ
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

// �ж�һ���ڵ��ڱ�λ���Ƿ��ͻ��"��"����true��"����"����false
// �ж��Ƿ��м��<=2��1
bool judge(int status, int n){
	assert(n <= 10);
	int a[5];
	status &= (1 << n) - 1;
	if ((status & 3) == 3){		// ����λΪ1
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

// ͳ���ڱ�������(��1�ĸ���)
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