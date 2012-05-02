#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

vector<vector<int> > mul(vector<vector<int> >& a, vector<vector<int> >& b) {
  int row_num = a.size(), col_num = b[0].size();
  vector<vector<int> > res(row_num, vector<int>(col_num, 0));
  for (int i = 0; i < row_num; i++) {
    for (int j = 0; j < col_num; j++) {
      for (int k = 0; k < a[0].size(); k++) {
        res[i][j] += a[i][k] * b[k][j];
        res[i][j] %= 1000;
      }
    }
  }
  return res;
}

int solve(int n) {
  vector<vector<int> > a(2, vector<int>(2));
  a[0][0] = 3; a[0][1] = 5;
  a[1][0] = 1; a[1][1] = 3;

  vector<vector<int> > cur(2, vector<int>(2));
  cur[0][0] = 1; cur[0][1] = 0;
  cur[1][0] = 0; cur[1][1] = 1;
  
  while (n > 0) {
    if (n & 1) cur = mul(cur, a);
    a = mul(a, a);
    n >>= 1;
  }
  return (cur[0][0] * 2 - 1) % 1000;
}

int main() {
  int T; cin >> T;
  for (int t=0; t<T; t++) {
    int n; cin >> n;
    int answer = solve(n);
    printf("Case #%d: %03d\n", t+1, answer);
  }
}
