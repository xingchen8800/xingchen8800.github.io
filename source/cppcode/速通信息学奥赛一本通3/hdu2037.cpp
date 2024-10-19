#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

vector< pair<int, int> > line;

bool cmp(pair<int, int>& a, pair<int, int>& b) {
	return a.second < b.second;
}

int main() {
	int n;
	while(cin >> n && n != 0) {
        line.clear();
		for(int i = 1; i <= n; i++) {
			int x, y; cin >> x >> y;
			line.push_back({x, y});	
		}
		
		sort(line.begin(), line.end(), cmp);
		
		int x = line.begin()->second, sum = 1;    //x记录上个节目的结束时间
		for(auto i : line) {
			if(x <= i.first) {  //当上一个的结束时间在这个节目之前，可以看的节目加一
				sum++;
				x = i.second; 
			}
		}
		cout << sum << endl;
	}
	return 0;
}