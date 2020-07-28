#include <iostream>
#include <vector>

using namespace std;


int containing_water(const vector<int>& walls) {
    int size = walls.size();
    int max_index = -1;
    int max_num = INT_MIN;
    for (int i = 0; i < size; ++i) {
        if (walls[i] >= max_num) {
            max_num = walls[i];
            max_index = i;
        }
    }

    int cur_max = 0;
    int water = 0;
    for (int i = 0; i < max_index; ++i) {
        water += max(cur_max - walls[i], 0);
        cur_max = max(cur_max, walls[i]);
    }
    cur_max = 0;
    for (int i = size - 1; i > max_index; --i) {
        water += max(cur_max - walls[i], 0);
        cur_max = max(cur_max, walls[i]);
    }
    return water;
}


void test() {
    cout << containing_water({2, 1, 2}) << endl;
    cout << containing_water({3, 0, 1, 3, 0, 5}) << endl;
}


int main() {
    test();
    return 0;
}
