#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef priority_queue<int, vector<int>, less<int>> MaxPQ;
typedef priority_queue<int, vector<int>, greater<int>> MinPQ;

void fix_queue(MaxPQ& left, MinPQ& right) {
    if (right.empty()) {
        while (left.size() > right.size()) {
            right.push(left.top());
            left.pop();
        }
    } else {
        while (!left.empty() && left.top() > right.top()) {
            right.push(left.top());
            left.pop();
        }
    }
    while (left.size() > right.size()) {
        right.push(left.top());
        left.pop();
    }
    while (left.size() < right.size()) {
        left.push(right.top());
        right.pop();
    }
}

void running_median(const vector<int>& data) {

    MaxPQ left;
    MinPQ right;
    for (int datum: data) {
        left.push(datum);
        fix_queue(left, right);
        if (left.size() == right.size()) {
            cout << (left.top() + right.top()) / 2.0 << ", ";
        } else if (left.size() > right.size()) {
            cout << left.top() << ", ";
        } else {
            cout << right.top() << ", ";
        }
    }
    cout << endl;
}


int main() {
    running_median({2, 1, 5, 7, 2, 0, 5});
    return 0;
}
