#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

double solve(int A, int B, vector<double>& P) {
  double retype = B + 1;
  // expected types when press enter right away
  double e = 1 + retype; 

  // compare with expectd types for each number of backspaces
  double correct_p = 1.0;
  for (int i=0; i<A; i++) {
    correct_p *= P[i];
    int backspaces = A - (i+1);
    int types_to_end = backspaces + B - (i+1) + 1;
    e = min(e, correct_p * types_to_end + (1 - correct_p) * (types_to_end + retype));
  }
  return e;
}

int main() {
  int T; cin >> T;
  for (int t=0; t<T; t++) {
    int A, B; cin >> A >> B;
    vector<double> P(A);
    for (int i=0; i<A; i++) cin >> P[i];

    double ans = solve(A, B, P);
    printf("Case #%d: %.6f\n", t+1, ans);
  }
}
