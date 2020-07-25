#ifndef __LIST_NODE__
#define __LIST_NODE__

#include <vector>
#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v): val(v), next(nullptr) {}
};


ListNode* make_list(const std::vector<int>& data) {
    ListNode dummy(-1);
    ListNode* prev = &dummy;
    for (const int datum : data) {
        ListNode* n = new ListNode(datum);
        prev->next = n;
        prev = n;
    }
    return dummy.next;
}

void free_list(ListNode* l) {
    while (l) {
        auto n = l->next;
        delete l;
        l = n;
    }
}

void print_list(ListNode* l) {
    while (l) {
        std::cout << l->val << ",";
        l = l->next;
    }
    std::cout << std::endl;
}

#endif // __LIST_NODE__
