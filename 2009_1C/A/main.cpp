#include <iostream>
#include <vector>
#include <map>
using namespace std;

long long solve(string s) {
  map<char, int> m;
  vector<int> v(s.size());
  for (int i = 0; i < s.size(); i++) {
    if (m.find(s[i]) == m.end()) {
      if (m.size() == 0) {
        m[s[i]] = 1;
      } else if (m.size() == 1) {
        m[s[i]] = 0;
      } else {
        m[s[i]] = m.size();
      }
    }
    v[i] = m[s[i]];
  }

  long long res = 0;
  int base = max(2, (int)m.size());
  for (int i = 0; i < v.size(); i++) {
    res *= base;
    res += v[i];
  }
    
  return res;
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    string s; cin >> s;
    long long ans = solve(s);
    cout << "Case #" << t+1 << ": " << ans << endl;
  }
}
