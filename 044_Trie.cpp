#include <array>
#include <bits/stdc++.h>
#include <functional>
#include <string>
#include <vector>

//using namespace std;
using std::vector;
using std::string;
using std::array;
using std::to_string;

// TODO: 前面两个写的不好，复习的时候重写


// leetcode 208 : 实现前缀树 hard 

// class version
// struct TrieNode{
//     bool flag;
//     array<TrieNode*, 26> dic;
//     TrieNode() : flag(false), dic(array<TrieNode*, 26>{nullptr}) {}
// };

// class Trie {
// private:
//     TrieNode* root;
// public:
//     Trie() {}
    
//     void insert(string word) {
//         TrieNode* ptr = root;
//         for(auto const ch : word){
//             if(ptr->dic[ch - 'a'] == nullptr){
//                 ptr->dic[ch - 'a'] = new TrieNode();
//             }
//             ptr = ptr->dic[ch - 'a'];
//         }
//         ptr->flag = true;
//     }
    
//     bool search(string word) {
//         TrieNode* ptr = root;
//         for(auto const ch : word){
//             if(ptr->dic[ch - 'a'] == nullptr){
//                 return false;
//             }
//         }
//         if(!ptr->flag) return false;
//         return true;
//     }
    
//     bool startsWith(string prefix) {
//         TrieNode* ptr = root;
//         for(auto const ch : prefix){
//             if(ptr->dic[ch - 'a'] == nullptr){
//                 return false;
//             }
//         }
//         if(ptr->dic.empty()){
//             return false;
//         }
//         if(ptr->dic.empty()){
//             return false;
//         }
//         return true;
//     }
// };

int const LEN = 1e5 + 50;

class Trie {
private:
    int cnt;
    int end[LEN];
    int arr[LEN][26];
public:
    Trie() {
        memset(end, 0, sizeof(end));
        memset(arr, 0, sizeof(arr));
        cnt = 0;
    }
    
    void insert(string word) {
        int cur = 0;
        for(auto ch : word){
            int path = ch - 'a';
            if(arr[cur][path] == 0){
                arr[cur][path] = ++cnt;
            }
            cur = arr[cur][path];
        }
        end[cur]++;
    }
    
    bool search(string word) {
        int cur = 0;
        for(auto ch : word){
            int path = ch - 'a';
            if(arr[cur][path] == 0){
                return false;
            }
            cur = arr[cur][path];
        }
        return end[cur];
    }
    
    bool startsWith(string prefix) {
        int cur = 0;
        for(auto ch : prefix){
            int path = ch - 'a';
            if(arr[cur][path] == 0){
                return false;
            }
            cur = arr[cur][path];
        }
        return true;
    }
};

class Solution {
public:
    vector<int> countConsistentKeys(vector<vector<int> >& b, vector<vector<int> >& a); // 接头密匙 https://www.nowcoder.com/practice/c552d3b4dfda49ccb883a6371d9a6932
    int findMaximumXOR(vector<int>& nums); // leetcode 421 : 数组中两个数的最大异或值 medium
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words); // leetcode 212 : 单词搜索 II hard
};

int main(){
    return 0;
}



vector<int> Solution::countConsistentKeys(vector<vector<int> >& b, vector<vector<int> >& a){
    const int N = 1e7 + 1;
    int cnt = 0;
    array<int, N> pass;
    array<array<int, 12>, N> arr; // 0~9, #, -

    auto getPos = [](char ch){
        if(ch == '#'){
            return 10;
        }
        else if(ch == '-'){
            return 11;
        }
        return ch - '0';
    };

    auto getStr = [](vector<int> &nums){
        string str;
        for(int i = 1; i < nums.size(); i++){
            str += to_string(nums[i] - nums[i - 1]);
            str += "#";
        }
        return str;
    };

    auto insert = [&](const string& str){
        int curr = 0;
        pass[curr]++;
        for(auto ch : str){
            auto path = getPos(ch);
            if(arr[curr][path] == 0){
                arr[curr][path] = ++cnt;
            }
            curr = arr[curr][path];
            pass[curr]++;
        }
    };

    auto getCnt = [&](const string& str){
        int curr = 0;
        for(auto ch : str){
            auto path = getPos(ch);
            if(arr[curr][path] == 0){
                return 0;
            }
            curr = arr[curr][path];
        }
        return pass[curr];
    };

    for(auto vec : a){
        insert(getStr(vec));
    }

    vector<int> ans;
    for(auto vec : b){
        int bcnt = getCnt(getStr(vec));
        ans.push_back(bcnt);
    }
    return ans;
}

