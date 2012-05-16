#include <iostream>
#include <vector>
using namespace std;

#define REP(i,n) for(int i=0;i<(n);++i)

const int DR[] = {0, 0, 1, 1};
const int DC[] = {0, 1, 0, 1};
const char RED[] = {'/', '\\', '\\', '/'};

void solve(int R, int C, vector<string>& tile) {
  REP(i, R) {
    REP(j, C) {
      if (tile[i][j] == '#') {
        REP(k, 4) {
          int r = i + DR[k];
          int c = j + DC[k];
          if (r < R && c < C && tile[r][c] == '#') {
            tile[r][c] = RED[k];
          } else {
            cout << "Impossible" << endl;
            return;
          }
        }
      }
    }
  }
  REP(i, R) cout << tile[i] << endl;
}

int main() {
  int T; cin >> T;
  REP(t, T) {
    int R, C; cin >> R >> C;
    vector<string> tile(R);
    REP(i, R) cin >> tile[i];

    cout << "Case #" << t+1 << ":" << endl;
    solve(R, C, tile);
  }
}
