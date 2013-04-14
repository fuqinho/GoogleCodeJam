#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

bool is_parindrome(ll n) {
    vector<int> digits;
    while (n) {
        digits.push_back(n % 10);
        n /= 10;
    }
    vector<int> rev_digits(digits.rbegin(), digits.rend());
    return digits == rev_digits;
}

vector<ll> listup(ll max_number) {
    vector<ll> res;
    for (ll i = 1; i * i <= max_number; i++) {
        if (is_parindrome(i) && is_parindrome(i*i)) {
            res.push_back(i*i);
        }
    }
    return res;
}

ll solve(ll A, ll B, const vector<ll>& ok_numbers) {
    return upper_bound(ok_numbers.begin(), ok_numbers.end(), B)
        - lower_bound(ok_numbers.begin(), ok_numbers.end(), A);
}

int main() {
    int T; cin >> T;
    vector<ll> ok_numbers = listup((ll)1e14);
    for (int t = 1; t <= T; t++) {
        ll A, B; cin >> A >> B;
        ll ans = solve(A, B, ok_numbers);
        cout << "Case #" << t << ": " << ans << endl;
    }
}
