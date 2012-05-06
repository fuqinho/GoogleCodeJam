#include <iostream>
#include <vector>
using namespace std;

bool dfs(int v, vector<bool>& used, vector<vector<int> >& G) {
  if (used[v]) return true;
  
  used[v] = true;
  for (int i = 0; i < G[v].size(); i++) {
    if (dfs(G[v][i], used, G)) return true;
  }
  return false;
}

bool solve(int N, vector<vector<int> >& G) {
  vector<bool> used(N);
  for (int i = 0; i < N; i++) {
    fill(used.begin(), used.end(), false);
    if (dfs(i, used, G)) return true;
  }
  return false;
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    int N; cin >> N;
    vector<vector<int> > G(N);
    for (int i = 0; i < N; i++) {
      int M; cin >> M;
      for (int j = 0; j < M; j++) {
        int tmp; cin >> tmp;
        G[i].push_back(tmp - 1);
      }
    }
    bool ans = solve(N, G);
    cout << "Case #" << t+1 << ": " << (ans ? "Yes" : "No") << endl;
  }
}

