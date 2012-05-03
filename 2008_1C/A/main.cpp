#include <iostream>
#include <vector>
using namespace std;

long long solve(int P, int K, int L, vector<int>& F) {
  int mult = 1;
  sort(F.rbegin(), F.rend());
  long long res = 0;
  for (int i = 0; i < F.size(); i++) {
    res += F[i] * (i / K + 1);
  }
  return res;
}

int main() {
  int N; cin >> N;
  for (int t = 0; t < N; t++) {
    int P, K, L; cin >> P >> K >> L;
    vector<int> F(L);
    for (int i = 0; i < L; i++) cin >> F[i];
    long long answer = solve(P, K, L, F);
    cout << "Case #" << t+1 << ": " << answer << endl;
  }
}

