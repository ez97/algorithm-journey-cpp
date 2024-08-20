// 036 : https://www.bilibili.com/video/BV1Rp4y1g7ys
#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <complex>
#include <iterator>
#include <queue>
#include <string>
#include <unistd.h>
#include <utility>
#include <vector>

using std::vector;
using std::queue;
using std::deque;
using std::string;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root); // leetcode 102 : 二叉树的层序遍历 medium
    vector<vector<int>> zigzagLevelOrder(TreeNode* root); // leetcode 103 : 二叉树的锯齿状层序遍历 medium
    int widthOfBinaryTree(TreeNode* root); // leetcode 662 : 二叉树最大宽度 medium
    int maxDepth(TreeNode* root); // leetcode 104 : 二叉树的最大深度 easy
    int minDepth(TreeNode* root); // leetcode 111 : 二叉树的最小深度 easy
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder); // leetcode 105 : 从前序与中序遍历序列构造二叉树 medium
    bool isCompleteTree(TreeNode* root); // leetcode 958 : 二叉树的完全性检验 medium
    int countNodes(TreeNode* root); // leetcode 222 : 完全二叉树的节点个数 easy
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q); // leetcode 236 : 二叉树的最近公共祖先 medium
    TreeNode* lowestCommonAncestorInBST(TreeNode* root, TreeNode* p, TreeNode* q); // leetcode 235 : 搜索二叉树的最近公共祖先 medium
    vector<vector<int>> pathSum2(TreeNode* root, int targetSum); // leetcode 113 : 路径总和2 medium
    bool isBalanced(TreeNode* root); // leetcode 110 : 平衡二叉树 easy
    bool isValidBST(TreeNode* root); // lettcode 98 : 验证搜索二叉树 medium
    TreeNode* trimBST(TreeNode* root, int low, int high); // leetcode 669 : 修建二叉搜索树 medium
    int rob(TreeNode* root); // leetcode 337 : 二叉树上的打家劫舍问题 medium
};


// leetcode 297 : 二叉树的序列化与反序列化 hard
class Codec {
public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root);
    // Decodes your encoded data to tree.
    TreeNode* deserialize(std::string data);
    vector<TreeNode*> split(std::string &data);  
};

int main(){
    return 0;
}

vector<vector<int>> Solution::levelOrder(TreeNode* root){
    if(root == nullptr){
        return {};
    }
    vector<vector<int>> ans;
    queue<TreeNode*> qu;
    qu.push(root);
    int cnt;
    while(!qu.empty()){
        vector<int> tmp;
        cnt = qu.size();
        for(int i = 0; i < cnt; i++){
            TreeNode* curr = qu.front();
            tmp.push_back(curr->val);
            qu.pop();
            if (curr->left != nullptr) {
                qu.push(curr->left);
            }
            if (curr->right != nullptr) {
                qu.push(curr->right);
            }
        }
        ans.push_back(std::move(tmp));
    }
    return ans;
}

vector<vector<int>> Solution::zigzagLevelOrder(TreeNode* root) {
    if (root == nullptr) {
        return {};
    }
    vector<vector<int>> ans;
    deque<TreeNode*> dq;
    dq.push_back(root);
    int cnt;
    bool reverse = false;
    while (!dq.empty()) {
        vector<int> tmp;
        deque<TreeNode*> dq2;
        cnt = dq.size();
        for (int i = 0; i < cnt; i++) {
            TreeNode* curr;
            if (reverse) {
                curr = dq.back();
                dq.pop_back();
                if (curr->right != nullptr) {
                    dq2.push_front(curr->right);
                }
                if (curr->left != nullptr) {
                    dq2.push_front(curr->left);
                }
            } else {
                curr = dq.front();
                dq.pop_front();
                if (curr->left != nullptr) {
                    dq2.push_back(curr->left);
                }
                if (curr->right != nullptr) {
                    dq2.push_back(curr->right);
                }
            }
            tmp.push_back(curr->val);
        }
        dq = std::move(dq2);
        ans.push_back(std::move(tmp));
        reverse = !reverse;
    }
    return ans;
}

int Solution::widthOfBinaryTree(TreeNode* root){
    unsigned long long ans = 0, max, min; // unsigned溢出结果不变
    vector<std::pair<TreeNode*, unsigned long long>> vec;
    vec.emplace_back(root, 1);
    int level = 1;
    while (!vec.empty()) {
        
        vector<std::pair<TreeNode*, unsigned long long>> tmp;
        max = 0;
        min = LONG_LONG_MAX;
        for (auto &p : vec) {
            //cout << val << endl;
            auto &node = p.first;
            auto &val = p.second;
            min = std::min(min, val);
            max = std::max(max, val);
            if (node->left)
                tmp.emplace_back(node->left, val << 1);
            if (node->right)
                tmp.emplace_back(node->right, (val << 1) + 1);
        }
        //cout << "level : " << level++ << ", ";
        //cout << max << " " << min << endl;
        ans = std::max(ans, vec.back().second - vec[0].second + 1);
        vec = std::move(tmp);
    }
    return ans;
}

