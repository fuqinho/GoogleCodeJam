#include <iostream>
#include <vector>
using namespace std;

int solve(int N, vector<int>& a, vector<int>& b) {
  vector<bool> took1(N, false);
  vector<bool> took2(N, false);

  // assign higher priority to a level which has higher 2-star rating
  vector<pair<int, int> > req(N);
  for (int i=0; i<N; i++) req[i] = make_pair(b[i], a[i]);
  sort(req.rbegin(), req.rend());

  int cur_stars = 0;
  int ans = 0;
  while (cur_stars < N * 2) {
    bool found = false;
    // search level2
    for (int i=0; i<N; i++) {
      if (!took2[i] && cur_stars >= req[i].first) {
        took2[i] = true;
        if (took1[i]) {
          cur_stars += 1;
        } else {
          cur_stars += 2;
          took1[i] = true;
        }
        ans ++;
        found = true;
        break;
      }
    }
    if (found) continue;

    // search level1
    for (int i=0; i<N; i++) {
      if (!took1[i] && cur_stars >= req[i].second) {
        took1[i] = true;
        cur_stars += 1;
        ans ++;
        found = true;
        break;
      }
    }
    if (found) continue;

    return -1;
  }
  return ans;
}

int main() {
  int T; cin >> T;
  for (int t=0; t<T; t++) {
    int N; cin >> N;
    vector<int> a(N), b(N);
    for (int i=0; i<N; i++) cin >> a[i] >> b[i];

    int ans = solve(N, a, b);
    if (ans != -1) {
      cout << "Case #" << (t+1) << ": " << ans << endl;
    } else {
      cout << "Case #" << (t+1) << ": " << "Too Bad" << endl;
    }
  }
}
