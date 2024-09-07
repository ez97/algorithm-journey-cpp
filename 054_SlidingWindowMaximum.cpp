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
    vector<int> maxSlidingWindow(vector<int>& nums, int k); // leetcode 239 : 滑动窗口最大值 hard
};

int main(){
    return 0;
}

vector<int> maxSlidingWindow(vector<int>& nums, int k){
    deque<int> dq;
    int left = 0;
    int right = k;
    for(int i = 0; i < k; i++){
        while(!dq.empty() && nums[dq.front()] <= nums[i]){
            dq.pop_front();
        }
        dq.push_front(i);
    }
    vector<int> ans;
    ans.push_back(nums[dq.back()]);
    for(int i = 0; i + k - 1 < nums.size(); i++){
        int right = i + k;
        int left = i;
        while(!dq.empty() && nums[dq.front()] <= nums[right]){
            dq.pop_front();
        }
        if(!dq.empty() && left == dq.back()){
            dq.pop_back();
        }
        dq.push_front(right);
        ans.push_back(nums[dq.back()]);
    }
    return ans;
}