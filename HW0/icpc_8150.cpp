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
typedef vector<int> vi;
typedef pair<int, int> pii;

int main() {
    int w;

    while (scanf("%d", &w) != EOF) {
        int n;
        int sum = 0;
        cin >> n;
        while (n--) {
            int n1, n2;
            cin >> n1 >> n2;
            sum += n1 * n2;
        }
        cout << sum / w << endl;
    }

    return 0;
}