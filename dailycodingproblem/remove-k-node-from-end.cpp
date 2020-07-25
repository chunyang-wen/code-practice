#include <iostream>
#include <cassert>
#include "utility.hpp"

using namespace std;

/*
 * k = 2
 * 1 -> 2 -> 3 -> 4 -> 5
 */
ListNode* remove_k_node_from_end(ListNode* head, int k) {
    ListNode* fast = head;
    ListNode* slow = head;
    ListNode* prev = head;
    int steps = k - 1;
    while (steps-- > 0) fast = fast->next;
    cout << "fast->val = " << fast->val << endl;
    assert(fast != nullptr);
    while (fast->next != nullptr) {
        fast = fast->next;
        prev = slow;
        slow = slow->next;
    }
    prev->next = slow->next;
    if (slow == head) head = head->next;
    slow->next = nullptr;
    delete slow;
    return head;
}

int main(int argc, char* argv[]) {

    ListNode* node = make_list({1,2,3,4,5});
    int k = stol(argv[1]);
    node = remove_k_node_from_end(node, k);
    print_list(node);
    cout << endl;


    free_list(node);


    return 0;
}
