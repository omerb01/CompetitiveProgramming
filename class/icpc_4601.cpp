
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

#define EPS 0.0000000001

ld calcDistance (ld x_a, ld y_a, ld x_b, ld y_b)    {
    ld dis = (((x_a-x_b)*(x_a-x_b))+((y_a-y_b)*(y_a-y_b)));
    return sqrt(dis);
}

ld calcTriangle(ld x_d, ld y_d, ld x_e, ld y_e, ld x_f, ld y_f)  {
    ld a = ((x_d*y_e)-(x_e*y_d));
    ld b = ((x_e*y_f)-(x_f*y_e));
    ld c = ((x_f*y_d)-(x_d*y_f));
    return abs((a+b+c)*0.5);
}

int main() {
    ld x_a, y_a, x_b, y_b, x_c, y_c, x_d, y_d, x_e, y_e, x_f, y_f;
    ld x_start, y_start, x_end, y_end;
    cin >> x_a >> y_a >> x_b >> y_b >> x_c >> y_c >> x_d >> y_d >> x_e >> y_e >> x_f >> y_f;
    while (x_a != 0 || y_a != 0 || x_b != 0 || y_b != 0 || x_c != 0 || y_c != 0 || x_d != 0 || y_d != 0 || x_e != 0 || y_e != 0 || x_f != 0 || y_f != 0)    {
        ld expected = calcTriangle(x_d, y_d, x_e, y_e, x_f, y_f);
        //ld distance = calcDistance(x_a, y_a, x_c, y_c);
        //distance = distance / 2;
        ld x_h = (x_a + x_c) / 2;
        ld y_h = (y_a + y_c) / 2;
        ld x_middle = (x_h + x_b) / 2;
        ld y_middle = (y_h + y_b) / 2;
        ld square = calcTriangle(x_a, y_a, x_h, y_h, x_b, y_b) * 2;
        x_start = x_a;
        y_start = y_a;
        x_end = x_c;
        y_end = y_c;
        while (abs(square - expected) > EPS)  {
            if (square > expected)  {
                x_end = x_h;
                y_end = y_h;
                x_h = (x_start + x_end) / 2;
                y_h = (y_start + y_end) / 2;
                x_middle = (x_h + x_b) / 2;
                y_middle = (y_h + y_b) / 2;
                square = calcTriangle(x_a, y_a, x_h, y_h, x_b, y_b) * 2;
            }
            else    {
                x_end = (2 * x_end) - x_start;
                y_end = (2 * y_end) - y_start;
//                x_end *= 2;
//                y_end *= 2;
                x_start = x_h;
                y_start = y_h;
                x_h = (x_start + x_end) / 2;
                y_h = (y_start + y_end) / 2;
                x_middle = (x_h + x_c) / 2;
                y_middle = (y_h + y_c) / 2;
                square = calcTriangle(x_a, y_a, x_h, y_h, x_b, y_b) * 2;
            }
        }
        ld x_mid = (x_h + x_b)/2;
        ld y_mid = (y_h + y_b)/2;
        ld x_g = (2 * x_mid - x_a);
        ld y_g = (2 * y_mid - y_a);
        printf ("%.3Lf %.3Lf %.3Lf %.3Lf\n", x_g, y_g, x_h, y_h);
        cin >> x_a >> y_a >> x_b >> y_b >> x_c >> y_c >> x_d >> y_d >> x_e >> y_e >> x_f >> y_f;
    }

    return 0;
}