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

int main() {
    int test_cases;
    cin >> test_cases;
    for (int i = 0; i < test_cases; ++i) {
        int n;
        vii v;
        cin >> n;
        for (int j = 0; j < n; ++j) {
            int x, y;
            cin >> x >> y;
            v.push_back(make_pair(x, y));
        }
        sort(v.begin(), v.end());
        int midX, midY;
        midX = v[0].first + v[n - 1].first; // no need to dived by 2.
        midY = v[0].second + v[n - 1].second; // no need to dived by 2.

        bool symmetry_exists = true;
        for (int k = 1; k < n - 1; ++k) {
            if ((v[k].first + v[n - k - 1].first != midX)
                || (v[k].second + v[n - k - 1].second != midY)) {
                symmetry_exists = false;
                break;
            }

        }

        if (symmetry_exists) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }
    return 0;
}