int Solution::maxDepth(TreeNode* root){
    if(root == nullptr){
        return 0;
    }
    int depth = 0;
    queue<TreeNode*> qu;
    qu.push(root);
    while(!qu.empty()){
        depth++;
        int size = qu.size();
        for(int i = 0; i < size; i++){
            TreeNode* tmp = qu.front();
            if(tmp->left) qu.push(tmp->left);
            if(tmp->right) qu.push(tmp->right);
            qu.pop();
        }
    }
    return depth;
}

// recursion version
// int Solution::maxDepth(TreeNode* root){
//     if(!root) return 0;
//     return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
// }

int depth = 1;
int mindepth = INT_MAX;
void dfs(TreeNode* root){
    if(!root->left && !root->right){
        mindepth = std::min(mindepth, depth);
        return;
    }
    depth++;
    if(root->right) dfs(root->right);
    if(root->left) dfs(root->left);
    depth--;
}
int Solution::minDepth(TreeNode* root) {
    if(!root) return 0;
    dfs(root);
    return mindepth;
}

// Codec
// Encodes a tree to a single string.
std::string Codec::serialize(TreeNode* root){
    if (!root)
        return "[]";
    std::string str = "[";
    queue<TreeNode*> qu;
    qu.push(root);
    str += std::to_string(root->val);
    while (!qu.empty()) {
        TreeNode* tmp = qu.front();
        qu.pop();
        if (tmp->left) {
            str += ",";
            str += std::to_string(tmp->left->val);
            qu.push(tmp->left);
        } else {
            str += ",#";
        }
        if (tmp->right) {
            str += ",";
            str += std::to_string(tmp->right->val);
            qu.push(tmp->right);
        } else {
            str += ",#";
        }
    }
    str += "]";
    return str;
}

vector<TreeNode*> Codec::split(std::string &data){
    //cout << "split" << endl;
    vector<TreeNode*> ans;
    int ptr = 1;
    int num = 0;
    bool neg = false;
    while (true) {
        if (data[ptr] == '#') {
            ans.push_back(nullptr);
            ptr++;
            //cout << "null input" << endl;
        } else if (data[ptr] == ',') {
            num = 0;
            ptr++;
        } else if (data[ptr] == ']') {
            break;
        } else {
            if(data[ptr] == '-'){
                neg = true;
                ptr++;
            }
            else{
                neg = false;
            }
            while (data[ptr] != ',' && data[ptr] != ']') {
                num = num * 10 + data[ptr] - '0';
                ptr++;
            }
            if(neg){
                num = -num;
            }
            TreeNode* node = new TreeNode(num);
            //cout << num << " input" << endl;
            ans.push_back(node);
        }
    }
    return ans;
}

// Decodes your encoded data to tree.
TreeNode* Codec::deserialize(std::string data){
    if (data == "[]") {
        return nullptr;
    }
    auto vec = split(data);
    queue<TreeNode*> qu;
    TreeNode* root = vec[0];
    qu.push(root);
    for (int i = 1; i < vec.size(); i += 2) {
        TreeNode* node = qu.front();
        qu.pop();
        if (vec[i]) {
            node->left = vec[i];
            qu.push(node->left);
        }
        if (vec[i+1]) {
            node->right = vec[i + 1];
            qu.push(node->right);
        }
    }
    return root;
}

TreeNode* buildSubTree(vector<int>& preorder, vector<int>& inorder, int l1, int r1, int l2, int r2){
    if(l1 > r1 || l2 > r2){
        return nullptr;
    }
    TreeNode* root = new TreeNode(preorder[l1]);
    int pos2 = std::distance(inorder.begin(), std::find(inorder.begin() + l2, inorder.begin() + r2, root->val));
    int leftcnt = pos2 - l2;
    int rightcnt = r2 - pos2;
    root->left = buildSubTree(preorder, inorder, l1 + 1, l1 + leftcnt, l2, pos2 - 1);
    root->right = buildSubTree(preorder, inorder, l1 + leftcnt + 1, r1, pos2 + 1, r2);
    return root;
}

TreeNode* Solution::buildTree(vector<int>& preorder, vector<int>& inorder){
    return buildSubTree(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
}

bool Solution::isCompleteTree(TreeNode* root){
    queue<TreeNode*> qu;
    qu.push(root);
    bool last = false;
    while(!qu.empty()){
        auto node = qu.front();
        qu.pop();
        if(node == nullptr){
            last = true;
            continue;
        }
        if(last){
            return false;
        }
        qu.push(node->left);
        qu.push(node->right);
    }
    return true;
}

int mostLeft(TreeNode* root, int level){
    while(root != nullptr){
        root = root->left;
        level++;
    }
    return level - 1;
}

int Solution::countNodes(TreeNode* root){
    if(root == nullptr){
        return 0;
    }
    int maxdep = mostLeft(root, 1);
    int cnt = 1;
    TreeNode* curr = root;
    int curr_level = 1;
    while(curr_level != maxdep){
        if(mostLeft(curr->right, curr_level + 1) == maxdep){
            curr = curr->right;
            cnt = cnt * 2 + 1;
        }
        else {
            curr = curr->left;
            cnt = cnt * 2;
        }
        curr_level++;
    }
    return cnt;
}

TreeNode* Solution::lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q){
    if(root == nullptr || root == p || root == q){
        return root;
    }
    auto l = lowestCommonAncestor(root->left, p, q);
    auto r = lowestCommonAncestor(root->right, p, q);
    if(!l && !r){
        return nullptr;
    }
    if(l && r){
        return root;
    }
    return l ? l : r;
}

