#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <cstdio>
#include <numeric>
#include <stack>
#include <vector>
using namespace std;


class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures); // leetcode 739 : 每日温度 medium
    int sumSubarrayMins(vector<int>& arr); // leetcode 907 : 子数组的最小值之和 medium
};

int main(){

}

// newcoder CD188 : 单调栈进阶 中等
int LeftRightLess(){
    int n;
    cin >> n;
    array<int, 1000001> nums;
    array<array<int, 2>, 1000001> ans;
    stack<pair<int, int>> stk;
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        while (!stk.empty() && stk.top().second >= nums[i]) {
            ans[stk.top().first][1] = i;
            stk.pop();
        }
        if (stk.empty()) {
            ans[i][0] = -1;
        } else {
            ans[i][0] = stk.top().first;
        }
        stk.push({i, nums[i]});
    }
    while (!stk.empty()) {
        int pos = stk.top().first;
        ans[pos][1] = -1;
        stk.pop();
        if(!stk.empty()){
            ans[stk.top().first][1] = pos;
        }
    }
    for(int i = n - 2; i >= 0; i--){
        while(ans[i][1] != -1 && nums[ans[i][1]] == nums[i]){
            ans[i][1] = ans[ans[i][1]][1];
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", ans[i][0], ans[i][1]);
    }
    return 0;
}

vector<int> Solution::dailyTemperatures(vector<int>& temperatures){
    stack<int> stk;
    int n = temperatures.size();
    vector<int> answer(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        while (!stk.empty() && temperatures[stk.top()] <= temperatures[i]) {
            stk.pop();
        }
        if (!stk.empty()) {
            answer[i] = stk.top() - i;
        } else {
            answer[i] = 0;
        }
        stk.push(i);
    }
    return answer;
}

int Solution::sumSubarrayMins(vector<int>& arr){
        array<array<int, 2>, 30001> pos;
        stack<int> stk;
        int n = arr.size();
        for (int i = 0; i < n; i++) {
            while (!stk.empty() && arr[stk.top()] > arr[i]) {
                //cout << "pos = " << stk.top() << ", right = " << i << endl;
                pos[stk.top()][1] = i; // maybe equal
                stk.pop();
            }
            if (stk.empty()) {
                pos[i][0] = -1;
            } else {
                pos[i][0] = stk.top();
            }
            stk.push(i);
        }
        while (!stk.empty()) {
            pos[stk.top()][1] = n;
            int tmp = stk.top();
            stk.pop();
            if (!stk.empty()) {
                pos[stk.top()][1] = tmp;
            }
        }
        /*for(int i = 0; i < n; i++){
            cout << "(" << pos[i][0] << ", " << pos[i][1] << ") ";
        }
        cout << endl;*/
        for(int i = n - 2; i >= 0; i--) {
            while (pos[i][1] != -1 && pos[i][1] != n && arr[i] == arr[pos[i][1]]) {
                pos[i][1] = pos[pos[i][1]][1];
            }
        }
        /*for(int i = 0; i < n; i++){
            cout << "(" << pos[i][0] << ", " << pos[i][1] << ") ";
        }
        cout << endl;*/

        int ans = 0;
        long long mod = 1e9 + 7;
        for (int i = 0; i < n; i++) {
            long long cnt = (i - pos[i][0]) * (pos[i][1] - i);
            //cout << cnt << " ";
            ans = (ans + (long long)(cnt * arr[i])) % mod;
        }
        //cout << endl;
        return ans;
}