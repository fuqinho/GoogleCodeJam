#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

typedef pair<int, int> PII;
#define REP(i,n) for(int i=0;i<(n);++i)

int char2int(int c) {
  if (c >= '0' && c <= '9') return c - '0';
  else return c - 'A' + 10;
}

map<int, int> solve(int M, int N, vector<string>& B) {
  vector<vector<bool> > board(M, vector<bool>(N));
  REP(i, M) REP(j, N) {
    if (char2int(B[i][j/4]) & (1 << (3-j%4))) board[i][j] = true;
  }

  vector<vector<int> > larg(M, vector<int>(N, 1));
  for (int i = 1; i < M; i++) {
    for (int j = 1; j < N; j++) {
      if (board[i][j] != board[i-1][j] && board[i][j] != board[i][j-1] && board[i][j] == board[i-1][j-1]) {
        larg[i][j] = min(larg[i-1][j-1], min(larg[i-1][j], larg[i][j-1])) + 1;
      }
    }
  }

  set<pair<int, PII> > s;
  REP(i, M) REP(j, N) s.insert(make_pair(-larg[i][j], PII(i, j)));

  map<int, int> res;
  while (!s.empty()) {
    pair<int, PII> d = *s.begin();
    int w = -d.first;
    int r = d.second.first;
    int c = d.second.second;
    res[w]++;

    // remove
    for (int i = r - w + 1; i <= r; i++) {
      for (int j = c - w + 1; j <= c; j++) {
        s.erase(make_pair(-larg[i][j], PII(i, j)));
        larg[i][j] = 0;
      }
    }
    // update
    for (int i = r - w + 1; i <= min(M - 1, r + w); i++) {
      for (int j = c - w + 1; j <= min(N - 1, c + w); j++) {
        if (larg[i][j] == 0) continue;
        int larg_new = min(larg[i][j], max(i - r, j - c));
        if (larg_new != larg[i][j]) {
          s.erase(make_pair(-larg[i][j], PII(i, j)));
          larg[i][j] = larg_new;
          s.insert(make_pair(-larg[i][j], PII(i, j)));
        }
      }
    }
  }
  return res;
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    int M, N; cin >> M >> N;
    vector<string> B(M);
    for (int i = 0; i < M; i++) cin >> B[i];

    map<int, int> ans = solve(M, N, B);
    cout << "Case #" << t+1 << ": " << ans.size() << endl;
    for (map<int, int>::reverse_iterator i = ans.rbegin(); i != ans.rend(); i++) {
      cout << (*i).first << " " << (*i).second << endl;
    }
  }
}
