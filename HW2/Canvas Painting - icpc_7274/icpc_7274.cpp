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
typedef vector<int> vi;
typedef long long ll;


int main() {
    ll T;
    while (cin >> T) {

        for (ll i = 0; i < T; ++i) {
            ll N;
            cin >> N;
            multimap<ll, bool> m;

            for (ll j = 0; j < N; ++j) {
                ll s;
                cin >> s;
                m.insert(make_pair(s, true));
            }

            ll sum = 0;
            ll temp_sum = 0;

            while (m.size() > 1) {
                temp_sum = (*m.begin()).first + (*(++(m.begin()))).first;
                sum += temp_sum;

                m.erase(m.begin());
                m.erase(m.begin());
                m.insert(make_pair(temp_sum, true));

            }

            cout << sum << endl;


        }
    }
    return 0;
}