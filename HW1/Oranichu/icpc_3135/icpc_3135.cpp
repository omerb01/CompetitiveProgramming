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
typedef long long ll;
typedef unsigned long long ull;
typedef vector<pair<int, string>> v_ex2;
typedef pair<int, int> pii;


int main() {

    string reg;
    int q_num, period, k;

//    <<a,b>, c>
//    a is the stacked period sum, b is q_num, and c is original peroid
    map<pair<int, int>, int> m;

    cin >> reg;

    while (reg != "#") {

        cin >> q_num >> period;
        m.insert(make_pair(make_pair(period, q_num), period));

        cin >> reg;
    }

    cin >> k;
    for (int i = 0; i < k; ++i) {
        pair<pair<int, int>, int> p = *(m.begin());
        m.erase(m.begin());
        cout << p.first.second << endl;

        m.insert(make_pair(make_pair(p.first.first + p.second, p.first.second),
                           p.second));


    }

    return 0;
}