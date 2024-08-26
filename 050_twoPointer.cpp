#include <algorithm>
#include <any>
#include <bits/stdc++.h>
#include <variant>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums); // leetcode 922 : 按奇偶排序数组 II esay
    int findDuplicate(vector<int>& nums); // leetcode 287 : 寻找重复数 medium
    int trap(vector<int>& height); // leetcode 42 : 接雨水 hard
    int numRescueBoats(vector<int>& people, int limit); // leetcode 881 : 救生艇
    int maxArea(vector<int>& height); // leetcode 11 : 盛最多水的容器 medium
    int findRadius(vector<int>& houses, vector<int>& heaters); // leetcode 475 : 供暖期 medium
    int firstMissingPositive(vector<int>& nums); // leetcode 41 : 缺失的第一个正数
};

int main(){
    return 0;
}

vector<int> Solution::sortArrayByParityII(vector<int>& nums){
    int len = nums.size();
    if(len < 2){
        return nums;
    }
    int ptr1 = 0;
    int ptr2 = 1;
    while(ptr1 < len && ptr2 < len){
        while(ptr1 < len && nums[ptr1] % 2 == 0){
            ptr1 += 2;
        }
        while(ptr2 < len && nums[ptr2] % 2 == 1){
            ptr2 += 2;
        }
        if(ptr1 < len && ptr2 < len){
            swap(nums[ptr1], nums[ptr2]);
        }
    }
    return nums;
}

int Solution::findDuplicate(vector<int>& nums){
    int ptr1 = 0;
    int ptr2 = 0;
    do {
        ptr1 = nums[ptr1];
        ptr2 = nums[nums[ptr2]];
    } while (ptr1 != ptr2);
    ptr1 = 0;
    while(ptr1 != ptr2){
        ptr1 = nums[ptr1];
        ptr2 = nums[ptr2];
    }
    return ptr1;
}

// dp
// int Solution::trap(vector<int>& height){
//     int len = height.size();
//     vector<int> left(len);
//     vector<int> right(len);
//     int maxheight = 0;
//     for (int i = 0; i < len; i++) {
//         maxheight = std::max(maxheight, height[i]);
//         left[i] = maxheight;
//     }
//     maxheight = 0;
//     for (int i = len - 1; i >= 0; i--) {
//         maxheight = std::max(maxheight, height[i]);
//         right[i] = maxheight;
//     }
//     vector<int> rain(len, 0);
//     for (int i = 1; i < len - 1; i++) {
//         int tmp = std::min(left[i - 1], right[i + 1]) - height[i];
//         if(tmp > 0){
//             rain[i] = tmp;
//         }
//     }
//     int ans = 0;
//     for (auto r : rain) {
//         ans += r;
//     }
//     return ans;
// }

// 2 pointer
int Solution::trap(vector<int>& height){
    int left = 0;
    int right = height.size() - 1;
    int leftMax = 0;
    int rightMax = 0;
    int ans = 0;
    while(left < right){
        leftMax = std::max(height[left], leftMax);
        rightMax = std::max(height[right], rightMax);
        if(height[left] < height[right]){
            ans += leftMax - height[left++];
        }
        else{
            ans += rightMax - height[right--];
        }
    }
    return ans;
}

int Solution::numRescueBoats(vector<int>& people, int limit){
    sort(people.begin(), people.end());
    int ptr1 = 0;
    int ptr2 = people.size() - 1;
    int cnt = 0;
    while(ptr1 <= ptr2){
        cnt++;
        if(ptr1 == ptr2){
            break;
        }
        if(people[ptr1] + people[ptr2] <= limit){
            ptr1++;
            ptr2--;
        }
        else{
            ptr2--;
        }
    }
    return cnt;
}

int Solution::maxArea(vector<int>& height){
    int left = 0;
    int right = height.size() - 1;
    int ans = 0;
    while(left < right){
        ans = std::max(ans, std::min(height[left], height[right]) * (right - left));
        if(height[left] > height[right]){
            right--;
        }
        else{
            left++;
        }
    }
    return ans;
}

int Solution::findRadius(vector<int>& houses, vector<int>& heaters){
    int ptr1 = 0;
    int ptr2 = 0;
    int len1 = houses.size();
    int len2 = heaters.size();
    int r = 0;
    sort(houses.begin(), houses.end());
    sort(heaters.begin(), heaters.end());
    while(ptr1 < len1){
        while(ptr2 < len2 - 1 && std::abs(houses[ptr1] - heaters[ptr2]) >= std::abs(houses[ptr1] - heaters[ptr2+1])){
            ptr2++;
        }
        r = std::max(r, std::abs(houses[ptr1] - heaters[ptr2]));
    }
    return r;
}

int Solution::firstMissingPositive(vector<int>& nums){
    int ptr1 = 0;
    int ptr2 = nums.size() - 1;
    while(ptr1 < ptr2){
        if((long long int)nums[ptr1] - 1 == ptr1){
            ptr1++;
        }
        else if(nums[ptr1] <= 0 || nums[ptr1] > nums.size() || nums[ptr1] == nums[nums[ptr1] - 1]){
            swap(nums[ptr1], nums[ptr2]);
            ptr2--;
        }
        else {
            swap(nums[ptr1], nums[nums[ptr1] - 1]);
        }
    }
    return ptr1 + 1;
}