TreeNode* Solution::lowestCommonAncestorInBST(TreeNode* root, TreeNode* p, TreeNode* q){
    if(root->val > p->val && root->val > q->val){
        return lowestCommonAncestorInBST(root->left, p, q);
    }
    if(root->val < p->val && root->val < q->val){
        return lowestCommonAncestorInBST(root->right, p, q);
    }
    return root;
}

void pathSubSum2(TreeNode* root, int targetSum, int currSum, vector<int> &path, vector<vector<int>> &ans){
    if(!root->left && !root->right){
        if(root->val + currSum == targetSum){
            path.push_back(root->val);
            ans.push_back(path);
            path.pop_back();
        }
        return;
    }
    path.push_back(root->val);
    currSum += root->val;
    pathSubSum2(root->left, targetSum, currSum, path, ans);
    pathSubSum2(root->right, targetSum, currSum, path, ans);
    currSum -= root->val;
    path.pop_back();
}

vector<vector<int>> Solution::pathSum2(TreeNode* root, int targetSum){
    if(root == nullptr){
        return {};
    }
    vector<vector<int>> ans;
    vector<int> path;
    pathSubSum2(root, targetSum, 0, path, ans);
    return ans;
}

int getSubTree(TreeNode* root, bool &result){
    if(!root || !result){
        return 0;
    }
    int left = getSubTree(root->left, result);
    int right = getSubTree(root->right, result);
    if(std::abs(left - right) > 1){
        result = false;
    }
    if(!result){
        return -1;
    }
    return std::max(left, right) + 1;
}

bool Solution::isBalanced(TreeNode* root){
    bool result = true;
    getSubTree(root, result);
    return result;
}

int getMaxSub(TreeNode* root, bool &result);
int getMinSub(TreeNode* root, bool &result);

int getMinSub(TreeNode* root, bool &result){
    if (!result) {
        return 0;
    }
    if(!root){
        return INT_MIN;
    }
    int right = getMinSub(root->right, result);
    int left = getMaxSub(root->left, result);
    if(right <= root->val || left >= root->val){
        result = false;
    }
    return left;
}

// 中序遍历做法
bool Solution::isValidBST(TreeNode* root){
    if(root == nullptr){
        return true;
    }
    const int MAXCNT = 10001;
    TreeNode* stk[MAXCNT];
    int p = 0;
    TreeNode* pre = nullptr;
    TreeNode* ptr = root;
    while(p > 0 || ptr != nullptr){
        if(ptr){
            stk[p++] = ptr;
            ptr = ptr->left;
        }
        else{
            ptr = stk[--p];
            if(pre && pre->val >= ptr->val){
                return false;
            }
            pre = ptr;
            ptr = ptr->right;
        }
    }
    return true;
}

// 递归做法
// long long min, max;
// bool Solution::isValidBST(TreeNode* root){
//     if (root == nullptr) {
//             min = LONG_LONG_MAX;
//             max = LONG_LONG_MIN;
//             return true;
//         }
//         bool l = isValidBST(root->left);
//         long long lmin = min;
//         long long lmax = max;
//         //cout << "(lmin, lmax) : " << lmin << " " << lmax << endl;
//         bool r = isValidBST(root->right);
//         long long rmin = min;
//         long long rmax = max;
//         //cout << "(rmin, rmax) : " << rmin << " " << rmax << endl;
//         min = std::min(std::min(lmin, rmin), (long long)root->val);
//         max = std::max(std::max(lmax, rmax), (long long)root->val);
//         return l && r && lmax < root->val && root->val < rmin;
// }

TreeNode* Solution::trimBST(TreeNode* root, int low, int high){
    if(!root){
        return nullptr;
    }
    if(root->val < low){
        return trimBST(root->right, low, high);
    }
    if(root->val > high){
        return trimBST(root->left, low, high);
    }
    root->left = trimBST(root->left, low, high);
    root->right = trimBST(root->right, low, high);
    return root;
}

int choose_root;
int nochoose_root;

void dfsRob(TreeNode* root){
    if(!root){
        choose_root = 0;
        nochoose_root = 0;
    }
    else{
        int c = root->val;
        int n = 0;
        dfsRob(root->left);
        c += nochoose_root;
        n += std::max(nochoose_root, choose_root);
        dfsRob(root->right);
        c += nochoose_root;
        n += std::max(nochoose_root, choose_root);
        choose_root = c;
        nochoose_root = n;
    }
}
int Solution::rob(TreeNode* root){
    dfsRob(root);
    return std::max(choose_root, nochoose_root);
}