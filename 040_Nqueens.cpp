#include <bits/stdc++.h>
#include <functional>
#include <vector>


using std::vector;
// using std::set;
// using std::stack;
// using std::cout;
// using std::endl;
// using std::queue;
// using std::deque;
using std::string;
//using std::map;


class Solution {
public:
    vector<vector<string>> solveNQueens(int n); // leetcode 51 : N皇后 hard
};

int main(){
    Solution solution;
    int n = 4;
    vector<vector<string>> ans = solution.solveNQueens(n);
    for(int i = 0; i < n; i++){

    }
    return 0;
}


// 数组解法
// vector<vector<string>> Solution::solveNQueens(int n){
//     vector<vector<string>> ans;
//     const string dotstr(n, '.');

//     std::function<void(int, vector<int>)> f1;
//     f1 = [&f1, &ans, n, dotstr](int pos, vector<int> path) -> void {
//         if (pos == n) {
//             vector<string> pathstr(n, dotstr);
//             for (int i = 0; i < n; i++) {
//                 pathstr[i][path[i]] = 'Q';
//             }
//             ans.push_back(pathstr);
//         }
//         for (int i = 0; i < n; i++) {
//             bool check = true;
//             for (int j = 0; j < pos; j++) {
//                 if (path[j] == i || path[j] - i == pos - j || path[j] - i == j - pos) {
//                     check = false;
//                     break;
//                 }
//             }
//             if(check){
//                 path[pos] = i;
//                 f1(pos+1, path);
//             }
//         }
//     };
//     f1(0, vector<int>(n, 0));

//     return ans;
// }

// 位运算
vector<vector<string>> Solution::solveNQueens(int n){
    vector<vector<string>> ans;
    const string allDot(n, '.');

    auto check = [](int i, int col, int left, int right){
        int bitpos = (1 << i);
        return !((bitpos & col) || (bitpos & left) || (bitpos & right));
    };
    
    std::function<void(int, int, int, int, vector<int>&)> f1;
    f1 = [n, &ans, &allDot, &check, &f1](int pos, int col, int left, int right, vector<int> &path){
        if(pos == n){
            vector<string> pathstr(n, allDot);
            for (int i = 0; i < n; i++) {
                pathstr[i][path[i]] = 'Q';
            }
            ans.push_back(pathstr);
        }
        else {
            left <<=1;
            right >>=1;
            for(int i = 0; i < n; i++){
                if(check(i, col, left, right)){
                    int bitpos = 1 << i;
                    path[pos] = i;
                    f1(pos + 1, col | bitpos, left | bitpos, right | bitpos, path);
                }
            }
        }
    };

    vector<int> path(n, 0);
    f1(0, 0, 0, 0, path);
    return ans;
}