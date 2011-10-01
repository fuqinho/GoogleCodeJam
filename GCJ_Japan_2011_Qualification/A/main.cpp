#include <iostream>
#include <vector>
using namespace std;

#define dump(x) cerr << #x << " = " << (x) << endl;

int solve(int M, int C, int W, vector<int>& A, vector<int>& B) {
    for (int i = C - 1; i >= 0; i--) {
        if (W <= B[i]) {
            W += A[i] - 1;
        } else if (W <= A[i] + B[i] - 1) {
            W -= B[i];
        }
    }
    return W;
}

int main() {
    int T, M, C, W, tmpA, tmpB;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cin >> M >> C >> W;
        vector<int> A;
        vector<int> B;
        for (int j = 0; j < C; j++) {
            cin >> tmpA >> tmpB;
            A.push_back(tmpA);
            B.push_back(tmpB);
        }
        int answer = solve(M, C, W, A, B);
        cout << "Case #" << i << ": " << answer << endl;
    }
}
