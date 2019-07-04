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

vii v;
int num_of_cases;

//int solve(int n, int i) {
//    if (n == num_of_cases) {
//        return 0;
//    }
//
//    if (i == -1) {
//        return max(1+solve(n+1,n), solve(n+1,i));
//    }
//
//    if (v[n].first >= v[i].first && v[n].second >= v[i].second) {
//        int val1 = 1+solve(n+1,n);
//        int val2 = solve(n+1,i);
//        if (val1 > val2) {
//            return val1;
//        } else {
//            return val2;
//        }
////        return max(1+solve(n+1,n), solve(n+1,i));
//    } else {
//        return solve(n+1,i);
//    }
//}

int solve(int n, int i) {
    if (n == -1) {
        return 0;
    }

    if (v[n].first >= v[i].first && v[n].second >= v[i].second) {
        return max(1 + solve(n - 1, n), solve(n - 1, i));
    } else {
        return solve(n - 1, i);
    }
}

int main() {
    cin >> num_of_cases;

    while (num_of_cases != 0) {
        int sum;
        for (int i = 0; i < num_of_cases; ++i) {
            int l, m;
            cin >> l >> m;
            v.push_back(make_pair(l, m));
        }

        sort(v.begin(),v.end());

        vector<int> LIS(num_of_cases,1);
        for (int i=1; i<num_of_cases; i++)
            for (int j=0; j<i; j++)
                if ((v[i].first >= v[j].first && v[i].second >= v[j].second)) {
                    LIS[i] = max(LIS[i], LIS[j] + 1);
                }


        v = vii();
        cout << LIS[num_of_cases-1] << endl;
        cin >> num_of_cases;

    }
    cout << "*" << endl;
    return 0;
}