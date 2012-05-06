#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;

vector<double> solve(double D, int N, int A, vector<double>& t, vector<double>x, vector<double>& a) {
  // calc goal time of other car
  double othergoal = 0.0;
  for (int i = 1; i < N; i++) {
    if (D >= x[i-1] && D <= x[i]) {
      othergoal = t[i-1] + (t[i]-t[i-1]) * (D-x[i-1]) / (x[i]-x[i-1]);
    }
  }
  vector<double> res(A, 0.0);
  for (int i = 0; i < A; i++){
    // calc start time to accel constantly without catch up the other car
    double t0 = 0.0;
    for (int j = 0; j < N; j++) {
      if (t[j] <= othergoal) {
        double tstart = t[j] - sqrt(2.0 * x[j] / a[i]);
        t0 = max(t0, tstart);
      }
    }
    res[i] = max(othergoal, sqrt(2 * D / a[i]) + t0);
  }
  return res;
}

int main() {
  int T; cin >> T;
  for (int c=0; c<T; c++) {
    double D; int N, A; cin >> D >> N >> A;
    vector<double> t(N), x(N);
    for (int i=0; i<N; i++) cin >> t[i] >> x[i];
    vector<double> a(A);
    for (int i=0; i<A; i++) cin >> a[i];

    vector<double> ans = solve(D, N, A, t, x, a);
    printf("Case #%d:\n", c+1);
    for (int i=0; i<A; i++) printf("%.7f\n", ans[i]);
  }
}
