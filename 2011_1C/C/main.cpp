#include <iostream>
#include <vector>
using namespace std;

typedef long long LL;
#define REP(i,n) for(int i=0;i<(n);++i)

const LL MAX_H = 1e+16;

LL get_gcd(LL a, LL b) {
  if (a < b) swap(a, b);
  if (b == 0) return a;
  return get_gcd(b, a % b);
}

// return lcm if it is not greater than MAX_H, otherwise return MAX_H+1.
LL get_lcm(LL a, LL b) {
  LL gcd = get_gcd(a, b);
  a /= gcd;
  if ((MAX_H + 1) / b >= a) {
    return a * b;
  } else {
    return MAX_H + 1;
  }
}

vector<LL> get_divisors(LL n) {
  vector<LL> res;
  for (LL i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      res.push_back(i);
      if (i != n / i) res.push_back(n / i);
    }
  }
  sort(res.begin(), res.end());
  return res;
}

LL solve(int N, LL L, LL H, vector<LL>& F) {
  sort(F.begin(), F.end());
  // insert 1 as minimum frequency for convenience
  if (F[0] != 1) {
    F.push_back(1);
    N++;
    sort(F.begin(), F.end());
  }

  // lcm[k]: lcm for F[0] ~ F[k]
  vector<LL> lcm(N);
  lcm[0] = F[0];
  for (int i = 1; i < N; i++) {
    lcm[i] = get_lcm(lcm[i-1], F[i]);
  }

  // gcd[k]: gcd for F[k] ~ F[N-1]
  vector<LL> gcd(N);
  gcd[N-1] = F[N-1];
  for (int i = N - 2; i >= 0; i--) {
    gcd[i] = get_gcd(gcd[i+1], F[i]);
  }

  // F can be found in the interval from lcm of F[0],F[1],..,F[k] to gcd of F[k+1],..,F[N-1]
  // if the gcd is divisible by the lcm.
  for (int i = 0; i < N-1; i++) {
    LL C = lcm[i];
    LL D = gcd[i+1];
    if (D < L || C > H) continue; // no intersection
    if (C <= D && D % C == 0) {
      vector<LL> v = get_divisors(D);
      REP(j, v.size()) {
        if (v[j] >= max(L, C) && v[j] <= min(D, H) && v[j] % C == 0) {
          return v[j];
        }
      }
    }
  }

  // find F from multiples of lcm of all frequencies.
  LL mult = lcm[N-1] * ((L - 1) / lcm[N-1] + 1);
  if (mult <= H) return mult;

  return -1; // not found
}

int main() {
  int T; cin >> T;
  REP(t, T) {
    int N; LL L, H; cin >> N >> L >> H;
    vector<LL> F(N);
    REP(i, N) cin >> F[i];

    LL ans = solve(N, L, H, F);
    if (ans == -1) cout << "Case #" << t+1 << ": NO" << endl;
    else cout << "Case #" << t+1 << ": " << ans << endl;
  }
}
