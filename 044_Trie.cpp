#include <array>
#include <bits/stdc++.h>
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

int const LEN = 2001;

class Trie {
private:
    int cnt = 1;
    array<int, LEN> pass;
    array<int, LEN> end;
    array<array<int, 26>, LEN> arr;
public:
    Trie() {}
    
    void insert(string word) {
        int cur = 1;
        pass[cur]++;
        for(auto ch : word){
            int path = ch - 'a';
            if(arr[cur][path] == 0){
                arr[cur][path] = ++cnt;
            }
            cur = arr[cur][path];
            pass[cur]++;
        }
        end[cur]++;
    }
    
    bool search(string word) {
        int cur = 1;
        for(auto ch : word){
            int path = ch - 'a';
            if(arr[cur][path] == 0){
                return false;
            }
            cur = arr[cur][path];
        }
        return end[cur] > 0 ? true : false;
    }
    
    bool startsWith(string prefix) {
        int cur = 1;
        for(auto ch : prefix){
            int path = ch - 'a';
            if(arr[cur][path] == 0){
                return false;
            }
            cur = arr[cur][path];
        }
        return pass[cur] > end[cur] ? true : false;
    }
};

int main(){
    return 0;
}