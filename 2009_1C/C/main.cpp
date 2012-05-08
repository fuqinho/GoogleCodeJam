#include <iostream>
#include <vector>
using namespace std;

const int INF = 100000000;
const int MAX_Q = 100;

int memo[MAX_Q+2][MAX_Q+2];

int dfs(vector<int>& p, int left, int right) {
  if (right - left == 1) return 0;
  if (memo[left][right] != -1) return memo[left][right];

  int res = INF;
  for (int i = 1; i < right - left; i++) {
    int cost = (p[right] - p[left] - 2) + dfs(p, left, left+i) + dfs(p, left+i, right);
    res = min(res, cost);
  }
  return memo[left][right] = res;
}

int main() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) {
    int P, Q; cin >> P >> Q;
    vector<int> p(Q+2);
    p[0] = 0;
    for (int j = 0; j < Q; j++) cin >> p[j+1]; 
    p[Q+1] = P+1;
    
    memset(memo, -1, sizeof(memo));
    int ans = dfs(p, 0, Q+1);
    cout << "Case #" << i+1 << ": " << ans << endl;
  }
}
