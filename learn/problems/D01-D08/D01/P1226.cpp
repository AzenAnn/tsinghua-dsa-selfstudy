#include<iostream>

using namespace std;
// 反复平方的话，复杂度是O(b)的，b最大有2^31-1
// 必然超时。

long long pow(long long a, long long b ,long long p){
    long long res=1;
    while(b){
        if(b&1){
            res = (res*a)%p;
        }
        a = (a*a) %p;
        b>>= 1;
    }  
    return res;
}

int main  () {
    int a, b ,p ; cin>> a>> b>> p;
    long long res=1;
    // for(int i=1;i<=b;i++){
    //     res =  (res *a )%p;
    // }
    res = pow(a,b,p);
    cout<<a<<"^"<<b<<" mod "<<p<<"="<<res<<'\n';
}

// 需要改变思路 每次把当前的结果平方
// 假设要 乘以b次方
// a*=a 然后a*=a 每一次相当于对自己做平方
// 那么次方次数应该是1 2 4 8 16 也就是等比数列增长
// 最后要增长到b 相当于 求和等于b 或者说把b写为二进制？

