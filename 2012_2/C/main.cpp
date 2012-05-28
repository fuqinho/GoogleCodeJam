#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> x;
vector<int> h; // height for each peak

bool fillHeights(int slope, int idx, int B) {
  if (h[idx] != -1) return idx == B;

  bool res = fillHeights(slope, x[idx], B);
  h[idx] = h[x[idx]] - (x[idx] - idx) * slope;
  return res;
}

void solve() {
  // make the height of the last peak high enough
  h = vector<int>(N, -1);
  h[N-1] = 10000000;

  for (int A = 0; A < N-1; A++) {
    // if the hight of current peak is not determined...
    if (h[A] == -1) {
      // calc slope for A-th peak (and following apparently highest peaks)
      int slope = 0;
      int B = N-1;
      if (A > 0) {
        int prevA = A-1;
        B = x[prevA];
        // the slope should be heavier than the slope from previous peak 
        // to its apparently highest peak.
        slope = (h[B] - h[prevA]) / (B - prevA) + 1;
      }
      
      // fill hight of peaks which can be on this slope
      bool res = fillHeights(slope, A, B);
      if (res == false) {
        cout << "Impossible";
        return;
      }
    }
  }

  // prettify (not necessary)
  int lowest = *min_element(h.begin(), h.end());
  for (int i = 0; i < N; i++) h[i] -= lowest;

  // print answer
  for (int i = 0; i < N; i++) cout << h[i] << " ";
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    // read input data
    cin >> N;
    x = vector<int>(N-1);
    for (int i = 0; i < N-1; i++) {
      cin >> x[i];
      x[i]--; // change to 0-base index
    }
    
    // solve and print answer
    cout << "Case #" << t+1 << ": ";
    solve();
    cout << endl;
  }
}
