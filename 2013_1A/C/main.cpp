#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

#define REP(i,n) for(int i=0; i<(int)(n); i++)
typedef long long ll;

int R, N, M, K;
vector<string> patterns;
double P[20000];
unordered_map<ll, double> CP[20000];

void listup_patterns(int pos, string& cur, vector<string>& out) {
    if (pos == cur.size()) {
        out.push_back(cur);
        return;
    }
    for (int i = 2; i <= M; i++) {
        if (pos > 0 && cur[pos-1]-'0' > i) continue;
        cur[pos] = char('0' + i);
        listup_patterns(pos+1, cur, out);
    }
}

ll factorial(int n) {
    ll res = 1;
    for (int i=1; i<=n; i++) res *= i;
    return res;
}

ll power(int n, int p) {
    ll res = 1;
    for (int i=0; i<p; i++) res *= n;
    return res;
}

double possibility(string pattern) {
    int n = pattern.size();
    ll numerator = factorial(n);
    for (char c = '2'; c <= '0'+M; c++)
        numerator /= factorial(count(pattern.begin(), pattern.end(), c));
    ll denominator = power(M-1, n);
    return (double)numerator / denominator;
}

void precompute() {
    // list up patterns
    patterns.clear();
    string cur(N, '0');
    listup_patterns(0, cur, patterns);

    // calculate possibility for each patterns
    for (int i=0; i<patterns.size(); i++) {
        P[i] = possibility(patterns[i]);
    }
    // calclulate conditional possibility
    for (int i=0; i<patterns.size(); i++) {
        CP[i].clear();
        for (int s=0; s<(1<<N); s++) {
            ll product = 1;
            for (int j=0; j<N; j++) if (s & (1<<j)) {
                product *= (patterns[i][j]-'0');
            }
            CP[i][product] += 1.0 / (1<<N);
        }
    }
}

string solve(vector<ll>& p) {
    int max_id = 0;
    double max_p = 0.0;
    for (int i=0; i<patterns.size(); i++) {
        double total_p = P[i];
        for (int j=0; j<p.size(); j++) {
            if (total_p < max_p) break;
            total_p *= CP[i][p[j]];
        }
        if (total_p >= max_p) {
            max_p = total_p;
            max_id = i;
        }
    }
    return patterns[max_id];
}

int main(int argc, char* argv[]) {
    int T; cin >> T;
    REP(t, T) {
        cin >> R >> N >> M >> K;
        cout << "Case #" << (t+1) << ":" << endl;
        precompute();
        REP(i, R) {
            vector<ll> p(K);
            REP(j, K) cin >> p[j];
            string ans = solve(p);
            cout << ans << endl;
        }
    }
}
