#include <iostream>
using namespace std;

const int N = 100001;
int n, d[N];
int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> d[i];

    int money = 0, pos = 0, dis = 0;    //有money元钱，最早在pos处负债，走了dis步
    for(int i = 1; i <= n; i++) {
        money += d[i];                  //先收钱/还钱
        if(money >= 0 && pos > 0) {     //当当前的钱不负债，就相当于还清了
            dis += (i - pos) * 2;      //从i走到pos再走回来
            pos = 0;
        } else if(money < 0 && pos == 0) {  //负债了
            pos = i;                        //标记在i处负债(不一定在还不起的那一刻标记)
                                            //因为回去还更前面的可以顺便还
        }
        dis++;                          //向前走
    }
    cout << dis << endl;
    return 0;
}