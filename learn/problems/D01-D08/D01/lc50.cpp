// 小数快速幂

class Solution {
public:
    double myPow(double x, int n) {
        double res = 1.0;
        long long N = n; // 1. 用 long long 接管，防止 n = INT_MIN 时取反溢出
        
        // 2. 处理负数指数的情况
        if (N < 0) {
            x = 1 / x;
            N = -N; // 此时 N 是 long long，不会溢出
        }
        
        while (N > 0) {
            if (N & 1) { // 如果最低位是 1
                res = res * x;
            }
            x = x * x;   // 底数平方
            N >>= 1;     // 指数右移（或者写 N /= 2 也可以）
        }
        
        return res;
    }
};