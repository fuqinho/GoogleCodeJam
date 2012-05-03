#include <iostream>
#include <sstream>
#include <vector>
#include <set>
using namespace std;

int next(int x, int b) {
  int res = 0;
  while (x) {
    int digit = x % b;
    res += digit * digit;
    x /= b;
  }
  return res;
}

const int CACHE_SIZE = 10000000;
int memo[CACHE_SIZE][11];

bool isHappy(int n, int b) {
  if (n < CACHE_SIZE && memo[n][b] != -1) return memo[n][b];

  set<int> inloop;
  bool result;
  while (true) {
    if (n < CACHE_SIZE && memo[n][b] != -1) {
      result = memo[n][b];
      break;
    }
    if (n == 1) {
      result = true;
      break;
    }
    if (inloop.find(n) != inloop.end()) {
      result = false;
      break;
    }
    inloop.insert(n);
    n = next(n, b);
  }

  for (set<int>::iterator i = inloop.begin(); i != inloop.end(); i++) {
    if (*i < CACHE_SIZE) memo[*i][b] = result;
  }
  return memo[n][b] = result;
}
  
int solve(vector<int> B) {
  for (int i = 2; ; i++) {
    bool isOK = true;
    for (int j = 0; j < B.size(); j++) {
      if (!isHappy(i, B[j])) {
        isOK = false;
        break;
      }
    }
    if (isOK) return i;
  }
  return -1;
}

int main() {
  memset(memo, -1, sizeof(memo));
  string s; getline(cin, s);
  istringstream iss(s); 
  int T; iss >> T;
  for (int i = 0; i < T; i++) {
    getline(cin, s);
    istringstream iss(s);
    vector<int> B;
    int n;
    while (iss >> n) B.push_back(n);
    
    int answer = solve(B);
    cout << "Case #" << i+1 << ": " << answer << endl;
  }
}

