#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v): val(v), next(nullptr) {}
};

int joint_node(ListNode* l, ListNode* r) {
    ListNode* n = l;
    int len1 = 0, len2 = 0;
    while (n) {++len1; n = n->next;}
    n = r;
    while (n) {++len2; n = n->next;}
    if (len1 < len2) {
        swap(len1, len2);
        swap(l, r);
    }
    while (len1 > len2) { l = l->next; --len1;}
    cout << "l->val: " << l->val << endl;
    cout << "r->val: " << r->val << endl;
    while (l && r && l->val != r->val) {
        l = l->next;
        r = r->next;
    }
    if (!l || !r) return -1;
    return l->val;
}

ListNode* make_list(const vector<int>& data) {
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

int main() {

    auto l = make_list({2,3,4,5});
    auto r = make_list({6,8,3,4,5});
    cout << joint_node(l, r) << endl;
    free_list(l); free_list(r);
    return 0;
}
