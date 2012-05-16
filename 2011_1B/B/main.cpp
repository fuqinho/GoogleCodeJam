#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

const long long INF = 10000000000000;

double solve(int C, int D, vector<pair<int, int> >& V) {
  sort(V.begin(), V.end());
  D *= 2;
  for (int i = 0; i < C; i++) V[i].first *= 2;

  long long lb = -1;
  long long ub = INF;
  while (ub - lb > 1) {
    long long mid = (lb + ub) / 2;
    bool isOK = true;
    long long left = -INF;
    for (int i = 0; i < C; i++) {
      left = max(left + D, V[i].first - mid);
      if (left + (long long)(V[i].second - 1) * D <= V[i].first + mid) {
        left += (long long)(V[i].second - 1) * D;
      } else {
        isOK = false;
        break;
      }
    }
    if (isOK) {
      ub = mid;
    } else {
      lb = mid;
    }
  }
  return (double)ub / 2;
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    int C, D; cin >> C >> D;
    vector<pair<int, int> > V(C);
    for (int i = 0; i < C; i++) {
      cin >> V[i].first >> V[i].second;
    }

    double ans = solve(C, D, V);
    printf("Case #%d: %.1f\n", t+1, ans);
  }
}
