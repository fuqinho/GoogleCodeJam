#include <iostream>
#include <vector>
using namespace std;

int solve(int D, int I, int M, int N, vector<int>& a) {
  const int INF = 100000000;

  // dp[i][j]: minimum cost to paint color j for i-th pixel
  vector<vector<int> > dp(N+1, vector<int>(256, INF));
  for (int i = 0; i < 256; i++) dp[0][i] = 0;
  
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 256; j++) {
      // delete
      dp[i+1][j] = min(dp[i+1][j], dp[i][j] + D);

      // insert and modify
      if (M == 0) {
        dp[i+1][j] = min(dp[i+1][j], dp[i][j] + abs(j - a[i]));
      } else {
        for (int j_next = 0; j_next < 256; j_next++) {
          int insert_cost = max(0, (abs(j - j_next) - 1) / M) * I;
          dp[i+1][j_next] = min(dp[i+1][j_next], 
              dp[i][j] + insert_cost + abs(j_next - a[i]));
        }
      }
    }
  }
  return *min_element(dp[N].begin(), dp[N].end());
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    int D, I, M, N; cin >> D >> I >> M >> N;
    vector<int> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];

    int ans = solve(D, I, M, N, a);
    cout << "Case #" << t+1 << ": " << ans << endl;
  }
}
