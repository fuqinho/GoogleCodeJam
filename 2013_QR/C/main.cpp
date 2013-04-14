#include <iostream>
#include <vector>
using namespace std;

const int MAX_DIGITS_ROOT = 53;
const int MAX_DIGITS = MAX_DIGITS_ROOT * 2 - 1;
int d[MAX_DIGITS_ROOT];
int sum[MAX_DIGITS];

bool check(int len) {
    memset(sum, 0, sizeof(sum));
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            sum[i+j] += d[i] * d[j];
            if (sum[i+j] >= 10) return false;
        }
    }
    return true;
}

string digits2str(int len) {
    memset(sum, 0, sizeof(sum));
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++)
            sum[i+j] += d[i] * d[j];
    string res(MAX_DIGITS, '0');
    for (int i = 0; i < MAX_DIGITS; i++)
        res[MAX_DIGITS-1-i] = '0' + sum[i];
    return res;
}

void backtrack(int p, int len, vector<string>& out) {
    if (p == (len+1)/2) {
        out.push_back(digits2str(len));
        return;
    }
    for (int i = (p == 0 ? 1 : 0); i <= 3; i++) {
        d[p] = d[len-1-p] = i;
        if (check(len)) backtrack(p+1, len, out);
        d[p] = d[len-1-p] = 0;
    }
}

vector<string> listup() {
    vector<string> res;
    for (int len = 1; len <= MAX_DIGITS_ROOT; len++) {
        memset(d, 0, sizeof(d));
        backtrack(0, len, res);
    }
    return res;
}

int solve(string A, string B, const vector<string>& ok_numbers) {
    return upper_bound(ok_numbers.begin(), ok_numbers.end(), B)
        - lower_bound(ok_numbers.begin(), ok_numbers.end(), A);
}

string normalize(string n) {
    return string(MAX_DIGITS - n.size(), '0') + n;
}

int main() {
    int T; cin >> T;
    vector<string> ok_numbers = listup();
    for (int t = 1; t <= T; t++) {
        string A, B; cin >> A >> B;
        A = normalize(A);
        B = normalize(B);
        int ans = solve(A, B, ok_numbers);
        cout << "Case #" << t << ": " << ans << endl;
    }
}
