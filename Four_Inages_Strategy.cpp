/* Description:	Young F found a secret record which inherited from ancient times in ancestral home by accident, which named "Four Inages Strategy". 
 *				He couldn't restrain inner exciting, open the record, and read it carefully. " 
 *				Place four magic stones at four points as array element in space, if four magic stones form a square, then strategy activates, destroying enemy around". 
 *				Young F traveled to all corners of the country, and have collected four magic stones finally. He placed four magic stones at four points, but 
 *				didn't know whether strategy could active successfully. So, could you help him? 
 * Input:	Multiple test cases, the first line contains an integer T(no more than 10000), indicating the number of cases. Each test case contains 
 *			twelve integers x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4,representing coordinate of four points. Any pair of points are distinct. 
 * Output:	For each case, the output should occupies exactly one line. The output format is Case #x: ans, here x is the data number begins at 1, 
 *			if your answer is yes,ans is Yes, otherwise ans is No. 
 * Author:	Wang Zonglei
 * Date:	2015.7.5
 *
 */


#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;

struct Point{
	int x;
	int y;
	int z;
	Point(int mx, int my, int mz) :x(mx), y(my), z(mz){}
	Point(){ x = y = z = 0; }
	Point vec(const Point& p);
	int mul(const Point& p);
	double distance(const Point& p);
	bool parallel(const Point& p);
};

double Point::distance(const Point& p){
	return sqrt(pow((x - p.x), 2)+pow((y - p.y), 2)+pow((z - p.z), 2));
}

Point Point::vec(const Point& p){
	return Point(x - p.x, y - p.y, z - p.z);
}

int Point::mul(const Point& p){
	return x*p.x + y*p.y + z*p.z;
}

bool Point::parallel(const Point& p){
	double ratio = 0;
	if (x != 0){
		ratio = (double)p.x / (double)x;
	}
	else if (y != 0){
		ratio = (double)p.y / (double)y;
	}
	else if (z != 0){
		ratio = (double)p.z / (double)z;
	}
	else{
		if (p.x == 0 && p.y == 0 && p.z == 0){
			return true;
		}
		else{
			return false;
		}
	}
	if (p.y == (ratio*y) && p.z == (ratio*z)){
		return true;
	}
	else{
		return false;
	}
}

bool isSquare(Point[4]);

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		Point p[4];
		for (int j = 0; j < 4; j++){
			scanf("%d %d %d", &p[j].x, &p[j].y, &p[j].z);
		}
		// 判断四点是否构成正方形
		cout << "Case: #" << i+1 << ": ";
		if (isSquare(p) == true){
			cout << "Yes";
		}
		else{
			cout << "No";
		}
		cout << '\n';
	}
}

bool isSquare(Point p[4]){
	// 首先从一点出发，算出到其他三个点的距离，必然有两个相等，不为0，且相邻边相互垂直
	double d1, d2, d3;
	Point v1, v2;
	d1 = p[0].distance(p[1]);
	d2 = p[0].distance(p[2]);
	d3 = p[0].distance(p[3]);
	int adj1=-1, adj2=-1, unadj=-1;
	double distance;
	if (d1 == d2){
		adj1 = 1;
		adj2 = 2;
		distance = d1;
		unadj = 3;
	}
	else if (d2 == d3){
		adj1 = 2;
		adj2 = 3;
		unadj = 1;
		distance = d2;
	}
	else if(d1 == d3){
		adj1 = 1;
		adj2 = 3;
		unadj = 2;
		distance = d3;
	}
	else{
		goto fail;
	}
	if (distance == 0){
		goto fail;
	}
	v1 = p[0].vec(p[adj1]);
	v2 = p[0].vec(p[adj2]);
	if (v1.mul(v2) != 0){
		goto fail;
	}
	// 两条边平行
	v1 = p[0].vec(p[adj1]);
	v2 = p[adj2].vec(p[unadj]);
	if (v1.parallel(v2) == true){
		return true;
	}
fail:
	return false;
}
