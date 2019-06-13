#include <iostream>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

#define MAX_N 1120
#define MAX_K 14

vector<bool> sieve(int n) {
    vector<bool> ps(n + 1, true);
    ps[0] = false;
    ps[1] = false;
    int sqrtn = sqrt(n);
    for (int i = 0; i <= sqrtn; ++i) {
        if (ps[i]) {
            for (int j = i * i; j <= n; j += i) {
                ps[j] = false;
            }
        }
    }
    return ps;
}

vector<bool> is_prime = sieve(MAX_N + 1);
vector<vector<int>> memo(MAX_N + 1, vector<int>(MAX_K + 1, 0));

void fill_memo() {
    for (int p = 0; p <= MAX_N; ++p) {
        if (is_prime[p]) {
            for (int n = MAX_N; n >= p; --n) {
                for (int k = 1; k <= MAX_K; ++k) {
                    int omer = memo[n - p][k - 1];
                    memo[n][k] += omer;
                }
            }
        }
    }
}

int main() {
    memo[0][0] = 1;
    fill_memo();

    int n, k;
    while (cin >> n >> k) {
        if (n == 0 && k == 0) break;
        cout << memo[n][k] << endl;
    }
    return 0;
}