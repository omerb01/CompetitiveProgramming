#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
}

int main() {
    ll t;
    cin >> t;

    while (t--) {
        ll c;
        cin >> c;

        vector<ll> arr(c, 0);
        vector<ll> xs(c, 0);
        for (ll i = 0; i < c; ++i) {
            ll sum = 0;
            ll x;
            for (ll j = 1; j <= 9; ++j) {
                cin >> x;
                sum += x;
            }
            cin >> x;
            arr[i] = sum - x;
            xs[i] = x;
        }

        ll max = *max_element(xs.begin(), xs.end());

        ll g = gcd(arr[0], 0);
        for (ll i = 0; i < arr.size(); ++i) {
            g = gcd(arr[i], g);
        }

        if (g > 1 && g > max) cout << g << endl;
        else cout << "impossible" << endl;
    }
    return 0;
}