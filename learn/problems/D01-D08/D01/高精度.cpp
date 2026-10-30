#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 高精度乘法：C = A * B
vector<int> mul(vector<int>& A, vector<int>& B) {
    // 结果的最大位数为 A的长度 + B的长度
    vector<int> C(A.size() + B.size(), 0); 
    
    // 1. 核心乘法：模拟竖式乘法
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B.size(); j++) {
            // 注意：A和B是逆序存储的，所以 i+j 就是结果对应的位置
            C[i + j] += A[i] * B[j]; 
        }
    }
    
    // 2. 统一处理进位
    int t = 0; // t 代表进位
    for (int i = 0; i < C.size(); i++) {
        t += C[i];       // 加上当前位置原本的数
        C[i] = t % 10;   // 当前位保留个位
        t /= 10;         // 进位到高位
    }
    
    // 3. 去除前导零（例如 0 * 123 会算出 000）
    while (C.size() > 1 && C.back() == 0) {
        C.pop_back();
    }
    
    return C;
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    
    vector<int> A, B;
    // 4. 字符串转数组（必须【逆序】存储，让个位在 index 0）
    for (int i = s1.size() - 1; i >= 0; i--) A.push_back(s1[i] - '0');
    for (int i = s2.size() - 1; i >= 0; i--) B.push_back(s2[i] - '0');
    
    auto C = mul(A, B);
    
    // 5. 逆序输出结果
    for (int i = C.size() - 1; i >= 0; i--) {
        cout << C[i];
    }
    cout << endl;
    
    return 0;
}