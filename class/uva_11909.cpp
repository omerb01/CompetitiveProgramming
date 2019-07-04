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

#define PI 3.14159265

int main() {
    ll l,w,h,t;
    while(cin >> l >> w >> h >> t) {
        double res, t1,t2;

        t1 = atan(((double)h)/((double)l));
        if (t1 < 0) {
            t1 = -1*t1;
        }
        t1 = t1 * 180/PI;

        if (t>t1) {

            t2 = tan((double)(PI*(90-t))/180);
            res = ((double)(h*h*t2*w))/((double)2);
        } else {

            t2 = tan((double)(PI*(t))/180);
            res = l*w*h - ((double)(l*l*t2*w))/((double)2);
        }
        printf("%.3f mL\n", res);
    }
    return 0;
}