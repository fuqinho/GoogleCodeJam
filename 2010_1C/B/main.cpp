#include <iostream>
#include <cmath>
using namespace std;

int solve(int L, int P, int C) {
  int t = 1;
  while ((long long)L * C < P) {
    L *= C;
    t++;
  }
  return (int)ceil(log2(t));;
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    int L, P, C; cin >> L >> P >> C;

    int ans = solve(L, P, C);
    cout << "Case #" << t+1 << ": " << ans << endl;
  }
}
