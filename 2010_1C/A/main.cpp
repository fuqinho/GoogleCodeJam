#include <iostream>
#include <vector>
using namespace std;

int solve(int N, vector<int>& A, vector<int>& B) {
  int res = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (A[j] < A[i] && B[j] > B[i]) res++;
    }
  }
  return res;
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    int N; cin >> N;
    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++) cin >> A[i] >> B[i];

    int ans = solve(N, A, B);
    cout << "Case #" << t+1 << ": " << ans << endl;
  }
}
