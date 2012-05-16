#include <iostream>
#include <vector>
using namespace std;

vector<double> solve(int N, const vector<string>& result) {
  // opponents[i]: the number of opponents for team i
  vector<int> opponents(N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (result[i][j] != '.') opponents[i]++;
    }
  }

  // wp[i]: wp of i
  vector<double> wp(N);
  for (int i = 0; i < N; i++) {
    int win = 0, lose = 0;
    for (int j = 0; j < N; j++) {
      if (result[i][j] == '1') win ++;
      if (result[i][j] == '0') lose ++;
    }
    wp[i] = (double)win / (win + lose);
  }

  // wp2[i][j]: wp of i after throwing out game with j
  vector<vector<double> > wp2(N, vector<double>(N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int win = 0, lose = 0;
      for (int k = 0; k < N; k++) {
        if (k != j) {
          if (result[i][k] == '1') win ++;
          if (result[i][k] == '0') lose ++;
        }
      }
      wp2[i][j] = (double)win / (win + lose);
    }
  }

  vector<double> owp(N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (result[i][j] != '.') {
        owp[i] += wp2[j][i];
      }
    }
    owp[i] /= opponents[i];
  }

  vector<double> oowp(N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (result[i][j] != '.') {
        oowp[i] += owp[j];
      }
    }
    oowp[i] /= opponents[i];
  }
  
  vector<double> res(N);
  for (int i = 0; i < N; i++) {
    res[i] = 0.25 * wp[i] + 0.50 * owp[i] + 0.25 * oowp[i];
  }

  return res;
}


int main() {
  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    int N; cin >> N;
    vector<string> result(N);
    for (int i = 0; i < N; i++) cin >> result[i];

    cout << "Case #" << t+1 << ":" << endl;
    vector<double> ans = solve(N, result);
    for (int i = 0; i < ans.size(); i++) {
      cout << ans[i] << endl;
    }
  }
}
