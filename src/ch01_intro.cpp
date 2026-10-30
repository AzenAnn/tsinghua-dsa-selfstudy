// 第1章 绪论：函数的实现。声明和说明见 learn/include/dsa/ch01_intro.h
// 每个函数现在都是 DSA_TODO();，把它换成你的实现。

#include "dsa/ch01_intro.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

namespace dsa::ch01 {

// ---------------- 第 1 天 ----------------

void bubblesort1A(int A[], int n) {
    for(int i = 0;i<n;i++){
        for(int  j =i+1;j<n;j++){ // 这里是i+1开始
            if(A[i] > A[j])std::swap(A[i],A[j]);
        }
    }
}

int countOnes(unsigned int n) {
    int cnt =0;
    while(n){
        cnt += n &1;
        n= n >>1;
    }
    return cnt;
}

int countOnes1(unsigned int n) {
    int cnt= 0;
    while(n){
        n  &=n-1;
        cnt++; 
    }
    return cnt;
}

long long power2BF(int n) {
    long long ans =1;
    for(int i=1;i<=n;i++){
        ans *=2;
    }
    return ans;
}

long long power2(int n) {
    long long ans = 1LL<<n;
    return ans;
}

long long sumI(const int A[], int n) {
    long long ans =0;
    for(int i=0;i<n;i++){
        ans +=A[i];
    }
    return ans;
}

// ---------------- 第 2 天 ----------------

long long sumLinear(const int A[], int n) {
    DSA_TODO();
}

long long sumBinary(const int A[], int lo, int hi) {
    DSA_TODO();
}

void reverseR(int A[], int lo, int hi) {
    DSA_TODO();
}

void reverseI(int A[], int lo, int hi) {
    DSA_TODO();
}

void max2I(const int A[], int lo, int hi, int& x1, int& x2) {
    DSA_TODO();
}

void max2R(const int A[], int lo, int hi, int& x1, int& x2) {
    DSA_TODO();
}

void hanoi(int n, char from, char via, char to, std::vector<std::pair<char, char>>& moves) {
    DSA_TODO();
}

long long fibR(int n) {
    DSA_TODO();
}

long long fibL(int n, long long& prev) {
    DSA_TODO();
}

long long fibI(int n) {
    DSA_TODO();
}

long long gcdEuclid(long long a, long long b) {
    DSA_TODO();
}

long long gcdCN(long long a, long long b) {
    DSA_TODO();
}

int lcsR(const std::string& a, const std::string& b) {
    DSA_TODO();
}

int lcsI(const std::string& a, const std::string& b) {
    DSA_TODO();
}

}  // namespace dsa::ch01
