// 035 : https://www.bilibili.com/video/BV1nF411y7rD
#include <bits/stdc++.h>
#include <cstdlib>
#include <functional>
#include <list>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>


// CD62 : 设计具有setAll功能的哈希表 esay
class SetAllHashMap{
public:
    void put(int key, int value);
    int get(int key);
    bool containsKey(int key);
    void setAll(int value);
private:
    std::unordered_map<int, std::pair<int, int>> HashMap;
    int setAllValue;
    int setAllTime = -1;
    int mapTime = 0;
};

// leetcode 146 : LRU cache medium
class LRUCache {
public:
    class ListNode {
    public:
        int key;
        int val;
        ListNode* next;
        ListNode* prev;
        ListNode(int k, int v) : key{k}, val{v}, next{nullptr}, prev{nullptr} {}
    };

    LRUCache(int capacity)
        : cnt_(0), head_{nullptr}, tail_(nullptr), capacity_(capacity),
          HashMap_{} {}
    int get(int key);
    void put(int key, int value);
    void evict();
    void moveToHead(ListNode* curr);

private:
    int cnt_;
    ListNode* head_;
    ListNode* tail_;
    int capacity_;
    std::unordered_map<int, ListNode*> HashMap_;
};

// leetcode 380 : O(1) 时间插入、删除和获取随机元素
class RandomizedSet {
public:
    RandomizedSet() {
        srand((unsigned int)time(NULL));
    }
    bool insert(int val);
    bool remove(int val);
    int getRandom();
private:
    std::vector<int> nums;
    std::unordered_map<int, int> HashMap;
};

// leetcode 381 : O(1) 时间插入、删除和获取随机元素，允许重复数字 hard
class RandomizedCollection {
public:
    RandomizedCollection() {
        srand((unsigned int)time(NULL));
    }
    bool insert(int val);
    bool remove(int val);
    int getRandom();
private:
    std::vector<int> nums;
    std::unordered_map<int, std::unordered_set<int>> HashSet; 
};

// leetcode 295 : 数据流的中位数 hard
class MedianFinder {
public:
    MedianFinder() {}
    void addNum(int num);
    double findMedian();
private:
    std::priority_queue<int, std::vector<int>, std::less<int>> MaxHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> MinHeap;
};

// leetcode 895 : 最大频率栈 hard
class FreqStack {
public:
    FreqStack() : maxFreq(0) {}
    void push(int val);
    int pop();
private:
    std::unordered_map<int, std::stack<int>> freq_to_data;
    std::unordered_map<int, int> data_to_freq;
    int maxFreq;
};

// leetcode 432 : All O(1) hard
class AllOne {
public:
    class ListNode{
    public:
        int freq;
        ListNode* prev;
        ListNode* next;
        std::unordered_set<std::string> HashSet;
        ListNode(int x) : freq(x) {}
        ListNode(int x, ListNode* l, ListNode* r) : freq(x), prev(l), next(r) {}
    };
    AllOne() {
        head = new ListNode(0);
        tail = new ListNode(INT_MAX);
        head->next = tail;
        tail->prev = head;
    }
    ~AllOne() {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
}
    void removeNode(ListNode* node);
    ListNode* addNode(int freq, ListNode* prev, ListNode* next);
    void inc(std::string key);
    void dec(std::string key);
    std::string getMaxKey();
    std::string getMinKey();
private:
    std::unordered_map<std::string, ListNode*> HashMap;
    ListNode* head;
    ListNode* tail;
};



int main(){
    return 0;
}


// SetAllHashMap
void SetAllHashMap::put(int key, int value){
    HashMap[key] = std::make_pair(value, mapTime);
}

int SetAllHashMap::get(int key){
    if(!HashMap.count(key)){
        return -1;
    }
    int value, time;
    std::tie(value, time) = HashMap[key];
    if(time <= setAllTime){
        value = setAllValue;
    }
    return value;
}

bool SetAllHashMap::containsKey(int key){
    if(!HashMap.count(key)){
        return false;
    }
    return true;
}

void SetAllHashMap::setAll(int value){
    setAllValue = value;
    setAllTime = mapTime++;
}

// LRU cache
int LRUCache::get(int key) {
    if (!HashMap_.count(key)) {
        return -1;
    }
    ListNode* curr = HashMap_[key];
    moveToHead(curr);
    return curr->val;
}

void LRUCache::evict() {
    if (tail_ == nullptr) {
        return;
    }
    HashMap_.erase(tail_->key);
    if(tail_->prev == nullptr){
        head_ = nullptr;
        tail_ = nullptr;
    }
    else{
        tail_ = tail_->prev;
        tail_->next = nullptr;
    }
}

void LRUCache::put(int key, int value) {
    if (HashMap_.count(key)) {
        HashMap_[key]->val = value;
        moveToHead(HashMap_[key]);
        return;
    }
    
    if (cnt_ == capacity_) {
        evict();
        cnt_--;
    }
    ListNode* nhead = new ListNode(key, value);
    HashMap_[key] = nhead;
    if (head_ == nullptr) {
        head_ = nhead;
        tail_ = nhead;
    } else {
        nhead->next = head_;
        head_->prev = nhead;
        head_ = nhead;
    }
    cnt_++;
}

