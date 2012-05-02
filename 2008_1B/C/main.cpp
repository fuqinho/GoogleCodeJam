#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct IntervalTree {
  int size;
  int K;
  vector<int> data;
  IntervalTree(int n) {
    K = n;
    size = 1;
    while (size < n) size <<= 1;
    data = vector<int>(size * 2, 0);
  }
  // find n-th empty position
  int findEmptyPos(int n) {
    return findEmptyPos(n, 0, 0, size);
  }
  int findEmptyPos(int n, int k, int l, int r) {
    if (r - l == 1) return l;
    int k1 = k * 2 + 1;
    int k2 = k * 2 + 2;
    int empty1 = (r - l) / 2 - data[k1];
    if (empty1 > n) {
      return findEmptyPos(n, k1, l, (l+r)/2);
    } else {
      return findEmptyPos(n-empty1, k2, (l+r)/2, r);
    }
  }
  // occupy x-th position
  void occupy(int x) {
    int k = x + size - 1;
    data[k] = 1;
    while (true) {
      k = (k - 1) / 2;
      data[k] = data[k*2+1] + data[k*2+2];
      if (k == 0) break;
    }
  }
};

string solve(int K, int n, vector<int> d) {
  IntervalTree tree(K);
  vector<int> result(K);

  int pos_in_empty = 0;
  for (int i = 0; i < K; i++) {
    pos_in_empty += i;
    pos_in_empty %= (K - i);
    int pos = tree.findEmptyPos(pos_in_empty);
    tree.occupy(pos);
    result[pos] = i;
  }

  ostringstream oss;
  for (int i = 0; i < d.size(); i++) {
    oss << result[d[i]-1] + 1 << " ";
  }
  return oss.str();
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    int K, n; cin >> K >> n;
    vector<int> d(n);
    for (int i = 0; i < n; i++) cin >> d[i];

    string answer = solve(K, n, d);
    cout << "Case #" << t+1 << ": " << answer << endl;
  }
}

