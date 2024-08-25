#include <bits/stdc++.h>
#include <cstring>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int> &nums); // leetcode 209 : 长度最小的子数组 medium
    int lengthOfLongestSubstring(string s); // leetcode 3 : 无重复字符的最长子串 medium
    string minWindow(string s, string t); // leetcode 76 : 最小覆盖子串 hard
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost); // leetcode 134 : 加油站 medium
    int balancedString(string s); // leetcode 1234 : 替换子串得到平衡字符串 medium
    int subarraysWithKDistinct(vector<int>& nums, int k); // leetcode 992 : K 个不同整数的子数组 hard
    int longestSubstring(string s, int k); // leetcode 395 : 至少有 K 个重复字符的最长子串 medium
};

// 滑动窗口的关键在于单调性
// 最小类问题遍历并定死起点，逐个向后检查终点；最大类问题遍历并定死终点，逐个向后检查起点
// 后两道比较难的题，都是将非单调问题拆成单调的子问题

int main(){
    return 0;
}

int Solution::minSubArrayLen(int target, vector<int> &nums){
    int ans = INT_MAX;
    int start = 0;
    int end = 0;
    int sum = 0;
    while (end < nums.size()) {
        while (sum < target && end < nums.size()) {
            sum += nums[end];
            end++;
        }
        while (sum - nums[start] >= target && start < nums.size()) {
            sum -= nums[start];
            start++;
        }
        if (sum >= target) {
            //cout << start << " " << end << " " << sum << endl;
            ans = std::min(ans, end - start);
        }
        sum -= nums[start++];
    }
    if (ans == INT_MAX) {
        return 0;
    }
    return ans;
}

int Solution::lengthOfLongestSubstring(string s){
    unordered_set<char> hash;
    int len = s.size();
    int right = 0;
    int ans = 0;
    for(int i = 0; i < len; i++){
        if(i != 0){
            hash.erase(s[i - 1]);
        }
        while(right < len && !hash.count(s[right])){
            hash.insert(s[right++]);
        }
        ans = std::max(ans, right - i);
    }
    return ans;
}

string minWindow(string s, string t){
    unordered_map<char, int> hash;
    int left = 0;
    int right = 0; 
    int len1 = s.size();
    int len2 = t.size();
    for(int i = 0; i < len2; i++){
        hash[t[i]]++;
        while(right < len1 && hash[t[i]] > 0){
            hash[s[right]]--;
            right++;
        }
        if(hash[t[i]] > 0){
            return string();
        }
    }
    int minlen = INT_MAX;
    string ret;
    while(left < len1){
        while(left < len1 && hash[s[left]] < 0){
            hash[s[left]]++;
            left++;
        }
        if(right - left < minlen){
            ret = s.substr(left, right - left);
            minlen = right - left;
        }
        hash[s[left]]++;
        while(right < len1 && hash[s[left]] > 0){
            hash[s[right]]--;
            right++;
        }
        if(hash[s[left]] > 0){
            break;
        }
        left++;
    }
    
    return ret;
}

int Solution::canCompleteCircuit(vector<int>& gas, vector<int>& cost){
    int len = gas.size();
    int end = 0;
    int oil = 0;
    for(int i = 0; i < len; i++){
        if(i != 0){
            oil = oil - gas[i - 1] + cost[i - 1];
        }
        if(oil < 0){
            continue;
        }
        while(end - i < len && (oil + gas[end % len] - cost[end % len] >= 0)){
            oil = oil + gas[end % len] - cost[end % len];
            end++;
        }
        if(end - i == len){
            return i;
        }
    }
    return -1;
}

int Solution::balancedString(string s){
    vector<int> chs(4, 0);

    for(auto ch : s){
        if(ch == 'Q'){
            chs[0]++;
        }
        else if(ch == 'W'){
            chs[1]++;
        }
        else if(ch == 'E'){
            chs[2]++;
        }
        else{
            chs[3]++;
        }
    }
    int len = s.size();
    int ans = INT_MAX;
    int end = 0;

    auto check = [&](){
        for(auto n : chs){
            if(n > len/4){
                return false;
            }
        }
        return true;
    };

    for(int i = 0; i < len; i++){
        if(i != 0){
            char ch = s[i-1];
            if(ch == 'Q'){
                chs[0]++;
            }
            else if(ch == 'W'){
                chs[1]++;
            }
            else if(ch == 'E'){
                chs[2]++;
            }
            else{
                chs[3]++;
            }
        }
        while(!check() && end < len){
            char ch = s[end];
            if(ch == 'Q'){
                chs[0]--;
            }
            else if(ch == 'W'){
                chs[1]--;
            }
            else if(ch == 'E'){
                chs[2]--;
            }
            else{
                chs[3]--;
            }
            end++;
        }
        if(check()){
            ans = std::min(ans, end - i);
        }
    }
    return ans;
}

int subarraysLessKDistinct(vector<int>& nums, int k){
    int types = 0;
    int hash[20001] = {};
    int cnt = 0;
    int left = 0;
    int len = nums.size();
    for(int i = 0; i < len; i++){
        hash[nums[i]]++;
        if(hash[nums[i]] == 1){
            types++;
        }
        while(types > k){
            if(hash[nums[left]] == 1){
                types--;
            }
            hash[nums[left]]--;
            left++;
        }
        cnt += i - left;
    }
    return cnt;
}

int Solution::subarraysWithKDistinct(vector<int>& nums, int k){
    return subarraysLessKDistinct(nums, k) - subarraysLessKDistinct(nums, k-1);
}

int Solution::longestSubstring(string s, int k){
    int hash[256];
    int ans = 0;
    for(int require = 1; require <= 26; require++){
        memset(hash, 0, sizeof(int) * 256);
        for(int l = 0, r = 0, types = 0, satisfy = 0; r < s.size(); r++){
            hash[s[r]]++;
            if(hash[s[r]] == 1){
                types++;
            }
            if(hash[s[r]] == k){
                satisfy++;
            }

            while(types > require){
                if(hash[s[l]] == 1){
                    types--;
                }
                if(hash[s[l]] == k){
                    satisfy--;
                }
                hash[s[l++]]--;
            }

            if(satisfy == require){
                ans = std::max(ans, r - l + 1);
            }
        }
    }
    return ans;
}