#include <iostream>
#include <vector>

int ways(const std::vector<int>& steps, int target) {
    std::vector<int> positions(target + 1, 0);
    positions[0] = 1;
    for (int i = 1; i <= target; ++i) {
        for (auto step : steps) {
            if (i - step >= 0) {
                positions[i] += positions[i-step];
            }
        }
        std::cout << "pos[" << i << "] = " << positions[i] << std::endl;
    }
    return positions[target];
}

int main() {

    std::cout << ways({1,2}, 4) << std::endl;

    return EXIT_SUCCESS;
}
