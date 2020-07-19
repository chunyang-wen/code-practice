#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

bool in_circle(double x, double y) {
    return x*x + y*y <= 1;
}

double estimator_pi() {
    const int COUNT = 500000000;
    int number = 0;
    srand(time(NULL));
    for (int i = 0; i < COUNT; ++i) {
        double x = rand()*1.0 / RAND_MAX;
        double y = rand()*1.0 / RAND_MAX;
        number += in_circle(x, y);
    }
    return 4.0 * number / COUNT;
}

int main() {


    cout << setprecision(4) << "PI = " << estimator_pi() << endl;
    return EXIT_SUCCESS;
}
