#include <iostream>
#include <vector>
using namespace std;

class DisjointSet {
public:
  DisjointSet(int n) {
    rank = vector<int>(n, 0);
    par = vector<int>(n);
    for (int i = 0; i < n; i++) par[i] = i;
  }
  int find(int x) {
    if (x == par[x]) return x;
    else return par[x] = find(par[x]);
  }
  void unite(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rank[rx] < rank[ry]) par[rx] = ry;
    else {
      par[ry] = rx;
      if (rank[rx] == rank[ry]) rank[rx]++;
    }
  }
  bool same(int x, int y) {
    return find(x) == find(y);
  }
  int size() {
    int res = 0;
    for (int i = 0; i < par.size(); i++) {
      if (par[i] == i) res++;
    }
    return res;
  }
private:
  vector<int> par;
  vector<int> rank;
};

vector<int> get_primes(int minNum, int maxNum) {
  vector<int> res;
  vector<bool> isPrime(maxNum + 1, true);
  for (int i = 2; i <= maxNum; i++) {
    if (isPrime[i]) {
      if (i >= minNum) res.push_back(i);
      for (int j = i * 2; j <= maxNum; j += i) {
        isPrime[j] = false;
      }
    }
  }
  return res;
}

long long solve(long long A, long long B, long long P) {
  vector<int> primes = get_primes(P, B - A);

  DisjointSet s(B - A + 1);
  for (int i = 0; i < primes.size(); i++) {
    int factor = primes[i];
    int first_multiple = A % factor == 0 ? 0 : factor - A % factor;
    for (int j = first_multiple + factor; j < B - A + 1; j += factor) {
      s.unite(first_multiple, j);
    }
  }

  return s.size();
}

int main() {
  int C; cin >> C;
  for (int i = 0; i < C; i++) {
    long long A, B, P;
    cin >> A >> B >> P;

    long long answer = solve(A, B, P);
    cout << "Case #" << i+1 << ": " << answer << endl;
  }
}

