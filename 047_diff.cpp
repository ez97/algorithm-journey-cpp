#include <bits/stdc++.h>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n); // leetcode 1109 : 航班预订统计 medium

};

// 等差数列差分略

int main(){

}

vector<int> Solution::corpFlightBookings(vector<vector<int>>& bookings, int n){
    vector<int> ans(n, 0);
    for (auto const& booking : bookings) {
        ans[booking[0] - 1]+= booking[2];
        if (booking[1] < n) {
            ans[booking[1]] -= booking[2];
        }
    }
    int curr = 0;
    for (auto &num : ans) {
        curr += num;
        num = curr;
    }
    return ans;
}