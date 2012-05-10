#include <iostream>
#include <numeric>
using namespace std;

const int MOD = 100003;
const int MAX_N = 500;

int C[MAX_N+1][MAX_N+1];
long long dp[MAX_N+1][MAX_N+1];
int ans[MAX_N+1];

void init() {
  // calc combination numbers;
  for (int i = 0; i <= MAX_N; i++) {
    for (int j = 0; j <= MAX_N; j++) {
      if (j > i) {
        C[i][j] = 0;
      }
      else if (j == 0 || j == i) {
        C[i][j] = 1;
      }
      else {
        C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
      }
    }
  }
  // dynamic programming
  for (int i = 2; i <= MAX_N; i++) dp[i][1] = 1;
  for (int i = 2; i <= MAX_N; i++) {
    for (int j = 2; j < i; j++) {
      for (int k = 1; k < j; k++) {
        if (i-j >= j-k) {
          dp[i][j] += dp[j][k] * C[i-j-1][j-k-1];
          dp[i][j] %= MOD;
        }
      }
    }
  }
  // calc answer
  for (int i = 1; i <= MAX_N; i++) {
    ans[i] = accumulate(dp[i], dp[i]+i, 0) % MOD;
  }
}

int main() {
  int T; cin >> T;
  init();
  for (int t = 0; t < T; t++) {
    int n; cin >> n;
    cout << "Case #" << t+1 << ": " << ans[n] << endl;
  }
}
