#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;

struct BinaryIndexedTree {
  vector<int> bit;
  BinaryIndexedTree(int n) {
    bit = vector<int>(n+1);
  }
  int sum(int i) {
    i++;
    int res = 0;
    while (i > 0) {
      res += bit[i];
      res %= MOD;
      i -= (i & -i);
    }
    return res;
  }
  void add(int i, int x) {
    i++;
    while (i < bit.size()) {
      bit[i] += x;
      bit[i] %= MOD;
      i += (i & -i);
    }
  }
};

int solve(int n, int m, int X, int Y, int Z, vector<int>& A) {
  // generate S
  vector<int> S(n);
  for (int i = 0; i < n; i++) {
    S[i] = A[i % m];
    A[i % m] = ((long long)X * A[i % m] + (long long)Y * (i + 1)) % Z;
  }
  // normalize S
  vector<int> tmp = S;
  sort(tmp.begin(), tmp.end());
  tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
  for (int i = 0; i < n; i++) {
    S[i] = lower_bound(tmp.begin(), tmp.end(), S[i]) - tmp.begin();
  }
  int N = tmp.size();

  // DP with binary indexed tree
  BinaryIndexedTree bit(N);
  for (int i = 0; i < n; i++) {
    int patterns = 1;
    if (S[i] > 0) patterns += bit.sum(S[i] - 1);
    bit.add(S[i], patterns);
  }
  return bit.sum(N-1);
}

int main() {
  int N; cin >> N;
  for (int t = 0; t < N; t++) {
    int n, m, X, Y, Z; cin >> n >> m >> X >> Y >> Z;
    vector<int> A(m);
    for (int i = 0; i < m; i++) cin >> A[i];

    int answer = solve(n, m, X, Y, Z, A);
    cout << "Case #" << t+1 << ": " << answer << endl;
  }
}

