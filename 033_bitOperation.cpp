// 033 : https://www.bilibili.com/video/BV1up4y1g7d8
#include <bits/stdc++.h>
#include <iostream>

int bitadd(int a, int b){
    int ans = a;
    while(b != 0){
        ans = a ^ b;
        b = (a & b) << 1;
        a = ans;
    }
    return ans;
}

int main(){
    int a = 1919810;
    int b = 114514;
    std::cout << a + b << std::endl;
    std::cout << bitadd(a, b) << std::endl;
    return 0;
}