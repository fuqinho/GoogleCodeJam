#include <iostream>
#include <vector>
using namespace std;

// O(n) solution
bool solve(int N, vector<int>& d, vector<int>& l, int D)
{
  // reach[i]: the longest distance which can be reached from i-th vine
  vector<int> reach(N, 0);
  reach[0] = d[0];

  // furthest: the index of furthest vine which is already reached
  int furthest = 0;

  for (int i = 0; i < N; i++) {
    // return true if you reach your one true love
    if (d[i] + reach[i] >= D) return true;

    // if vines which are further than {furthest}-th view can be reached,
    // update their {reach} and move {furthest} forward.
    // It is assured that the updated {reach} is the best if we process vines
    // from near to far.
    while (furthest+1 < N && d[furthest+1] <= d[i] + reach[i]) {
      furthest++;
      reach[furthest] = min(l[furthest], d[furthest] - d[i]);
    }
  }
  return false;
}

int main()
{
  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    // read input data
    int N; cin >> N;
    vector<int> d(N), l(N);
    for (int i = 0; i < N; i++) cin >> d[i] >> l[i];
    int D; cin >> D;

    // solve it and print answer
    bool ans = solve(N, d, l, D);
    cout << "Case #" << (t+1) << ": " << (ans ? "YES" : "NO") << endl;
  }
}
