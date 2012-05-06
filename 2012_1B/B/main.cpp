#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cstdio>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PII;
#define REP(i,n) for(int i=0;i<(n);++i)

const int DR[] = {0, 0, -1, 1};
const int DC[] = {-1, 1, 0, 0};

// Dijkstra
double solve(int H, int N, int M, VVI& C, VVI& F) {
  vector<vector<bool> > reached(N, vector<bool>(M, false));
  vector<vector<double> > shortest(N, vector<double>(M, 100000000.0));
  priority_queue<pair<double, PII>, vector<pair<double, PII> >, greater<pair<double, PII> > > que;
  que.push(make_pair(0.0, PII(0, 0)));

  while (!que.empty()) {
    pair<double, PII> cur = que.top(); que.pop();
    double t = cur.first;
    int r = cur.second.first;
    int c = cur.second.second;
    reached[r][c] = true;

    if (r == N-1 && c == M-1) {
      return t;
    }

    for (int k = 0; k < 4; k++) {
      int nr = r + DR[k];
      int nc = c + DC[k];
      if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
      if (reached[nr][nc]) continue;

      if (C[nr][nc] >= F[r][c] + 50 && C[nr][nc] >= F[nr][nc] + 50 && C[r][c] >= F[nr][nc] + 50) {
        double time_to_clear = max(0.0, (H - (double)(C[nr][nc]-50)) / 10.0);
        double time = max(t, time_to_clear);
        if (t != 0.0 || time_to_clear != 0.0) {
          if (H - time * 10 >= F[r][c] + 20) {
            time += 1.0;
          } else {
            time += 10.0;
          }
        }
        if (time < shortest[nr][nc]) {
          que.push(make_pair(time, PII(nr, nc)));
          shortest[nr][nc] = min(shortest[nr][nc], time);
        }
      }
    }
  }
  return -1;
}

int main() {
  int T; cin >> T;
  REP(t, T) {
    int H, N, M; cin >> H >> N >> M;
    VVI C(N, VI(M));
    REP(i, N) REP(j, M) cin >> C[i][j];
    VVI F(N, VI(M));
    REP(i, N) REP(j, M) cin >> F[i][j];

    double ans = solve(H, N, M, C, F);
    printf("Case #%d: %.7f\n", t+1, ans);
  }
}

