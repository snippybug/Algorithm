/*
* Description:	Given an integer N, you should come up with the mininum nonnegative integer M. M meets the follow condition: M^2 % 10^x = N(x=0, 1, 2, 3...)
* Input:	The first line has an integer T(T <= 1000), the numebr of test cases.
*			For each case, each line contains one integer N(0 <= N <= 10^9), indicating	the given number.
* Output:	For each case output the answer if it exists, otherwise print "None".
*
* Author:	Wang Zonglei
* Date:		2015.7.2
*
*/

#include <iostream>
#include <queue>
#include <math.h>
#include <assert.h>

using namespace std;

// digit[i]��ʾ����ƽ���ĸ�λ����i��һλ����digit[i][0]��ʾ����
int digit[10][3] = {
	1, 0, 0,		// 0
	2, 1, 9,		// 1
	0, 0, 0,		// 2
	0, 0, 0,		// 3
	2, 2, 8,		// 4
	1, 5, 0,		// 5
	2, 4, 6,		// 6
	0, 0, 0,		// 7
	0, 0, 0,		// 8
	2, 3, 7			// 9
};

int get_magnitude(int num){
	assert(num >= 0);
	int magnitude = 10;
	while (num >= magnitude){
		magnitude *= 10;
	}
	return magnitude;
}

int main(){
	int N;		// N��ʾ��������, 0 <= N <= 10^9. int�ͱ�ʾ�ķ�Χ��-2^31~2^31-1(-21 4748 3648 ~ 21 4748 3647��
	cin >> N;
	queue<int> queue;
	int i = 0;

	// �õ�N��������
	int magnitude = get_magnitude(N);
	int bit = N % 10;
	// ȡ����λ����Ȼ�������ڵ�Ԫ�ط������
	while (i < digit[bit][0]){
		i++;
		queue.push(digit[bit][i]);
	}
	while (queue.empty() == false){
		// ÿ�δӶ�����ȡ��һ����T���ж�T^2 % magnitude �Ƿ����N
		// ������ڣ�˵���ҵ��⣬��ӡ�󷵻�
		// ������T�������(�����λ��1λ��λ��)���μ���1~9���õ�TT��Ȼ���ж�TT^2 % level �Ƿ���� N % level������level��ʾTT��������
		// ������ڣ���TT�������
		// �����������
		int T = queue.front();
		queue.pop();
		if ((int)pow(T, 2) % magnitude == N){
			cout << T << '\n';
			return 0;
		}
		else{
			for (int i = 1; i < 10; i++){
				int level = get_magnitude(T);
				int TT = i*level + T;
				level *= 10;
				if ((int)pow(TT, 2) % level == N % level){
					queue.push(TT);
				}
			}
		}
		
	}
	cout << "None\n";
	return 0;
}


