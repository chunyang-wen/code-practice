#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>
#include <iterator>
#include <utility>

using namespace std;

/*
 * [10, 5, 2, 7, 8, 7]
 *
 */
vector<int> maximum_sub_k(const vector<int>& arr, int k) {
    vector<int> result;
    if (arr.empty()) return result;
    deque<pair<int, int> > dq;  // <value, index>
    dq.push_back(make_pair(arr[0], 0));
    int size = arr.size();
    for (int i = 1; i < size; ++i) {
        if (i >= k) {
            result.push_back(dq.front().first);
        }
        if (dq.empty() || dq.back().first > arr[i]) {
            dq.push_back(make_pair(arr[i], i));
        } else {
            while (!dq.empty() && dq.back().first < arr[i]) dq.pop_back();
            dq.push_back(make_pair(arr[i], i));
        }
        if (i - dq.front().second >= k) dq.pop_front();
    }
    result.push_back(dq.front().first);
    return result;

}

void test(const vector<int>& arr, int k) {
    auto result = maximum_sub_k(arr, k);
    copy(begin(result), end(result), ostream_iterator<int>(cout, ","));
    cout << endl;
}


int main() {

    test({10, 5, 2, 7, 8, 7}, 3);
    test({10, 9, 8, 7, 6, 5}, 3);
    test({5,6,7,8,9,10}, 3);
    test({1,2,3,4,5,6,7}, 1);

    return 0;
}
