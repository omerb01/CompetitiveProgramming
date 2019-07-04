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
    int n;

    cin >> n;
    for (int k = 1; k <= n; k++) {
        int result = 0;
        string s, t;
        cin >> s >> t;

        int n1_s = 0;
        for (int i = 0; i < s.length(); i++) if (s[i] == '1') n1_s++;

        int n1_t = 0;
        for (int i = 0; i < t.length(); i++) if (t[i] == '1') n1_t++;

        for (int i = 0; i < s.length(); i++) {
            if (n1_t - n1_s > 0 && s[i] == '?' && t[i] == '1') {
                s[i] = '1';
                n1_s++;
                result++;
            }
        }

        for (int i = 0; i < s.length(); i++) {
            if (n1_t - n1_s > 0 && s[i] == '?') {
                s[i] = '1';
                n1_s++;
                result++;
            } else if (s[i] == '?') {
                s[i] = '0';
                result++;
            }
        }

        if (n1_s > n1_t) result = -1;
        else {
            string xor_input = "";
            for (int i = 0; i < s.length(); i++) {
                if (s[i] == '0' && t[i] == '0') xor_input += '0';
                else if (s[i] == '1' && t[i] == '1') xor_input += '0';
                else if (s[i] == '0' && t[i] == '1') xor_input += '1';
                else if (s[i] == '1' && t[i] == '0') xor_input += '1';
            }
            int counter = 0;
            for (int i = 0; i < s.length(); i++) if (xor_input[i] == '1') counter++;

            result += ((counter + (n1_t - n1_s)) / 2);
        }

        cout << "Case " << k << ": " << result << endl;
    }

    return 0;
}