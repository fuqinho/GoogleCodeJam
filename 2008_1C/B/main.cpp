#include <iostream>
#include <vector>
using namespace std;

long long solve(string s) {
  const int LCM = 2 * 3 * 5 * 7;
  const int MAX_S = 40;

  vector<int> v(s.size());
  for (int i = 0; i < s.size(); i++) v[i] = s[i] - '0';
  
  // dp[i][j]: i番目の文字まで使って、LCMで割った余りが
  // jになっているパターン数
  long long dp[MAX_S+1][LCM];
  memset(dp, 0, sizeof(dp));
  dp[0][0] = 1;

  for (int i = 1; i <= s.size(); i++) {
    int mul = 1;
    int curNum = 0;
    for (int j = i-1; j >= 0; j--) {
      curNum = (curNum + v[j] * mul) % LCM;
      for (int k = 0; k < LCM; k++) {
        dp[i][(k + curNum) % LCM] +=  dp[j][k];
        if (j != 0) dp[i][(k - curNum + LCM) % LCM] +=  dp[j][k];
      } 
      mul = (mul * 10) % LCM;
    }
  }

  long long res = 0;
  for (int i = 0; i < LCM; i++) {
    if (i % 2 == 0 || i % 3 == 0 || i % 5 == 0 || i % 7 == 0) {
      res += dp[s.size()][i];
    }
  }

  return res;
}

int main() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) {
    string s; cin >> s;
    long long answer = solve(s);
    cout << "Case #" << i+1 << ": " << answer << endl;
  }
}

