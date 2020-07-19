#include <iostream>
#include <string>
using namespace std;

int decode_ways(const string& input) {
    int count = 0;
    int size = input.size();
    function<void(int)> decode = [&](int start) {
        if (start == size) {
            ++count;
            return;
        }
        if (input[start] == '0') return;
        decode(start+1);
        if (start+1 >= size) return;
        int next = start+1;
        if (input[start] == '1' && input[next] >= '0' && input[next] <= '9') {
            decode(start+2);
        }
        if (input[start] == '2' && input[next] >= '0' && input[next] <= '6') {
            decode(start+2);
        }
    };
    decode(0);
    return count;
}

int main() {
    string a = "101";
    cout << decode_ways(a) << endl;
}
