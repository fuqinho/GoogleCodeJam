#include <iostream>
#include <vector>
#include <numeric>
#include <cstdio>
using namespace std;

const double EPS = 1e-10;

// find necessary points by binary search
double threshold(vector<int>& S) {
  int total = accumulate(S.begin(), S.end(), 0);
  double lb = 0.0, ub = total;
  while (ub - lb > EPS) {
    double mid = (lb + ub) / 2;
    double sum = 0;
    for (int i = 0; i < S.size(); i++) sum += max(0.0, mid - S[i]);
    if (sum >= total) ub = mid;
    else lb = mid;
  }
  return ub;
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    int N; cin >> N;
    vector<int> S(N);
    for (int i = 0; i < N; i++) cin >> S[i];

    printf("Case #%d: ", t+1);
    double needed = threshold(S); 
    int total = accumulate(S.begin(), S.end(), 0);
    for (int i = 0; i < N; i++) {
      double p = (needed - S[i]) / total;
      if (p >= 0) {
        printf("%.6f ", p * 100);
      } else {
        printf("%.6f ", 0.0);
      }
    }
    printf("\n");
  }
}

