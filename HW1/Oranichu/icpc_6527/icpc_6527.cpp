#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <numeric>

using namespace std;
typedef vector<pair<int, int>> vii;
typedef long long ll;

ll bin_length(ll n, vector<ll> &ones_places){
    ll length = 0;
    while (n > 0) {

        if (n%2 == 1) {
            ones_places.push_back(length);
        }

        length++;
        n/=2;
    }
    return length;
}

ll ll_pow (ll x, ll y){
    ll sum = 1;
    for (ll i = 0; i < y; ++i) {
        sum *= x;
    }
    return sum;
}

ll count_ones(ll n) {
    ll sum = 0;
    vector<ll> ones_places;
    for (ll i = bin_length(n, ones_places) - 1; i > 0 ; i--) {
        if ((n>>i)%2 == 1) { // bit in location i is set.
            sum+=(i * ll_pow(2,i-1));
        } // add to sum all the one's from the closest pow of 2.
    }

    for (ll i = 0 ; i<ones_places.size() ; i++) {
        sum+= i* ll_pow(2, ones_places[ones_places.size() - i -1]);
    } // add the number of one's after the closest pow of 2.

    return sum;

}

int main() {

    ll a,b;
    while (cin >> a >> b){
        cout << count_ones(b+1) - count_ones(a) << endl;
    }

    return 0;
}