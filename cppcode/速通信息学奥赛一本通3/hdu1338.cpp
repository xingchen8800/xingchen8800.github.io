#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int card[1001];
bool isMine[1001] = {false};

int main() {
    int caseCnt = 0, m, n;
    while(cin >> m >> n) {
        memset(isMine, false, sizeof isMine);
        if(m == 0 && n == 0) break;
        caseCnt++;
        for(int i = 1; i <= n; i++) {
            scanf("%d", &card[i]);
            isMine[card[i]] = true;
        }
        int winCnt = 0, biggerCard = 0;
        for(int i = n * m; i >= 1; i--) {
            if(isMine[i]) {
                if(biggerCard == 0) winCnt++;   //别人没有比“我”当前卡牌大的卡，“我”赢
                else biggerCard--;              //用别人的比“我”当前卡牌大的卡打“我”的卡 
            } else biggerCard++;    //是别人的卡
        }
        printf("Case %d: %d\n", caseCnt, winCnt);
    }
    return 0;
}