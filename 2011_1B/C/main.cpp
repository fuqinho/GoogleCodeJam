#include <iostream>
#include <vector>
using namespace std;

#define REP(i,n) for(int i=0;i<(n);++i)

pair<int, vector<int> > solve(int N, int M, const vector<int>& U, const vector<int>& V) {
  // find all cuts and sort by its size
  vector<pair<int, pair<int, int> > > E;
  REP(i, M) {
    E.push_back(make_pair(V[i]-U[i], make_pair(U[i], V[i])));
    E.push_back(make_pair(N+U[i]-V[i], make_pair(V[i], U[i])));
  }
  sort(E.begin(), E.end());

  // get polygons by descending order of the size of cut
  vector<bool> exist(N, true);
  vector<vector<int> > polygons;
  REP(i, E.size()) {
    int a = E[i].second.first;
    int b = E[i].second.second;
    if (!exist[a] || !exist[b]) continue;

    vector<int> v;
    v.push_back(b);
    v.push_back(a);
    if (b < a) b += N;
    for (int i = a+1; i < b; i++) {
      if (exist[i%N]) {
        v.push_back(i%N);
        exist[i%N] = false;
      }
    }
    if (v.size() > 2) polygons.push_back(v);
  }
  reverse(polygons.begin(), polygons.end());

  // calc C by finding minimum polygon
  int C = N;
  REP(i, polygons.size()) C = min(C, (int)polygons[i].size());

  vector<int> color(N, -1);
  color[polygons[0][0]] = 1;
  color[polygons[0][1]] = 2;
  REP(i, polygons.size()) {
    // use C colors for front C vertices
    int v = 2;
    for (int c = 1; c <= C; c++) {
      if (c != color[polygons[i][0]] && c != color[polygons[i][1]]) {
        color[polygons[i][v]] = c;
        v++;
      }
    }
    // color remaining vertices
    for (int j = C; j < polygons[i].size(); j++) {
      int c = 1;
      while (c == color[polygons[i][j-1]] || 
          (j == polygons[i].size()-1 && c == color[polygons[i][0]])) {
        c++;
      }
      color[polygons[i][j]] = c;
    }
  }
  return make_pair(C, color);
}

int main() {
  int T; cin >> T;
  REP(t, T) {
    int N, M; cin >> N >> M;
    vector<int> U(M), V(M);
    REP(i, M) cin >> U[i];
    REP(i, M) cin >> V[i];
    REP(i, M) {
      U[i]--; V[i]--;
    }

    pair<int, vector<int> > ans = solve(N, M, U, V);
    cout << "Case #" << t+1 << ": " << ans.first << endl;
    REP(i, ans.second.size()) cout << ans.second[i] << " ";
    cout << endl;
  }
}
