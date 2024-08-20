#include <bits/stdc++.h>

class Solution {
public:
    int gcd(int a, int b);
    int lcm(int a, int b);

    int nthMagicalNumber(int n, int a, int b); // leetcode 878 : 第N个神奇数字 hard
};


int main(){
    return 0;
}

int Solution::nthMagicalNumber(int n, int a, int b){
    long long int ll = lcm(a, b);
    long long int ans = 0;
    for(long long int l = 0, r = (long long int)n * std::min(a, b), m = 0; l <= r;){
        m = l + (r - l) / 2;
        if(m / a + m / b - m / ll >= n){
            ans = m;
            r = m - 1;
        }
        else{
            l = m + 1;
        }
    }
    return (int ) (ans % 1000000007);
}

int Solution::gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

int Solution::lcm(int a, int b){
    return a / gcd(a, b) * b;
}
