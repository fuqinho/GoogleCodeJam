#include <iostream>
using namespace std;

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a%b);
}

bool solve(long long N, int PD, int PG) {
  if ((PG == 0 && PD != 0) || (PG == 100 && PD != 100)) return false;
  return N >= (100 / gcd(100, PD)); 
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    long long N; int PD, PG; cin >> N >> PD >> PG;

    bool ans = solve(N, PD, PG);
    cout << "Case #" << t+1 << ": " << (ans ? "Possible" : "Broken") << endl;
  }
}
