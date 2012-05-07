#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 100, MAX_M = 100;
int N, M;
vector<int> A, B;
vector<long long>a, b;
long long memo[MAX_N][MAX_M];

long long dfs(int i, int j, long long used_a, long long used_b) {
  if (i == N || j == M) return 0;
  if (used_a == 0 && used_b == 0) {
    if (memo[i][j] != -1) return memo[i][j];
  }

  long long sum = 0;
  if (A[i] == B[j]) {
    long long common = min(a[i] - used_a, b[j] - used_b);
    if (a[i] - used_a == b[j] - used_b) {
      sum = common + dfs(i+1, j+1, 0, 0);
    } else if (a[i] - used_a > b[j] - used_b) {
      sum = common + dfs(i, j+1, used_a + common, 0);
    } else {
      sum = common + dfs(i+1, j, 0, used_b + common);
    }
  } else {
    sum = max(dfs(i+1, j, 0, used_b), dfs(i, j+1, used_a, 0));
  }

  if (used_a == 0 && used_b == 0) memo[i][j] = sum;
  return sum;
}

int main() {
  int T; cin >> T;
  for (int t=0; t<T; t++) {
    cin >> N >> M;
    a = vector<long long>(N), A = vector<int>(N);
    for (int i=0; i<N; i++) cin >> a[i] >> A[i];
    b = vector<long long>(M), B = vector<int>(M);
    for (int i=0; i<M; i++) cin >> b[i] >> B[i];

    for (int i=0; i<N; i++) for (int j=0; j<M; j++) memo[i][j] = -1;
    long long ans = dfs(0, 0, 0, 0);
    cout << "Case #" << t+1 << ": " << ans << endl;
  }
}
