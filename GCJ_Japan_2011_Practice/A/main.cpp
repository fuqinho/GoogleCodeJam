#include <iostream>
using namespace std;

string solve(unsigned int N, unsigned int K) {
    return (K & ((1 << N) - 1)) == ((1 << N) - 1) ? "ON" : "OFF";
}

int main() {
    // Read from standard input
    unsigned int T, N, K;
    cin >> T;
    for (unsigned int i = 1; i <= T; i++) {
        cin >> N >> K;
        // solve and print answer to standard output
        string answer = solve(N, K);
        cout << "Case #" << i << ": " << answer << endl;
    }
}
