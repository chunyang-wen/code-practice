#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;


int minimum_classroom(vector<pair<int, int>> time) {

    sort(begin(time), end(time));
    int min_begin = INT_MAX, max_end = INT_MIN;
    for (auto& p : time) {
        min_begin = min(min_begin, p.first);
        max_end = max(max_end, p.second);
    }

    int max_result = INT_MIN;
    for (int i = min_begin; i < max_end; ++i) {
        int cur = 0;
        for (auto& p : time) {
            if (i <= p.first) {
                break;
            }
            if (i <= p.second && i >= p.first) {
                ++cur;
            }
        }
        max_result = max(max_result, cur);
    }

    return max_result;
}


int main() {
    cout << minimum_classroom({ {0, 50}, {30, 75}, {60, 150} }) << endl;
    cout << minimum_classroom({ {0, 120}, {30, 75}, {75, 80} }) << endl;
    return 0;
}
