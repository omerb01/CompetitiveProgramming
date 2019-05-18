#include <iostream>
#include <cmath>

using namespace std;
typedef long long ll;

ll calc_col_lower_bound(ll num, ll n) {
    ll upper_bound = pow(2, n);
    return (num - (num % upper_bound)) / 2;
}

ll calc_col_remains(ll num, ll n) {
    ll upper_bound = pow(2, n);
    ll lower_bound = pow(2, n - 1);
    ll check = num % upper_bound;
    if (check > lower_bound) return check - lower_bound;
    return 0;
}

ll solve(ll num) {
    ll n = log2(num) + 1;
    ll sum = 0;
    while (n) {
        sum += calc_col_lower_bound(num, n) + calc_col_remains(num, n);
        n--;
    }
    return sum;
}

int main() {
    ll a, b;
    while (cin >> a >> b) {
        cout << solve(b + 1) - solve(a) << endl;
    }
    return 0;
}