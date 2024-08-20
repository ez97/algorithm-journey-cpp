// 034 : https://www.bilibili.com/video/BV1A14y1i7GY
#include <bits/stdc++.h>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <tuple>
#include <utility>

class ListNode{
public:
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution{
public:
    std::pair<ListNode*, ListNode*> reverseList(ListNode* head, ListNode* tail); // Leetcode 206(改) 反转链表 easy
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB); // Leetcode 160 相交链表 easy
    ListNode* reverseKGroup(ListNode* head, int k); // Leetcode 25 K个一组翻转链表 hard
    Node* copyRandomList(Node* head); // Leetcode 138 复制带随机指针的链表 medium
    bool isPalindrome(ListNode* head); // Leetcode 234 回文链表 easy
    ListNode* detectCycle(ListNode *head); // Leetcode 142 链表第一个入环的节点 medium
    ListNode* sortList(ListNode* head); // Leetcode 148 链表排序 medium
    
};

int main(){
    Node* head = new Node(0);
    Node* prev = head;
    for(int i = 1; i < 10; i++){
        prev->next = new Node(i);
        prev = prev->next;
    }

    prev = head;
    while(prev != nullptr){
        std::cout << prev->val << std::endl;
        prev = prev->next;
    }

    Solution s;
    Node* newhead = s.copyRandomList(head);
    prev = newhead;
    while(prev != nullptr){
        std::cout << prev->val << std::endl;
        prev = prev->next;
    }
    return 0;
}

