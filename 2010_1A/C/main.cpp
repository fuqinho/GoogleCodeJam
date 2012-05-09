#include <iostream>
#include <cmath>
using namespace std;

const double GOLDEN = (1.0 + sqrt(5.0)) / 2.0;

// return the number of winning As which are larger than B
int winningPosNum(int a_min, int a_max, int b) {
  a_min = max(a_min, b);
  if (a_max < a_min) return 0;

  int minWiniingA = (int)ceil(b * GOLDEN);
  return max(0, a_max - max(minWiniingA, a_min) + 1);
}

long long solve(int A1, int A2, int B1, int B2) {
  long long res = 0;
  for (int B = B1; B <= B2; B++) {
    res += winningPosNum(A1, A2, B);
  }
  for (int A = A1; A <= A2; A++) {
    res += winningPosNum(B1, B2, A);
  }
  return res;
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    int A1, A2, B1, B2;
    cin >> A1 >> A2 >> B1 >> B2;

    long long ans = solve(A1, A2, B1, B2);
    cout << "Case #" << t+1 << ": " << ans << endl;
  }
}
