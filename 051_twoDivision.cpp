#include <algorithm>
#include <bits/stdc++.h>
#include <numeric>
#include <vector>
using namespace std;

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h); // leetcode 875 : 爱吃香蕉的珂珂 medium
    int splitArray(vector<int>& nums, int k); // leetcode 410 : 分割数组的最大值 hard
    int smallestDistancePair(vector<int>& nums, int k); // leetcode 719 : 找出第 K 小的数对距离 hard
    long long maxRunTime(int n, vector<int>& batteries); // leetcode 2141 : 同时运行 N 台电脑的最长时间 hard
    int WaitingTime(vector<int>& nums, int m); // 计算等位时间
    int CutOrPoison(vector<int>& nums, vector<int>& poisons, int hp);
};

int main(){
    return 0;
}

int Solution::minEatingSpeed(vector<int>& piles, int h){
    int low = 1;
    int high = 0;
    for (auto pile : piles) {
        high = std::max(high, pile);
    }
    high = high / (h / piles.size()) + 1;
    int ans = 0;
    while (low < high) {
        int time = 0;
        int mid = low + (high - low) / 2;
        for (auto pile : piles) {
            time += (pile + mid - 1) / mid;
        }
        if (time > h) {
            low = mid + 1;
        } else {
            ans = mid;
            high = mid;
        }
    }
    return low;
}

int Solution::splitArray(vector<int>& nums, int k){
    int left = 0;
    int right = 0;
    for (auto num : nums) {
        right += num;
        left = std::max(left, num);
    }
    int len = nums.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        int ptr = 0;
        int cnt = 0;
        int sum = 0;
        while (ptr < len) {
            if (sum + nums[ptr] <= mid) {
                sum += nums[ptr];
                ptr++;
            } else {
                cnt++;
                sum = 0;
            }
        }
        if (sum != 0) {
            cnt++;
        }
        if (cnt <= k) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

// newcoder ZJ24 : 机器人跳跃问题 中等
bool check(vector<int> const &height, int energy, int maxHeight){
    for(auto h : height){
        energy += energy - h;
        if(energy < 0){
            return false;
        }
        else if(energy > maxHeight){
            return true;
        }
    }
    return true;
}

void RobotPassThroughBuilding(){
    int n;
    cin >> n;
    vector<int> height(n, 0);
    int maxheight = 0;
    for(int i = 0; i < n; i++){
        cin >> height[i];
        maxheight = std::max(maxheight, height[i]);
    }
    int left = 1;
    int right = maxheight;
    int ans = 0;
    while(left <= right){
        int mid = left + (right - left)/2;
        if(check(height, mid, maxheight)){
            ans = mid;
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    cout << ans << endl;
}

int Solution::smallestDistancePair(vector<int>& nums, int k){
    sort(nums.begin(), nums.end());
    int left = 0;
    int right = nums.back() - nums.front();
    int len = nums.size();
    int ans = 0;
    while(left <= right){
        int mid = left + (right - left)/2;
        int cnt = 0;
        for(int i = 0; i < len; i++){
            int j = lower_bound(nums.begin(), nums.begin() + i, nums[i] - mid) - nums.begin();
            cnt += i - j;
        }
        if(cnt >= k){
            ans = mid;
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    return ans;
}

long long Solution::maxRunTime(int n, vector<int>& batteries){
    long long sumBattery = 0;
    for (auto&& battery : batteries) {
        sumBattery += (long long)battery;
    }
    long long left = 0;
    long long right = sumBattery / n + 1;
    long long ans = 0;
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        long long sumTime = 0;
        for (long long b : batteries) {
            sumTime += std::min(b, mid);
        }
        if (sumTime >= mid * (long long)n) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}

// 计算等位时间
// 给定一个数组arr长度为n，表示n个服务员，每服务一个客人的时间
// 给定一个正数m，表示有m个人等位，如果你是刚来的人，每个客人遵循有空位就上的原则请问你需要等多久?
// 假设m远远大于n，比如n <= 10^3，m <= 10^9，该怎么做是最优解?谷歌的面试，这个题连考了2个月

int Solution::WaitingTime(vector<int>& nums, int m){
    int maxNum = 0;
    for(auto num : nums){
        maxNum = std::max(maxNum, num);
    }
    int left = 0;
    int right = maxNum * m;
    int ans = 0;
    while(left <= right){
        int mid = left + (right - left)/2;
        int cnt = 0;
        for(auto num : nums){
            cnt += mid / num + 1;
        }
        if(cnt >= m + 1){
            ans = mid;
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    return ans;
}

// 刀砍毒杀怪兽问题
// 怪兽的初始血量是一个整数hp，给出每一回合刀砍和毒杀的数值cuts和poisons
// 第i回合如果用刀砍，怪兽在这回合会直接损失cuts[i]的血，不再有后续效果
// 第i回合如果用毒杀，怪兽在这回合不会损失血量，但是之后每回合都损失poisons[i]的血量
// 并且你选择的所有毒杀效果，在之后的回合都会叠加
// 两个数组cuts、poisons，长度都是n，代表你一共可以进行n回合
// 每一回合你只能选择刀砍或者毒杀中的一个动作
// 如果你在n个回合内没有直接杀死怪兽，意味着你已经无法有新的行动了
// 但是怪兽如果有中毒效果的话，那么怪兽依然会在血量耗尽的那回合死掉
// 返回至少多少回合，怪兽会死掉
// 数据范围 : 
// 1 <= n <= 10^5
// 1 <= hp <= 10^9
// 1 <= cuts[i]、poisons[i] <= 10^9

int CutOrPoison(vector<int>& cuts, vector<int>& poisons, int hp){
    int minCut = INT_MAX;
    for(auto cut : cuts){
        minCut = std::min(cut, minCut);
    }
    int left = 1;
    int right = hp / minCut + 1;
    int ans = 0;
    while(left <= right){
        int mid = left + (right - left) / 2;
        int damage = 0;
        for(int i = 0; i < mid; i++){
            damage += std::max(cuts[i], poisons[i] * (mid - i));
        }
        if(damage < mid){
            left = mid + 1;
        }
        else{
            ans = mid;
            right = mid - 1;
        }
    }
    return ans;
}