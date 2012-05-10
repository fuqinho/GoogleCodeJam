#include <iostream>
#include <vector>
using namespace std;

int solve(int N, int K, int B, int T, vector<int>& X, vector<int>& V) {
  int swaps = 0;
  int late_chicks = 0;
  int ontime_chicks = 0;
  for (int i = X.size() - 1; i >= 0; i--) {
    if (B - X[i] > V[i] * T) {
      late_chicks++;
    } else {
      swaps += late_chicks;
      ontime_chicks++;
      if (ontime_chicks == K) break;
    }
  }
  if (ontime_chicks >= K) return swaps;
  else return -1;
}

int main() {
  int C; cin >> C;
  for (int c = 0; c < C; c++) {
    int N, K, B, T; cin >> N >> K >> B >> T;
    vector<int> X(N), V(N);
    for (int i = 0; i < N; i++) cin >> X[i];
    for (int i = 0; i < N; i++) cin >> V[i];
    
    int ans = solve(N, K, B, T, X, V);
    if (ans != -1) {
      cout << "Case #" << c+1 << ": " << ans << endl;
    } else {
      cout << "Case #" << c+1 << ": " << "IMPOSSIBLE" << endl;
    }
  }
}
