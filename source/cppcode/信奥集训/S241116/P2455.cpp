// #include <iostream>
// #include <cstring>
// #include <cstdio>
// #include <map>
// using namespace std;

// // 快速读入
// namespace FastIO {
//     inline int read() {
//         int s = 0, f = 1;
//         char t = getchar();
//         while ('0' > t || t > '9') {
//             if (t == '-') f = -1;
//             t = getchar();
//         }
//         while ('0' <= t && t <= '9') {
//             s = (s << 1) + (s << 3) + t - '0';
//             t = getchar();
//         }
//         return s * f;
//     }
// }
// using FastIO::read;

// const int N = 105;
// const double eps = 1e-7;
// double A[N][N], X[N];  // A为增广矩阵,X为解
// int n;  // 方程个数

// // 判断浮点数与0的关系
// double dcmp(double x) {
//     if (x > eps) return 1;
//     return x < -eps ? -1 : 0;
// }

// // 判断两个浮点数是否相等
// bool equal(double a, double b) {
//     return dcmp(a - b) == 0;
// }

// // 判断方程组是否无解
// /*
// 如果某一行都是0，且等号右边不为0，则无解
// */
// bool noSolution() {
//     for (int i = 1; i <= n; i++) {
//         bool allZero = true;
//         for (int j = 1; j <= n; j++) {
//             if (dcmp(A[i][j]) != 0) {
//                 allZero = false;
//                 break;
//             }
//         }
//         if (allZero && dcmp(A[i][n + 1])) return true;
//     }
//     return false;
// }

// // 高斯消元
// void Gauss() {
//     int r = 0; 
//     for (int i = 1; i <= n; i++) {
//         int pos = -1;
//         for (int j = r + 1; j <= n; j++) {
//             if (dcmp(A[j][i]) != 0) {
//                 pos = j;
//                 break;
//             }
//         }

//         if (pos == -1) continue;    //一列都是零
//         swap(A[pos], A[++r]);  // 保证第r个方程的第i列系数是非0的
        
//         for (int j = r + 1; j <= n; j++) {  // 用第r个方程对第r+1~n个方程做消元
//             double c = A[j][i] / A[r][i];
//             for (int k = i; k <= n + 1; k++) {
//                 A[j][k] -= A[r][k] * c;
//             }
//         }
//     }

//     if (r < n) {  // 非标准阶梯
//         if (noSolution()) cout << "-1\n";
//         else cout << "0\n";
//         return;
//     }
    
//     // 标准倒三角阶梯，从后往前回代
//     for (int i = n; i >= 1; i--) {
//         for (int j = i + 1; j <= n; j++) {
//             A[i][n + 1] -= X[j] * A[i][j];
//         }
//         X[i] = A[i][n + 1] / A[i][i];
//     }
    
//     for (int i = 1; i <= n; i++) {
//         printf("x%d=%.2lf\n", i, X[i]);
//     }
// }

// int main() {
//     n = read();
//     for (int i = 1; i <= n; i++) {
//         for (int j = 1; j <= n + 1; j++) {
//             A[i][j] = read();
//         }
//     }
//     Gauss();
//     return 0;
// }

#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
using namespace std;

// 快速读入
namespace FastIO {
    inline int read() {
        int s = 0, f = 1; // s为读取的数字，f为符号（1或-1）
        char t = getchar(); // 读取字符
        // 跳过非数字字符
        while ('0' > t || t > '9') {
            if (t == '-') f = -1; // 处理负号
            t = getchar(); // 继续读取
        }
        // 读取数字
        while ('0' <= t && t <= '9') {
            s = (s << 1) + (s << 3) + t - '0'; // 将字符转换为数字
            t = getchar(); // 继续读取
        }
        return s * f; // 返回最终的数字
    }
}
using FastIO::read;

const int N = 105; // 最大方程个数
const double eps = 1e-7; // 浮点数比较的精度
double A[N][N], X[N];  // A为增广矩阵，X为解
int n;  // 方程个数

// 判断浮点数与0的关系
double dcmp(double x) {
    if (x > eps) return 1; // x大于eps，返回1
    return x < -eps ? -1 : 0; // x小于-eps，返回-1，否则返回0
}

// 判断两个浮点数是否相等
bool equal(double a, double b) {
    return dcmp(a - b) == 0; // 如果a与b的差值接近于0，则认为相等
}

// 判断方程组是否无解
/*
如果某一行都是0，且等号右边不为0，则无解
*/
bool noSolution() {
    for (int i = 1; i <= n; i++) { // 遍历每个方程
        bool allZero = true; // 假设当前行全为0
        for (int j = 1; j <= n; j++) { // 检查当前行的系数
            if (dcmp(A[i][j]) != 0) { // 如果有非零系数
                allZero = false; // 当前行不是全零
                break; // 退出内层循环
            }
        }
        // 如果当前行全为0且等号右边不为0，则无解
        if (allZero && dcmp(A[i][n + 1])) return true;
    }
    return false; // 否则有解
}

// 高斯消元
void Gauss() {
    int r = 0; // 当前行数
    for (int i = 1; i <= n; i++) { // 遍历每一列
        int pos = -1; // 找到非零元素的行
        for (int j = r + 1; j <= n; j++) { // 从当前行的下一行开始查找
            if (dcmp(A[j][i]) != 0) { // 找到非零元素
                pos = j; // 记录该行
                break; // 退出循环
            }
        }

        if (pos == -1) continue; // 如果该列全为零，继续下一列
        swap(A[pos], A[++r]);  // 将找到的非零行与当前行交换，保证第r个方程的第i列系数是非0的
        
        // 用第r个方程对第r+1~n个方程做消元
        for (int j = r + 1; j <= n; j++) {
            double c = A[j][i] / A[r][i]; // 计算消元系数
            for (int k = i; k <= n + 1; k++) { // 更新当前行
                A[j][k] -= A[r][k] * c; // 消去第j行的第i列
            }
        }
    }

    // 检查是否为非标准阶梯
    if (r < n) {  
        if (noSolution()) cout << "-1\n"; // 无解
        else cout << "0\n"; // 有无穷多解
        return;
    }
    
    // 标准倒三角阶梯，从后往前回代
    for (int i = n; i >= 1; i--) {
        for (int j = i + 1; j <= n; j++) {
            A[i][n + 1] -= X[j] * A[i][j]; // 更新增广矩阵
        }
        X[i] = A[i][n + 1] / A[i][i]; // 计算当前变量的值
    }
    
    // 输出结果
    for (int i = 1; i <= n; i++) {
        printf("x%d=%.2lf\n", i, X[i]); // 输出每个变量的值
    }
}

int main() {
    n = read(); // 读取方程个数
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            A[i][j] = read(); // 读取增广矩阵
        }
    }
    Gauss(); // 调用高斯消元函数
    return 0;
}