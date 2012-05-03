#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
#define ALL(a)  (a).begin(),(a).end()
#define REP(i,n) for(int i=0;i<(n);++i)
const double EPS = 1e-10;
const double PI  = acos(-1.0);
#define dump(x) cerr << "  (L" << __LINE__ << ") " << #x << " = " << (x) << endl;
#define dumpv(x) cerr << "  (L" << __LINE__ << ") " << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& d) {return s << "(" << d.first << "," << d.second << ")";}


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

