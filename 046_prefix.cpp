#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>

using namespace std;

// leetcode 303 : 区域和检索 - 数组不可变 easy
class NumArray {
private:
    vector<int> prefix;
public:
    NumArray(vector<int>& nums) {
        int sum = 0;
        for(int i = 0; i < nums.size(); i++){
            sum += nums[i];
            prefix.push_back(sum);
        }
    }
    
    int sumRange(int left, int right) {
        return prefix[right] - ((left == 0) ? 0 : prefix[left - 1]);
    }
};

// newcoder CD9 : 未排序数组中累加和为给定值的最长子数组长度 easy
void LongestSubarraySumEqualsAim(){
    int N, k;
    vector<int> prefix(1, 0);
    unordered_map<int, int> HashMap;
    HashMap[0] = -1;
    int sum = 0;
    int ans = 0;
    cin >> N >> k;
    for(int i = 0; i < N; i++){
        int tmp;
        cin >> tmp;
        sum += tmp;
        prefix.push_back(sum);
        if(!HashMap.count(sum)){
            HashMap[sum] = i;
        }
        if(HashMap.count(sum - k)){
            ans = std::max(ans, i - HashMap[sum - k]);
        }
    }
    cout << ans;
}

class Solution {
public:
    int subarraySum(vector<int>& nums, int k);// leetcode 560 : 和为 K 的子数组 medium
    int longestWPI(vector<int>& hours); // leetcode 1124 : 表现良好的最长时间段 medium
    int minSubarray(vector<int>& nums, int p); // leetcode 1590 : 使数组和能被 P 整除 medium
    int findTheLongestSubstring(string s); // leetcode  1371 : 每个元音包含偶数次的最长子字符串 medium
};

int Solution::subarraySum(vector<int>& nums, int k){
    unordered_map<int, int> HashMap;
    HashMap[0] = 1;
    int sum = 0;
    int cnt = 0;
    for (int i = 0; i < nums.size(); i++) {
        sum += nums[i];
        if (HashMap.count(sum - k)) {
            cnt += HashMap[sum - k];
        }
        HashMap[sum]++;
    }
    return cnt;
}

// nowcoder CD10 : 未排序数组中累加和为给定值的最长子数组系列问题补1 easy

void PositivesEqualsNegtivesLongestSubarray(){
    unordered_map<int, int> HashMap;
    HashMap[0] = -1;
    int n;
    cin >> n;
    int pos = 0;
    int ans = 0;
    for(int i = 0; i < n; i++){
        int tmp;
        cin >> tmp;
        if(tmp > 0){
            pos++;
        }
        else if(tmp < 0){
            pos--;
        }
        if(HashMap.count(pos)){
            ans = std::max(ans, i - HashMap[pos]);
        }
        else{
            HashMap[pos] = i;
        }
    }
    cout << ans;
}

int Solution::longestWPI(vector<int>& hours){
    unordered_map<int, int> HashMap;
    HashMap[0] = -1;
    int ans = 0;
    int tired = 0;
    for (int i = 0; i < hours.size(); i++) {
        tired += hours[i] > 8 ? 1 : -1;
        if (tired > 0) {
            ans = std::max(ans, i + 1);
        } else {
            if (HashMap.count(tired - 1)) {
                ans = std::max(ans, i - HashMap[tired - 1]);
            }
        }
        if (!HashMap.count(tired)) {
            HashMap[tired] = i;
        }
    }
    return ans;
}

int Solution::minSubarray(vector<int>& nums, int p){
    int target = 0;
    for (auto num : nums) {
        target += num % p;
        target = target % p;
    }

    unordered_map<int, int> HashMap;
    HashMap[0] = -1;
    int rem = 0;
    int sublen = nums.size();
    cout << target << endl;
    for (int i = 0; i < nums.size(); i++) {
        rem = (rem + nums[i] % p) % p;
        int search = (rem - target + p) % p;
        HashMap[rem] = i;
        if (HashMap.count(search)) {
            sublen = std::min(sublen, i - HashMap[search]);
        }
        
    }
    return (sublen == nums.size()) ? -1 : sublen;
}

int Solution::findTheLongestSubstring(string s) {
    for(int i = 0; i < s.size(); i++){
        int ans = 0, status = 0, n = s.length();
        vector<int> pos(1 << 5, -1);
        pos[0] = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'a') {
                status ^= 1<<0;
            } else if (s[i] == 'e') {
                status ^= 1<<1;
            } else if (s[i] == 'i') {
                status ^= 1<<2;
            } else if (s[i] == 'o') {
                status ^= 1<<3;
            } else if (s[i] == 'u') {
                status ^= 1<<4;
            }
            if (~pos[status]) {
                ans = max(ans, i + 1 - pos[status]);
            } else {
                pos[status] = i + 1;
            }
        }
        return ans;
    }
}