ListNode* Solution::getIntersectionNode(ListNode *headA, ListNode *headB) {
    int len1{0}, len2{0};
    ListNode *ptr1 = headA, *ptr2 = headB;
    while(ptr1 != nullptr){
        len1++;
        ptr1 = ptr1->next;
    }
    while(ptr2 != nullptr){
        len2++;
        ptr2 = ptr2->next;
    }
    if(ptr1 != ptr2){
        return nullptr;
    }

    ptr1 = headA;
    ptr2 = headB;
    int n = abs(len1 - len2);
    if(len1 > len2){
        while(n--){
            ptr1 = ptr1->next;
        }
    }
    else{
        while(n--){
            ptr2 = ptr2->next;
        }
    }
    while(ptr1 != ptr2){
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    return ptr1;
}

std::pair<ListNode*, ListNode*> Solution::reverseList(ListNode* head, ListNode* tail){
    ListNode* curr = head;
    ListNode* prev = tail->next;
    while(prev != tail){
        ListNode* nex = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nex;
    }
    return std::make_pair(tail, head);
}

ListNode* Solution::reverseKGroup(ListNode* head, int k){
    ListNode* L = head;
    ListNode* R = L;
    for(int i = 0; i < k - 1; i++){
        R = R->next;
        if(R == nullptr){
            return head;
        }
    }
    ListNode* nex = R->next;
    
    std::tie(L, R) = reverseList(L, R);
    head = L;
    R->next = nex;
    ListNode* pre = R;
    L = R->next;

    while(L != nullptr){
        R = L;
        for(int i = 0; i < k - 1; i++){
            R = R->next;
            if(R == nullptr){
                return head;
            }
        }
        nex = R->next;
        std::tie(L, R) = reverseList(L, R);
        pre->next = L;
        R->next = nex;
        pre = R;
        L = R->next;
    }
    return head;
}

Node* Solution::copyRandomList(Node* head){
    // use map : 
    // std::map<Node*, Node*> mp;
    // Node* ptr = head;
    // while(ptr != nullptr){
    //     Node* nNode = new Node(ptr->val);
    //     mp[ptr] = nNode;
    //     ptr = ptr->next;
    // }
    // ptr = head;
    // while(ptr != nullptr){
    //     mp[ptr]->val = ptr->val;
    //     mp[ptr]->next = mp[ptr->next];
    //     mp[ptr]->random = mp[ptr->random];
    //     ptr = ptr->next;
    // }
    // return mp[head];
    
    if(head == nullptr){
        return nullptr;
    }
    Node* ptr = head;
    while(ptr != nullptr){
        Node* tmp = ptr->next;
        ptr->next = new Node(ptr->val);
        ptr->next->next = tmp;
        ptr = tmp;
    }
    ptr = head;
    while(ptr != nullptr){
        if(ptr->random == nullptr){
            ptr->next->random = nullptr;
        }
        else{
            ptr->next->random = ptr->random->next;
        }
        ptr = ptr->next->next;
    }
    Node* nhead = head->next;
    Node* prev = nhead;
    head->next = prev->next;
    ptr = prev->next;
    while(ptr != nullptr){
        // prev -> A(ptr) -> A' -> B -> B'
        prev->next = ptr->next;
        ptr->next = ptr->next->next;
        prev = prev->next;
        ptr = prev->next;
    }
    return nhead;
}

bool Solution::isPalindrome(ListNode* head){
    if(head == nullptr || head->next == nullptr){
        return true;
    }
    ListNode* slow = head;
    ListNode* fast = head->next;
    ListNode* L;
    ListNode* R;
    while (true) {
        if(fast->next == nullptr){
            R = fast;
            L = slow->next;
            break;
        }
        if(fast->next->next == nullptr){
            R = fast->next;
            L = slow->next->next;
            slow = slow->next;
            break;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    reverseList(L, R);

    L = head;
    while(R != nullptr){
        if(R->val == L->val){
            R = R->next;
            L = L->next;
        }
        else{
            return false;
        }
    }
    return true;
}

ListNode* Solution::detectCycle(ListNode *head){
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast != nullptr){
        if(fast->next == nullptr){
            return nullptr;
        }
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow){
            fast = head;
            while(fast != slow){
                fast = fast->next;
                slow = slow->next;
            }
            return fast;
        }
    }
    return nullptr;
}

std::pair<ListNode*, ListNode*> sortSublist(ListNode* L1, ListNode* R1, ListNode* L2, ListNode* R2){
    ListNode* head;
    ListNode* ptr1 = L1;
    ListNode* ptr2 = L2;
    if(L1->val < L2->val){
        head = L1;
        ptr1 = L1->next;
    }
    else{
        head = L2;
        ptr2 = L2->next;
    }
    ListNode* prev = head;
    while(prev != R1 && prev != R2){
        if(ptr1->val < ptr2->val){
            prev->next = ptr1;
            prev = ptr1;
            ptr1 = ptr1->next;
        }
        else{
            prev->next = ptr2;
            prev = ptr2;
            ptr2 = ptr2->next;
        }
    }
    ListNode* end;
    if(prev == R1){
        prev->next = ptr2;
        end = R2;
    }
    else{
        prev->next = ptr1;
        end = R1;
    }
    return std::make_pair(head, end);
}

ListNode* findEnd(ListNode* head, int sublen){
    ListNode* end = head;
    sublen--;
    while(end->next != nullptr && sublen > 0){
        end = end->next;
        sublen--;
    }
    return end;
}

ListNode* Solution::sortList(ListNode* head){
    ListNode* ptr = head;
    int len = 0;
    while(ptr != nullptr){
        ptr = ptr->next;
        len++;
    }
    ListNode *L1, *R1, *L2, *R2, *pre, *nex, *start, *end;
    for(int sublen = 1; sublen < len; sublen *= 2){
        L1 = head;
        R1 = findEnd(L1, sublen);
        L2 = R1->next;
        R2 = findEnd(L2, sublen);
        nex = R2->next;
        std::tie(start, end) = sortSublist(L1, R1, L2, R2);
        head = start;
        pre = end;
        end->next = nex;

        while(pre->next != nullptr){
            L1 = pre->next;
            R1 = findEnd(L1, sublen);
            L2 = R1->next;
            if(L2 == nullptr){
                pre->next = L1;
                break;
            }
            R2 = findEnd(L2, sublen);

            nex = R2->next;
            std::tie(start, end) = sortSublist(L1, R1, L2, R2);
            pre->next = start;
            end->next = nex;
            pre = end;
        }
    }
    return head;
}
