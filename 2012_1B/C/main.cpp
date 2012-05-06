// example to use unordered_map: $ clang++ -std=c++11 -stdlib=libc++ main.cpp
#include <iostream>
#include <vector>
#if __cplusplus >= 201103L
#include <unordered_map>
#else
#include <map>
#endif
using namespace std;

typedef long long LL;

void solve(int N, vector<LL>& S) {
  const int SIZE = 20;

  while (true) {
#if __cplusplus >= 201103L
    unordered_map<LL, int> m;
#else
    map<LL, int> m;
#endif
    random_shuffle(S.begin(), S.end());
    vector<LL> S1(S.begin(), S.begin() + SIZE);
    for (int i = 1; i < (1 << SIZE) - 1; i++) {
      LL sum = 0;
      for (int j = 0; j < SIZE; j++) if (i & (1 << j)) sum += S1[j];
      if (m.find(sum) != m.end()) {
        int num1 = m[sum];
        int num2 = i;
        for (int k=0; k<SIZE; k++) if (num1 & (1 << k)) cout << S1[k] << " ";
        cout << endl;
        for (int k=0; k<SIZE; k++) if (num2 & (1 << k)) cout << S1[k] << " ";
        cout << endl;
        return;
      } else {
        m[sum] = i;
      }
    }
    vector<LL> S2(S.begin() + SIZE, S.begin() + SIZE * 2);
    for (int i = 1; i < (1 << SIZE) - 1; i++) {
      LL sum = 0;
      for (int j = 0; j < SIZE; j++) if (i & (1 << j)) sum += S2[j];
      if (m.find(sum) != m.end()) {
        int num1 = m[sum];
        int num2 = i;
        for (int k=0; k<SIZE; k++) if (num1 & (1 << k)) cout << S1[k] << " ";
        cout << endl;
        for (int k=0; k<SIZE; k++) if (num2 & (1 << k)) cout << S2[k] << " ";
        cout << endl;
        return;
      }
    }
  }
  cout << "Impossible" << endl;
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    int N; cin >> N;
    vector<LL> S(N);
    for (int i = 0; i < N; i++) cin >> S[i];

    cout << "Case #" << t+1 << ":" << endl;
    solve(N, S);
  }
}

