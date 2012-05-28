#include <iostream>
#include <vector>
using namespace std;

void solve(int N, int W, int L, vector<int>& r) {
  // ri[x]: pair({radius of i-th person}, {i});
  vector<pair<int, int> > ri(N);
  for (int i = 0; i < N; i++) ri[i] = make_pair(r[i], i);

  // sort members by their radius (descending order)
  sort(ri.rbegin(), ri.rend());

  // placed position for i-th person
  vector<int> xs(N);
  vector<int> ys(N);

  for (int i = 0; i < N; i++) {
    while (true) {
      // select position randomly
      int x = rand() % (W+1);
      int y = rand() % (L+1);

      // check if this poisition doesn't conflict with others
      bool canPlace = true;
      for (int j = 0; j < i; j++) {
        long long diff_x = abs(xs[ri[j].second] - x);
        long long diff_y = abs(ys[ri[j].second] - y);
        long long sum_radius = ri[i].first + ri[j].first;
        if (diff_x * diff_x + diff_y * diff_y < sum_radius * sum_radius) {
          canPlace = false;
          break;
        }
      }

      // place the person at (x, y) if there's no conflict
      if (canPlace) {
        xs[ri[i].second] = x;
        ys[ri[i].second] = y;
        break;
      }
    }
  }

  // print positions
  for (int i = 0; i < N; i++) {
    cout << xs[i] << " " << ys[i] << " ";
  }
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    // read input data
    int N, W, L; cin >> N >> W >> L;
    vector<int> r(N);
    for (int i = 0; i < N; i++) cin >> r[i];

    // solve and print answer
    cout << "Case #" << t+1 << ": ";
    solve(N, W, L, r);
    cout << endl;
  }
}
