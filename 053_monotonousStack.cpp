#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <cstdio>
#include <numeric>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    int maxWidthRamp(vector<int>& nums); // leetcode 962 : 最大宽度坡 medium
    string removeDuplicateLetters(string s); // leetcode 316 : 去除重复字母 medium
    int totalSteps(vector<int>& nums); // leetcode 2289 : 使数组按非递减顺序排列 medium
    int numSubmat(vector<vector<int>>& mat); // leetcode 1504 : 统计全 1 子矩形 medium
};

int main(){
    return 0;
}

int Solution::maxWidthRamp(vector<int>& nums){
    int n = nums.size();
    int ans = 0;
    stack<int> stk;
    for(int i = 0; i < n; i++){
        if(stk.empty() || nums[stk.top()] > nums[i]){
            stk.push(i);
        }
    }
    for(int i = n - 1; i >= 0; i--){
        int curr = i;
        while(!stk.empty() && nums[stk.top()] <= nums[i]){
            curr = stk.top();
            stk.pop();
        }
        ans = std::max(ans, i - curr);
    }
    return ans;
}

string Solution::removeDuplicateLetters(string s){
    string stk;
    int n = s.size();
    vector<int> cnt(26, 0);
    vector<int> vis(26, 0);
    for(auto ch : s){
        cnt[ch - 'a']++;
    }
    for(int i = 0; i < n; i++){
        cnt[s[i] - 'a']--;
        if(vis[s[i] - 'a'] == 1){
            continue;
        }
        while(!stk.empty() && cnt[stk.back() - 'a'] > 0 && stk.back() > s[i]){
            vis[stk.back() - 'a'] = 0;
            stk.pop_back();
        }
        vis[s[i] - 'a'] = 1;
        stk.push_back(s[i]);
    }
    return stk;
}

int Solution::totalSteps(vector<int>& nums){
    return 0;
    // TODO
}

int Solution::numSubmat(vector<vector<int>>& mat){
    return 0;
    // TODO
}