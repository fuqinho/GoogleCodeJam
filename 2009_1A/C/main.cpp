#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long LL;

LL gcd(LL a, LL b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

LL combination(int a, int b) {
  if (a - b < b) b = a - b;

  LL n = 1, d = 1;
  for (int i = 0; i < b; i++) {
    n *= (a-i);
    d *= (b-i);
    LL g = gcd(n, d);
    n /= g;
    d /= g;
  }
  return n / d;
}

double solve(int N, int C) {
  LL denom = combination(N, C);

  // dp[i]: まだ獲得してないカードがi枚ある状態からの必要な手数の期待値
  vector<double> dp(N+1, 0);
  dp[0] = 0.0;
  for (int i = 1; i <= N; i++) {
    // 取ってないカードがi個、とったカードがN-i個ある状態から、
    // 新しいカードがj個(0-i個)取れるパターンそれぞれの確率を計算する
    double e = 0.0;
    double p_noprogress = 0.0;
    for (int j = 0; j <= i; j++) {
      if (C-j >= 0 && N-i >= C-j) {
        if (j == 0) {
          p_noprogress += ((double)combination(i, j) * combination(N-i, C-j) / denom);
        } else {
          e += dp[i-j] * ((double)combination(i, j) * combination(N-i, C-j) / denom);
        }
      }
    }
    dp[i] = (e + 1) / (1 - p_noprogress);
  }

  return dp[N];
}

int main() {
  int T; cin >> T;
  for (int i = 0; i < T; i++) {
    int N, C; cin >> N >> C;
    double answer = solve(N, C);
    printf("Case #%d: %.8lf\n", i+1, answer);
  }
}

