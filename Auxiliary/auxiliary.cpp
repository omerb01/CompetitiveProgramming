// Headers

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
    return 0;
}

// Reads n input test cases

cin >> n;
while (n--) {}

// Reads n and k ints until EOF

while (cin >> n >> k) {}

// Generate all subsets of {1,...,n}

for (i = 0; i < (1 << n); i++) {
    // i represents a subset
    for (int j = 0; j < n; j++) if (i & (1 << j)) {
        ...
        // j represents an element in i
    }
}

// Generate all permutations

int n = 8, p[8] = {0, 1, 2, 3, 4, 5, 6, 7};
do {
    ...
} while (next_permutation(p, p + n));