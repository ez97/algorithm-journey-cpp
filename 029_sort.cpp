// 029 : https://www.bilibili.com/video/BV1Kh4y1c7Pu
#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>
#include <stack>
#include <utility>
#include <vector>

const int ARRAYSIZE = 100;

int getRand(int min, int max) {
    return ( rand() % (max - min + 1) ) + min;
}

void bubble_sort(std::vector<int> &nums); // 冒泡
void select_sort(std::vector<int> &nums); // 选择
void insertion_sort(std::vector<int> &nums); // 插入
void merge_sort(std::vector<int> &nums); // 归并
void quick_sort(std::vector<int> &nums); // 快排
void heap_sort(std::vector<int> &nums); // 堆
void count_sort(std::vector<int> &nums); // 计数
void radix_sort(std::vector<int> &nums); // 基数

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    std::vector<int> nums;
    for(int i = 0; i < ARRAYSIZE; i++){
        nums.emplace_back(getRand(100, 999));
    }

    auto target = nums;
    std::sort(target.begin(), target.end());

    heap_sort(nums);
    if(nums == target){
        std::cout << "ans right" << std::endl;
    }
    else{
        std::cout << "ans wrong" << std::endl;
    }

    return 0;
}

void bubble_sort(std::vector<int> &nums){
    int len = nums.size();
    for(int i = 0; i < len - 1; i++){
        for(int j = 0; j < len - i - 1; j++){
            if(nums[j] > nums[j+1]){
                std::swap(nums[j], nums[j+1]);
            }
        }
    }
}

void select_sort(std::vector<int> &nums){
    int len = nums.size();
    int minpos;
    for(int i = 0; i < len; i++){
        minpos = i;
        for(int j = i + 1; j < len; j++){
            if(nums[j] < nums[minpos]){
                minpos = j;
            }
        }
        std::swap(nums[i], nums[minpos]);
    }
}

void insertion_sort(std::vector<int> &nums){
    int len = nums.size();
    for(int i = 1; i < len; i++){
        int tmp = nums[i];
        int j = i;
        while(j > 0 && nums[j - 1] > tmp){
            nums[j] = nums[j - 1];
            j--;
        }
        nums[j] = tmp;
    }
}

void merge_sort(std::vector<int> &nums){
    int len = nums.size();
    std::vector<int> tmp(len);
    for(int sublen = 1; sublen < len; sublen *= 2){
        for(int i = 0; i < len; i += sublen * 2){
            int pos = i;
            int start1 = i;
            int end1 = std::min(i + sublen, len);
            int start2 = end1;
            int end2 = std::min(i + sublen * 2, len);

            while(start1 < end1 && start2 < end2){
                tmp[pos++] = nums[start1] < nums[start2] ? nums[start1++] : nums[start2++];
            }
            while(start1 < end1){
                tmp[pos++] = nums[start1++];
            }
            while(start2 < end2){
                tmp[pos++] = nums[start2++];
            }
        }
        nums.swap(tmp);
    }
}

void quick_sort(std::vector<int> &nums){
    int len = nums.size();
    std::stack<std::pair<int, int>> stk;
    stk.push(std::make_pair(0, len - 1));
    while(!stk.empty()){
        int start = stk.top().first;
        int end = stk.top().second;
        stk.pop();

        int pivot = nums[end];
        int lt = start; // nums[start...lt-1] < pivot
        int gt = end; // nums[gt+1...end] > pivot
        int i = start; // nums[lt...i-1] = pivot
        // nums[i...gt] = unknow

        while(i <= gt){
            if(nums[i] < pivot){
                std::swap(nums[i++], nums[lt++]);
            }
            else if(nums[i] == pivot){
                i++;
            }
            else{
                std::swap(nums[i], nums[gt--]);
            }
        }

        if (start < lt - 1) stk.push(std::make_pair(start, lt - 1));
        if (gt + 1 < end) stk.push(std::make_pair(gt + 1, end));
    }
}

void heapify(std::vector<int> &nums, int target, int heapsize){
    while(true){
        int largest = target;
        int left = 2 * target;
        int right = 2 * target + 1;
        if(left < heapsize && nums[left] > nums[largest]){
            largest = left;
        }
        if(right < heapsize && nums[right] > nums[largest]){
            largest = right;
        }
        if(largest != target){
            std::swap(nums[target], nums[largest]);
            target = largest;
        }
        else{
            break;
        }
    }
}

void heap_sort(std::vector<int> &nums){
    // insert one by one: O(nlogn)
    // std::vector<int> heap;
    // for(auto num : nums){
    //     heap.push_back(num);
    //     int i = heap.size() - 1;
    //     while(i > 0 && heap[(i - 1) / 2] < heap[i]){
    //         std::swap(heap[(i - 1) / 2], heap[i]);
    //         i = (i - 1) / 2;
    //     }
    // }

    // use heapify : O(n)
    int n = nums.size();
    for(int i = n / 2 - 1; i >= 0; i--){
        heapify(nums, i, n);
    }
    for(int i = n - 1; i > 0; i--){
        if(nums[i] < nums[0]){
            std::swap(nums[i], nums[0]);
            heapify(nums, 0, i);
        }
    }
}

void count_sort(std::vector<int> &nums){
    int maxVal = *std::max_element(nums.begin(), nums.end());
    int minVal = *std::min_element(nums.begin(), nums.end());
    int range = maxVal - minVal + 1;
    std::vector<int> cnt(range, 0);
    for(auto num : nums){
        cnt[num - minVal]++;
    }
    for(int i = 1; i < range; i++){
        cnt[i] += cnt[i - 1];
    }

    int len = nums.size();
    std::vector<int> ans(len);
    for(int i = len - 1; i >= 0; i--){
        ans[--cnt[nums[i] - minVal]] = nums[i];
    }

    nums = std::move(ans);
}

int get_n_digit(int num, int n){
    int offset = 1;
    while(n > 0){
        offset *= 10;
        n--;
    }
    return (num / offset) % 10;
}

void radix_sort(std::vector<int> &nums){
    int maxVal = *std::max_element(nums.begin(), nums.end());
    int maxDigit = 0;
    while(maxVal > 0){
        maxVal /= 10;
        maxDigit++;
    }

    int len = nums.size();
    for(int i = 0; i < maxDigit; i++){
        std::vector<int> tmp(len);
        int cnt[10] = { 0 };
        for(int j = 0; j < len; j++){
            cnt[get_n_digit(nums[j], i)]++;
        }
        for(int j = 1; j < 10; j++){
            cnt[j] += cnt[j - 1];
        }
        for(int j = len - 1; j >= 0; j--){
            tmp[--cnt[get_n_digit(nums[j], i)]] = nums[j];
        }
        nums = std::move(tmp);
    }
}