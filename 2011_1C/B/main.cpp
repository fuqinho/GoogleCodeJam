#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

typedef long long LL;
#define REP(i,n) for(int i=0;i<(n);++i)

LL solve(int L, LL t, int N, int C, vector<int>& a) {
  // a[i]: necessary time without booster
  REP(i, C) a[i] *= 2;

  vector<pair<int, int> > count(C);
  REP(i, C) count[i] = make_pair(a[i], N / C + (i < N % C ? 1 : 0));

  LL res = 0;
  REP(i, C) res += (LL)count[i].second * a[i];

  if (t < res) {
    int cycle_time = accumulate(a.begin(), a.end(), 0);
    int cycles = t / cycle_time;
    REP(i, C) count[i].second -= cycles;
    int remaining_time = t % cycle_time;
    
    int rem = 0;
    REP(i, C) {
      if (remaining_time == 0) {
        break;
      } else {
        count[i].second --;
        if (remaining_time < a[i]) {
          count.push_back(make_pair(a[i] - remaining_time, 1));
          break;
        } else {
          remaining_time -= a[i];
        }
      }
    }

    sort(count.rbegin(), count.rend());
    REP(i, count.size()) {
      if (L == 0) break;
      int booster_num = min(L, count[i].second);
      res -= booster_num * (count[i].first / 2);
      L -= booster_num;
    }
  }
  return res; 
}

int main() {
  int T; cin >> T;
  REP(i, T) {
    int L, N, C; LL t;
    cin >> L >> t >> N >> C;
    vector<int> a(C);
    REP(j, C) cin >> a[j];

    LL ans = solve(L, t, N, C, a);
    cout << "Case #" << i+1 << ": " << ans << endl;
  }
}