void LRUCache::moveToHead(ListNode *curr){
    if(curr == head_){
        return;
    }
    if(curr == tail_){
        tail_->prev->next = nullptr;
        tail_ = tail_->prev;
    }
    else{
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }
    
    head_->prev = curr;
    curr->next = head_;
    head_ = curr;
}

// RandomizedSet
bool RandomizedSet::insert(int val){
    if(HashMap.count(val)){
        return false;
    }
    nums.push_back(val);
    HashMap[val] = nums.size() - 1;
    return true;
}
bool RandomizedSet::remove(int val){
    if (!HashMap.count(val)) {
        return false;
    }
    HashMap[nums.back()] = HashMap[val];
    nums[HashMap[val]] = nums.back();
    nums.pop_back();
    HashMap.erase(val);
    return true;
}
int RandomizedSet::getRandom(){
    int randomindex = rand() % nums.size();
    return nums[randomindex];
}

// RandomizedCollection
bool RandomizedCollection::insert(int val) {
    bool ret = true;
    if (HashSet.count(val)) {
        ret = false;
    }
    nums.push_back(val);
    HashSet[val].insert(nums.size() - 1);
    return ret;
}
    
bool RandomizedCollection::remove(int val) {
    if (!HashSet.count(val)) {
        return false;
    }
    int index = *(HashSet[val].begin());
    nums[index] = nums.back();
    HashSet[val].erase(index);
    HashSet[nums[index]].erase(nums.size() - 1);
    if(index < nums.size() - 1){
        HashSet[nums[index]].insert(index);
    }
    if(HashSet[val].size() == 0){
        HashSet.erase(val);
    }
    nums.pop_back();
    return true;
}
    
int RandomizedCollection::getRandom() {
    int randomindex = rand() % nums.size();
    return nums[randomindex];
}

// MedianFinder
void MedianFinder::addNum(int num){
    // x x x ... max | min ... x x x
    if(MaxHeap.empty() || num <= MaxHeap.top()){
        MaxHeap.push(num);
        if(MinHeap.size() + 1 < MaxHeap.size()){
            MinHeap.push(MaxHeap.top());
            MaxHeap.pop();
        }
    }
    else{
        MinHeap.push(num);
        if(MaxHeap.size() < MinHeap.size()){
            MaxHeap.push(MinHeap.top());
            MinHeap.pop();
        }
    }
}

double MedianFinder::findMedian(){
    if(MaxHeap.size() == MinHeap.size()){
        return static_cast<double>(MaxHeap.top() + MinHeap.top()) / 2;
    }
    return MaxHeap.top();
}

// FreqStack
void FreqStack::push(int val){
    data_to_freq[val]++;
    freq_to_data[data_to_freq[val]].push(val);
    maxFreq = std::max(maxFreq, data_to_freq[val]);
}

int FreqStack::pop(){
    int val = freq_to_data[maxFreq].top();
    freq_to_data[maxFreq].pop();
    data_to_freq[val]--;
    if(freq_to_data[maxFreq].empty()){
        maxFreq--;
    }
    return val;
}

// AllOne
void AllOne::removeNode(ListNode* node){
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
}

AllOne::ListNode* AllOne::addNode(int freq, ListNode *prev, ListNode *next){
    ListNode* node = new ListNode(freq, prev, next);
    prev->next = node;
    next->prev = node;
    return node;
}

void AllOne::inc(std::string key){
    if(!HashMap.count(key)){
        if(head->next->freq == 1){
            HashMap[key] = head->next;
            head->next->HashSet.insert(key);
        }
        else{
            HashMap[key] = addNode(1, head, head->next);
            HashMap[key]->HashSet.insert(key);
        }
    }
    else{
        ListNode* curr = HashMap[key];
        curr->HashSet.erase(key);
        if(curr->next->freq == curr->freq + 1){
            HashMap[key] = curr->next;
            curr->next->HashSet.insert(key);
        }
        else{
            HashMap[key] = addNode(curr->freq + 1, curr, curr->next);
            HashMap[key]->HashSet.insert(key);
        }
        if(curr->HashSet.empty()){
            removeNode(curr);
        }
    }
}

void AllOne::dec(std::string key){
    if(!HashMap.count(key)){
        return;
    }
    ListNode* curr = HashMap[key];
    curr->HashSet.erase(key);
    if(curr->freq != 1){
        if(curr->prev->freq == curr->freq - 1){
            curr->prev->HashSet.insert(key);
            HashMap[key] = curr->prev;
        }
        else{
            HashMap[key] = addNode(curr->freq - 1, curr->prev, curr);
            HashMap[key]->HashSet.insert(key);
        }
    }
    else{
        HashMap.erase(key);
    }
    if(curr->HashSet.empty()){
        removeNode(curr);
    }
}

std::string AllOne::getMaxKey(){
    if(tail->prev->HashSet.empty()){
        return "";
    }
    return *(tail->prev->HashSet.begin());
}
std::string AllOne::getMinKey(){
    if(head->next->HashSet.empty()){
        return "";
    }
    return *(head->next->HashSet.begin());
}