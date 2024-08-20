// 038 : https://www.bilibili.com/video/BV19m4y1n7mo
#include <algorithm>
#include <bits/stdc++.h>
#include <cctype>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::vector;
using std::set;
using std::stack;
using std::cout;
using std::endl;
// using std::queue;
// using std::deque;
using std::string;
//using std::map;

class Solution {
public:
    vector<string> generatePermutation(string s); // NC190 : 字符串的全部子序列 medium
    vector<vector<int>> subsetsWithDup(vector<int>& nums); // leetcode 90 : 子集 medium
    vector<vector<int>> permute(vector<int>& nums); // leetcode 46 : 全排列
    vector<vector<int>> permuteUnique(vector<int>& nums); // leetcode 47 : 不重复的全排列
    void reversestk(stack<int>& stk); // 递归逆序栈
    void sortstk(stack<int>& stk); // 递归排序栈
    void hanoi(int n); // 汉诺塔最优路径
    int basicCalculatorIII(string expression); // leetcode 772 : 基本计算器 III
    string decodeString(string s); // leetcode 394 : 字符串解码
    string countOfAtoms(string formula); // leetcode 726 : 原子的数量
};

int main(){
    Solution solution;
    // stack<int> stk;
    // stk.push(1);
    // stk.push(1);
    // stk.push(4);
    // stk.push(5);
    // stk.push(1);
    // stk.push(4);
    // solution.sortstk(stk);
    // while(!stk.empty()){
    //     cout << stk.top() << " ";
    //     stk.pop();
    // }
    // cout << endl;

    // int n = 6;
    // solution.hanoi(n);

    string s = "1+18*3";
    int ans = solution.basicCalculatorIII(s);
    cout << s << "=" << ans << endl;
    return 0;
}

void dfsGeneratePermutation(string& str, int pos, set<string>& stringset, string& substr) {
    if (pos == str.size()) {
        stringset.insert(substr);
        return;
    }
    dfsGeneratePermutation(str, pos + 1, stringset, substr);
    substr += str[pos];
    dfsGeneratePermutation(str, pos + 1, stringset, substr);
    substr.pop_back();
}

vector<string> Solution::generatePermutation(string s){
    vector<string> ans;
    set<string> stringset;
    string substr = "";
    dfsGeneratePermutation(s, 0, stringset, substr);
    for(auto str : stringset){
        ans.push_back(str);
    }
    return ans;
}

void dfsSubsets(vector<int> &nums, int pos, int size, vector<int> &subset, vector<vector<int>> &ans){
    if(pos == nums.size()){
        vector<int> arr;
        for(int i = 0; i < size; i++){
            arr.push_back(subset[i]);
        }
        ans.push_back(arr);
        return;
    }
    int next = pos + 1;
    while(next != nums.size() && nums[next] == nums[pos]){
        next++;
    }
    dfsSubsets(nums, next, size, subset, ans);
    for(; pos < next; pos++){
        subset[size] = nums[pos];
        size++;
        dfsSubsets(nums, next, size, subset, ans);
    }
}

vector<vector<int>> Solution::subsetsWithDup(vector<int>& nums){
    vector<vector<int>> ans;
    vector<int> subset(nums.size());
    sort(nums.begin(), nums.end());
    dfsSubsets(nums, 0, 0, subset, ans);

    return ans;
}

// C++ next_permutation 库
// vector<vector<int>> Solution::permute(vector<int>& nums) {
//     vector<vector<int>> ans;
//     sort(nums.begin(), nums.end());
//     do{
//         ans.push_back(nums);
//     } while (next_permutation(nums.begin(), nums.end()));
//     return ans;
// }

void permuteHelper(vector<int> &nums, int pos, vector<vector<int>>& ans, vector<int>& arr){
    if(pos == nums.size()){
        ans.push_back(arr);
    }
    else{
        for(int i = pos; i < nums.size(); i++){
            std::swap(nums[i], nums[pos]);
            arr.push_back(nums[pos]);
            permuteHelper(nums, pos + 1, ans, arr);
            arr.pop_back();
            std::swap(nums[i], nums[pos]);
        } 
    }
}

vector<vector<int>> Solution::permute(vector<int>& nums){
    vector<vector<int>> ans;
    vector<int> arr;
    permuteHelper(nums, 0, ans, arr);
    return ans;
}

void permuteUniqueHelper(vector<int> &nums, int pos, vector<vector<int>>& ans, vector<int>& arr){
    if(pos == nums.size()){
        ans.push_back(arr);
    }
    else{
        std::unordered_set<int> set;
        for(int i = pos; i < nums.size(); i++){
            if(set.count(nums[i])){
                continue;
            }
            else{
                set.insert(nums[i]);
            }
            std::swap(nums[i], nums[pos]);
            arr.push_back(nums[pos]);
            permuteUniqueHelper(nums, pos + 1, ans, arr);
            arr.pop_back();
            std::swap(nums[i], nums[pos]);
        } 
    }
}

vector<vector<int>> Solution::permuteUnique(vector<int>& nums){
    vector<vector<int>> ans;
    vector<int> arr;
    permuteUniqueHelper(nums, 0, ans, arr);
    return ans;
}

int bottomOut(stack<int>& stk){
    int t = stk.top();
    stk.pop();
    if(stk.empty()){
        return t;
    }
    int last = bottomOut(stk);
    stk.push(t);
    return last;
}

void Solution::reversestk(stack<int>& stk){
    //stack<int> tmp;
    if(stk.empty()){
        return;
    }
    int bottom = bottomOut(stk);
    reversestk(stk);
    stk.push(bottom);
}

