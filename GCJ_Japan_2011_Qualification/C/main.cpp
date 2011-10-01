#include <iostream>
#include <vector>
using namespace std;

#define dump(x) cerr << #x << " = " << (x) << endl;

int solve(unsigned long long N) {
    int result = 0;
    while (N != 0) {
        if (N & 1) {
            result += 1;
        } else {
            result += 2;
            N -= 2;
        }
        N = (N >> 1);
    }
    return result;
}

int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        unsigned long long N;
        cin >> N;
        int answer = solve(N);
        cout << "Case #" << i << ": " << answer << endl;
    }
}