int Solution::findMaximumXOR(vector<int>& nums){
    int cnt = 0;
    
    const int N = 3000001;
    array<int, N> pass{};
    array<array<int, 2>, N> arr{{}};
    
    int highestNum = 0;
    int high = 0;
    for(auto num : nums){
        highestNum = std::max(highestNum, num);
    }
    while(highestNum > 0){
        highestNum >>= 1;
        high++;
    }

    auto insert = [&](int num) {
        int k = high;
        int curr = 0;
        pass[curr]++;
        while (k >= 0) {
            int mask = 1 << k;
            int path = ((mask & num) == 0) ? 0 : 1;
            if (arr[curr][path] == 0) {
                arr[curr][path] = ++cnt;
            }
            curr = arr[curr][path];
            pass[curr]++;
            k--;
        }
    };
    auto getXor = [&](int num) {
        int k = high;
        int curr = 0;
        int ans = 0;
        while (k >= 0) {
            int mask = 1 << k;
            int path = ((mask & num) == 0) ? 1 : 0;
            if (arr[curr][path] != 0 ) {
                ans += mask;
                curr = arr[curr][path];
            } else {
                curr = arr[curr][!path];
            }
            k--;
        }
        return ans;
    };

    int maxXor = INT_MIN;
    for(auto num : nums){
        insert(num);
    }
    for (auto num : nums) {
        maxXor = std::max(maxXor, getXor(num));
    }
    return maxXor;
}


static const int N = 1e5 + 1;
array<int, N> pass{};
array<string, N> end{};
array<array<int, 26>, N> arr{};
int cnt;

void buildTrie(vector<string> const &words){
    cnt = 1;
    for(auto const &word : words){
        int curr = 1;
        pass[curr]++;
        for(auto ch : word){
            int path = ch - 'a';
            if(arr[curr][path] == 0){
                arr[curr][path] = ++cnt;
            }
            curr = arr[curr][path];
            pass[curr]++;
        }
        end[curr] = word;
    }
}

int dfsTrie(vector<vector<char>> &board, vector<string> &ans, int x, int y, int curr){
    if(x < 0 || x >= board.size() || y < 0 || y >= board[0].size() || board[x][y] == 0){
        return 0;
    }
    char ch = board[x][y];
    int path = ch - 'a';
    curr = arr[curr][path];
    if(pass[curr] == 0){
        return 0;
    }

    int fix = 0;
    if(!end[curr].empty()){
        fix++;
        ans.push_back(end[curr]);
        end[curr].clear();
    }

    board[x][y] = 0;
    fix += dfsTrie(board, ans, x+1, y, curr);
    fix += dfsTrie(board, ans, x-1, y, curr);
    fix += dfsTrie(board, ans, x, y+1, curr);
    fix += dfsTrie(board, ans, x, y-1, curr);
    board[x][y] = ch;
    pass[curr] -= fix;
    return fix;
}

void clearTrie(){
    for(int i = 1; i <= cnt; i++){
        arr[i].fill(0);
        pass[i] = 0;
        end[i].clear();
    }
}

vector<string> Solution::findWords(vector<vector<char>>& board, vector<string>& words){
    vector<string> ans;
    buildTrie(words);
    for(int i = 0; i < board.size(); i++){
        for(int j = 0; j < board[0].size(); j++){
            dfsTrie(board, ans, i, j, 0);
        }
    }
    return ans;
}