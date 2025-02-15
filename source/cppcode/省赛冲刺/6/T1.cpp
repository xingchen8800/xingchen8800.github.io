#include <iostream>
using namespace std;

int main() {
    int d, h, m;
    cin >> d >> h >> m;

    int start_day = 11, start_hour = 11, start_minute = 11;
    int start_min = (start_day * 24 * 60) + (start_hour * 60) + start_minute;
    int end_min = (d * 24 * 60) + (h * 60) + m;
    int wait_time = end_min - start_min;
    if (wait_time < 0) 
        cout << -1 << endl;
    else 
        cout << wait_time << endl;

    return 0;
}