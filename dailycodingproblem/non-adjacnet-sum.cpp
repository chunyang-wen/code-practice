#include <iostream>
#include <vector>

using namespace std;

int max_nonadjacent_sum(vector<int>& n) {
    int size = n.size();
    if (size == 1) return n[0];
    if (size == 2) return max(n[0], n[1]);
    int f0 = n[0];
    int f1 = max(n[0], n[1]);
    for (int i = 2; i < size; ++i) {
        auto cur = n[i] <= 0 ? 0: n[i];
        auto tmp = max({f1, f0 + cur, n[i]});
        f0 = f1;
        f1 = tmp;
    }
    return f1;
}

int main() {
    vector<int> n{2, 4, 6, 2, 5};
    cout << max_nonadjacent_sum(n) << endl;
    vector<int> n1{-5, -2, -1, -5};
    cout << max_nonadjacent_sum(n1) << endl;
}
