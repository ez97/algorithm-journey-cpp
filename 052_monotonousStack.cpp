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
    int largestRectangleArea(vector<int>& heights); // leetcode 84 : 柱状图中最大的矩形 hard
    int maximalRectangle(vector<vector<char>>& matrix); // leetcode 85 : 最大矩形 hard
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

int Solution::largestRectangleArea(vector<int>& heights){
    int n = heights.size();
    vector<int> left(n), right(n, n);
    stack<int> stk;
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && heights[stk.top()] >= heights[i]) { 
            right[stk.top()] = i;
            // 有可能相等，但是不需要更新，不影响结果
            stk.pop();
        }
        left[i] = stk.empty() ? -1 : stk.top();
        stk.push(i);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = std::max(ans, heights[i] * (right[i] - left[i] - 1));
    }
    return ans;
}

int getMax(vector<int> const &height){
    int n = height.size();
    vector<int> left(n, 0);
    vector<int> right(n, 0);
    stack<int> stk;
    for(int i = 0; i < n; i++){
        while(!stk.empty() && height[stk.top()] >= height[i]){
            stk.pop();
        }
        left[i] = stk.empty() ? -1 : stk.top();
        stk.push(i);
    }
    stk = stack<int>(); // 快速清空
    for(int i = n - 1; i >= 0; i--){
        while(!stk.empty() && height[stk.top()] >= height[i]){
            stk.pop();
        }
        right[i] = stk.empty() ? n : stk.top();
        stk.push(i);
    }
    int maxArea = 0;
    for(int i = 0; i < n; i++){
        maxArea = std::max(maxArea, height[i] * (right[i] - left[i] - 1));
    }
    return maxArea;
}

int Solution::maximalRectangle(vector<vector<char>>& matrix){
    int m = matrix.size();
    int n = matrix[0].size();
    int ans = 0;
    vector<int> prefix(n, 0);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            prefix[j] = matrix[i][j] == '1' ? (prefix[j] + 1) : 0;
        }
        ans = std::max(ans, getMax(prefix));
    }
    return ans;
}

// 洛谷P5788 单调栈
int MonotonicStackLuogu(){
    stack<int> stk;
    int n;
    int nums[3000001];
    int ans[3000001];
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &nums[i]);
    }
    for(int i = n; i >= 1; i--){
        while(!stk.empty() && nums[stk.top()] <= nums[i]){
            stk.pop();
        }
        ans[i] = stk.empty() ? 0 : stk.top();
        stk.push(i);
    }
    for(int i = 1; i <= n; i++){
        printf("%d ", ans[i]);
    }
    return 0;
}
