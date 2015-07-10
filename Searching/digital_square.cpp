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

// digit[i]表示所有平方的个位数是i的一位数，digit[i][0]表示个数
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
	int N;		// N表示给定整数, 0 <= N <= 10^9. int型表示的范围是-2^31~2^31-1(-21 4748 3648 ~ 21 4748 3647）
	cin >> N;
	queue<int> queue;
	int i = 0;

	// 得到N的数量级
	int magnitude = get_magnitude(N);
	int bit = N % 10;
	// 取出个位数，然后将数组内的元素放入队列
	while (i < digit[bit][0]){
		i++;
		queue.push(digit[bit][i]);
	}
	while (queue.empty() == false){
		// 每次从队列中取出一个数T，判断T^2 % magnitude 是否等于N
		// 如果等于，说明找到解，打印后返回
		// 否则在T的最左边(比最高位高1位的位置)依次加上1~9，得到TT，然后判断TT^2 % level 是否等于 N % level，其中level表示TT的数量级
		// 如果等于，将TT放入队列
		// 否则放弃该数
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


