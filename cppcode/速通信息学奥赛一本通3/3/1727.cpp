#include <iostream>
using namespace std;

char num, op;
long long And = 0, Or = 0;

bool func(bool isDuanLu = false) {
    cin >> num;
    if(num == '(') {
        return func();
    } else {
        cin >> op;
        if(op == '&') {
			And += !isDuanLu;
            switch(num) {
                case '0' : {
                    return false & func(true);
                   	break;
                }
                case '1': {
                    return true & func(true);
                    break;
                }
            }
        } else if(op == '|') {
            Or += !isDuanLu;
            switch(num) {
                case '0' : {
                    return false | func(true);
                   	break;
                }
                case '1': {
                    return true | func(true);
                    break;
                }
            }
        } else {
            return func();
        }
    }
}

int main() {
    cout << func() << endl << And << " " << Or << endl;
    return 0;
}