#include <bits/stdc++.h>
using namespace std;

int getOneNum(int x) {      //获取x中1的数量
	int num = 0;            
	while(x) {
		num += (x % 2 == 1);//拆分成二进制数
		x /= 2;
	}
	return num;
}

int main() {
	int i;

    while(cin >> i && i != 0) {
        int num = getOneNum(i++);
        for(;getOneNum(i) != num; i++);
        cout << i << endl; 
	}
	return 0;
}