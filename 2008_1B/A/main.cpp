#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define REP(i,n) for(int i=0;i<(n);++i)

long long solve(int n, int A, int B, int C, int D, int x0, int y0, int M) {
  set<pair<int, int> > trees;
  // dp[i][j][k]: i個の木の座標を合計して、x(mod 3)がjでy(mod 3)がkになっているパターン数
  long long dp[4][3][3];
  memset(dp, 0, sizeof(dp));
  dp[0][0][0] = 1;

  long long x = x0, y = y0;
  for (int i = 0; i < n; i++) {
    pair<int, int> p(x, y);
    if (trees.find(p) == trees.end()) {
      REP(j, 3) REP(k, 3) dp[3][(j+x)%3][(k+y)%3] += dp[2][j][k];
      REP(j, 3) REP(k, 3) dp[2][(j+x)%3][(k+y)%3] += dp[1][j][k];
      REP(j, 3) REP(k, 3) dp[1][(j+x)%3][(k+y)%3] += dp[0][j][k];
      trees.insert(p);
    }
    x = (A * x + B) % M;
    y = (C * y + D) % M;
  }

  return dp[3][0][0];
}

int main() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) {
    int n, A, B, C, D, x0, y0, M;
    cin >> n >> A >> B >> C >> D >> x0 >> y0 >> M;

    long long answer = solve(n, A, B, C, D, x0, y0, M);
    cout << "Case #" << i+1 << ": " << answer << endl;
  }
}

