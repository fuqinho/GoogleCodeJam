#include <iostream>
using namespace std;

string solve(string s) {
  bool noloop = next_permutation(s.begin(), s.end());
  if (!noloop) {
    s = '0' + s;
    for (int i = 0; i < s.size(); i++) {
      if (s[i] != '0') {
        swap(s[0], s[i]);
        break;
      }
    }
  }
  return s;
}

int main() {
  int T; cin >> T;
  for (int t = 1; t <= T; t++) {
    string s; cin >> s;
    string ans = solve(s);
    cout << "Case #" << t << ": " << ans << endl;
  }
}

