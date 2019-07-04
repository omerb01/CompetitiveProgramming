//

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
#include <fstream>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;

int main() {
    ll sums[62];

    sums[0] = 1;
    sums[1] = 1;
    sums[2] = 1;

    for (int i = 3; i < 61; ++i) {
        sums[i] = sums[i-1] + sums[i-2] + sums[i-3];
    }

    int n;
    int count = 1;
    cin >> n;
    while (n!=0) {
        cout << "Case " << count++ << ":" << " " << sums[n-1] << endl;
        cin >> n;
    }
    return 0;
}