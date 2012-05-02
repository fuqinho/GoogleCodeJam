#include <iostream>
#include <vector>
using namespace std;

long long solve(int n, vector<int>& x, vector<int>& y) {
  long long res = 0;
  sort(x.begin(), x.end());
  sort(y.rbegin(), y.rend());
  for (int i=0; i<n; i++) res += (long long)x[i] * y[i];
  return res;
}

int main() {
  int T; cin >> T;
  for (int t=0; t<T; t++) {
    int n; cin >> n;
    vector<int> x(n), y(n);
    for (int i=0; i<n; i++) cin >> x[i];
    for (int i=0; i<n; i++) cin >> y[i];

    long long answer = solve(n, x, y);
    cout << "Case #" << t+1 << ": " << answer << endl;
  }
}
