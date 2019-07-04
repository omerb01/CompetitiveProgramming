
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
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;


bool isSqrt(double n) { // O(n)
    if (sqrt(n) - (double) floor((sqrt(n))) == 0) {
        return true;
    }
    return false;
}

int main() {
    int test_cases;
    cin >> test_cases;
    string temp;
    getline(cin, temp);
    for (int i = 0; i < test_cases; ++i) {
        string s;
        getline(cin, s);
        if (!isSqrt(s.length())) {
            cout << "INVALID" << endl;
        } else {

            int n = sqrt(s.length());
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    cout << s[j + n * k];
                }
            }
            cout << endl;

        }
    }
    return 0;
}