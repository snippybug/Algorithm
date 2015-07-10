/*
 * Description:	Xiaoqiang entered the "shortest code" challenge organized by some self-claimed astrologists. He was given a boolean function taking n
 *				inputs (in C++):
 *				bool f(bool x1, bool x2, bool x3){
 *				// your code here
 *				// return something
 *				}
 *				All possible inputs and expected outputs of this function have been revealed
 *				x1	x2	x3	f
 *				0	0	0	0
 *				0	0	1	0
 *				0	1	0	0
 *				0	1	1	1
 *				1	0	0	0
 *				1	0	1	0
 *				1	1	0	1
 *				1	1	1	1
 *				Xiaoqiang's code must be like:
 *				bool a = NAND(b, c);	// NAND(b, c) = !(b&&c)
 *				After starting at the function for a while, Xiaoqiang came up with the answer:
 *				bool a = NAND(x1, x2);
 *				bool b = NAND(x2, x3);
 *				bool y = NAND(a,b);
 *				return y;
 *				Xiaoqiang wants to make sure that his solution is the shortest possible. Can you help him?
 * Input:	The first line contains an integer T(T <= 20) denoting the number of test cases.
 *			For each test case, there is one line containing 8 characters encoding the truth table of the function.
 * Output:	For each of the case, output a single line containing the mininum number of lines Xiaoiang has to write.
 *
 * Author:	Wang Zonglei
 * Date:	2015.7.2
 *
 */

#include <iostream>
#include <queue>

const int SIZE = 256;

using namespace std;

struct Status{
	unsigned char value;
	int level;
	Status(unsigned char v, int l){
		value = v;
		level = l;
	}
};

int main(){
	bool flag[SIZE] = { false };				// 判断是否已被检查
	unsigned char x[3] = { 0x0f, 0x33, 0x55 };	// 初始状态, 0x0f代表return x1，0x33代表return x2，0x55代表return x3的真值表

	char buf[10] = { 0 };
	cin.getline(buf, 10);
	unsigned char obj_val = 0;
	// 将字符串转化为二进制值
	int i;
	for (i = 0; i < 7; i++){
		if (buf[i] == '1'){
			obj_val |= 1;
		}
		obj_val = obj_val << 1;
	}
	if (buf[i] == '1'){
		obj_val |= 1;
	}

	queue<Status> queue;
	for (int i = 0; i < 3; i++){
		queue.push(Status(x[i], 1));
		flag[x[i]] = true;
	}
	
	while (queue.empty() == false){
		// 从队列中取出真值后，检查是否与目标相同
		// 如果相同，说明找到结果，打印层数后返回，
		// 否则，置标志位，与x[0]~x[2]进行与非操作生成新的真值，如果真值还没有出现过(flag=false)，则将层数加1后放入队列
		Status s(0, 0);
		s = queue.front();
		queue.pop();
		if (s.value == obj_val){
			cout << s.level << '\n';
			return 0;
		}
		flag[s.value] = true;
		for (int i = 0; i < 3; i++){
			unsigned char nv = ~(s.value & x[i]);
			if (flag[nv] == false){
				queue.push(Status(nv, s.level + 1));
			}
		}
	}
	cout << "No Solution!!!\n";
	return 0;
}
