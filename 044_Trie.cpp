#include <array>
#include <bits/stdc++.h>
#include <functional>
#include <string>
#include <vector>

using namespace std;

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

vector<string> findWords(vector<vector<char>>& board, vector<string>& words){
    // TODO
    int cnt = 0;
    const int N = 3e6 + 1;
    array<int, N> pass;
    array<array<int, 26>, N> arr;

    auto insert = [&](string &word){
        int curr = 0;
        pass[curr]++;
        for(auto ch : word){
            int path = ch - 'a';
            if(arr[curr][path] == 0){
                arr[curr][path] = ++cnt;
            }
            curr = arr[curr][path];
            pass[curr]++;
        }
    };

    set<string> ans;
    int m = board.size();
    int n = board[0].size();
    vector<vector<int>> matrix(m, vector<int>(n, 0));
    auto check = [&](int x, int y){
        if(x < 0 || x >= m || y < 0 || y >= n){
            return false;
        }
        return true;
    };

    std::function<void(int, int, string, int)> dfs;
    dfs = [&](int x, int y, string word, int curr){
        if(!check(x, y)){
            return;
        }
        matrix[x][y] = 1;
        dfs(x - 1, y, word, curr);

    };

    for(auto word : words){
        insert(word);
    }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            dfs(i, j, "", 0);
        }
    }

    vector<string> ret;
    for(auto s : ans){
        ret.push_back(s);
    }
    return ret;
}