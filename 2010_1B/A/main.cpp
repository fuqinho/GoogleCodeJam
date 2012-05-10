#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define REP(i,n) for(int i=0;i<(n);++i)

int solve(vector<string>& e, vector<string>& n) {
  set<string> dirs;
  dirs.insert("");
  REP(i, e.size()) {
    REP(j, e[i].size()) {
      if (e[i][j] == '/') dirs.insert(e[i].substr(0, j));
      dirs.insert(e[i]);
    }
  }
  int initial = dirs.size();

  REP(i, n.size()) {
    REP(j, n[i].size()) {
      if (n[i][j] == '/') dirs.insert(n[i].substr(0, j));
      dirs.insert(n[i]);
    }
  }
  return dirs.size() - initial;
}

int main() {
  int T; cin >> T;
  REP(t, T) {
    int N, M; cin >> N >> M;
    vector<string> e(N);
    REP(i, N) cin >> e[i];
    vector<string> n(M);
    REP(i, M) cin >> n[i];

    int ans = solve(e, n);
    cout << "Case #" << t+1 << ": " << ans << endl;
  }
}