int stkDepth(stack<int>& stk){
    if(stk.empty()){
        return 0;
    }
    int tmp = stk.top();
    stk.pop();
    int ans = stkDepth(stk) + 1;
    stk.push(tmp);
    return ans;
}

int stkMax(stack<int>& stk, int depth){
    if(depth == 0){
        return INT_MIN;
    }
    int tmp = stk.top();
    stk.pop();
    int com = stkMax(stk, depth - 1);
    stk.push(tmp);
    return std::max(tmp, com);
}

int stkTimes(stack<int>& stk, int max, int depth){
    if(depth == 0){
        return 0;
    }
    int tmp = stk.top();
    stk.pop();
    int resTimes = stkTimes(stk, max, depth - 1);
    stk.push(tmp);
    return resTimes + (tmp == max ? 1 : 0);
}

void stkDown(stack<int>& stk, int max, int depth, int cnt){
    if(depth == 0){
        for(int i = 0; i < cnt; i++){
            stk.push(max);
        }
    }
    else{
        int tmp = stk.top();
        stk.pop();
        stkDown(stk, max, depth - 1, cnt);
        if(tmp != max){
            stk.push(tmp);
        }
    }
}

void Solution::sortstk(stack<int> &stk){
    int resdepth = stkDepth(stk);
    //cout << resdepth << endl;
    while(resdepth > 0){
        int max = stkMax(stk, resdepth);
        int times = stkTimes(stk, max, resdepth);
        //cout << max << " " << times << endl;
        stkDown(stk, max, resdepth, times);
        resdepth -= times;
    }
}

void hanoiHelper(int n, const string &from, const string &to, const string &other, int &step){
    if(n == 1){
        cout << "step " << step << ": move no." << n << " from " << from << " to " << to << endl;
        step++;
    }
    else{
        hanoiHelper(n - 1, from, other, to, step);
        cout << "step " << step << ": move no." << n << " from " << from << " to " << to << endl;
        step++;
        hanoiHelper(n - 1, other, to, from, step);
    }
}

void Solution::hanoi(int n){
    int step = 1;
    if(n > 0){
        hanoiHelper(n, "a", "b", "c", step);
    }
}

int compute(stack<int> &nums, stack<char> &ops){
    int ans = nums.top();
    nums.pop();
    while(!ops.empty()){
        ans += ops.top() == '+' ? nums.top() : -nums.top();
        nums.pop();
        ops.pop();
    }
    return ans;
}

void push(stack<int> &nums, stack<char> ops, int curr, int op){
    if(nums.size() == 0 || ops.top() == '+' || ops.top() == '-'){
        nums.push(curr);
        ops.push(op);
    }
    else{
        int topNum = nums.top();
        nums.pop();
        char topOp = ops.top();
        ops.pop();
        cout << topNum << " " << topOp << " " << curr << endl;
        if(topOp == '*'){
            nums.push(topNum * curr);
        }
        else{
            nums.push(topNum / curr);
        }
        ops.push(op);
    }
}

int calculator(string &str, int &pos){
    int curr = 0;
    stack<int> nums;
    stack<char> ops;
    while(pos < str.size() && str[pos] != ')'){
        if(str[pos] >= '0' && str[pos] <= '9') {
            curr = curr * 10 + str[pos];
            pos++;
        }
        else if(str[pos] == '(') {
            push(nums, ops, curr, str[pos]);
            pos++;
            curr = 0;
        }
        else{
            pos++;
            curr = calculator(str, pos);
        }
    }
    push(nums, ops, curr, '+');
    return compute(nums, ops);
}

int Solution::basicCalculatorIII(string expression){
    int pos = 0;
    return calculator(expression, pos);
}

string decodeHelper(string &s, int pos, int &gpos){
    string ret;
    while(pos < s.size() && s[pos] != ']'){
        if(std::isalpha(s[pos])){
            ret += s[pos];
        }
        else {
            int cnt = s[pos] - '0';
            while(std::isdigit(s[pos + 1])){
                pos++;
                cnt = cnt * 10 + s[pos] - '0';
            }
            string substr = decodeHelper(s, pos + 2, gpos);
            pos = gpos;
            for(int i = 0; i < cnt; i++){
                ret += substr;
            }
        }
    }
    gpos = pos + 1;
    return ret;
}

string Solution::countOfAtoms(string formula){
    int pos = 0;
    int n = formula.size();
    auto parseAtom = [&]() -> string {
        string ret;
        ret += formula[pos++];
        while(pos < n && std::islower(formula[pos])){
            ret += formula[pos++];
        }
        return ret;
    };

    auto parseNum = [&]() -> int {
        if(pos == n || !isdigit(formula[pos])){
            return 1;
        }
        int num = 0;
        while(pos < n && isdigit(formula[pos])){
            num = num * 10 + formula[pos++] - '0';
        }
        return num;
    };

    stack<std::unordered_map<string, int>> stk;
    stk.push({});
    while (pos < n) {
        char ch = formula[pos];
        if(ch == '('){
            pos++;
            stk.push({});
        }
        else if(isalpha(ch)){
            string atom = parseAtom();
            int num = parseNum();
            stk.top()[atom] += num;
        }
        else if (ch == ')') {
            pos++;
            int num = parseNum();
            auto hash = stk.top();
            stk.pop();
            for(auto &p : hash){
                stk.top()[p.first] += p.second * num;
            }
        }
    }

    vector<std::pair<string, int>> vec;
    auto &atomNum = stk.top();
    for(auto &p : atomNum){
        vec.push_back(p);
    }
    std::sort(vec.begin(), vec.end(), [](auto p1, auto p2){
        return p1.first < p2.first;
    });

    string ans;
    for(auto &p : vec){
        ans += p.first;
        if(p.second > 1){
            ans += std::to_string(p.second);
        }
    }
    return ans;
}