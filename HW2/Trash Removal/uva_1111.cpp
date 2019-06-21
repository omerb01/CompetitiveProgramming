#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <chrono>
#include <vector>
#include <bitset>
#include <stdio.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <iomanip>

using namespace std;

#define INF 1e9
#define EPS 1e-9
#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

struct PT
{
    double x,y;
    PT()    {
        x = 0;
        y = 0;
    }
    PT (double x, double y) : x(x), y(y)    {}

    // compare the lexicographic order of 2 points
    // first compare x, if 2 x's are equal, compare y
    bool operator < (const PT& _p) const
    {
        if (fabs(x - _p.x) > EPS) {
            return (x < _p.x);
        } else {
            return (y < _p.y);
        }
    }
};

// check p3 (leftmost) -> p2 -> p1 (rightmost) left turn (not right turn)
bool left(PT& p1, PT& p2, PT& p3)
{
    double cross = (p2.x - p3.x) * (p1.y - p3.y) - (p2.y - p3.y) * (p1.x - p3.x);

    if (fabs(cross) <= EPS)
        return true;    // to delete p2
    if (cross > 0)
        return true;
    return false;
}

double dist(PT a, PT b)
{
    return hypot(a.x-b.x, a.y-b.y);
}

struct vec {
    double x, y; vec(double a, double b) {x = a; y = b;}
};

PT translate(PT p, vec v){        // translate p according to v
    return PT(p.x + v.x, p.y + v.y);
}

double dot(vec a, vec b) {return (a.x*b.x + a.y*b.y);}

vec tovec(PT a, PT b){
    return vec(b.x - a.x, b.y-a.y);
}

vec scale (vec v, double s) {return vec(v.x*s, v.y*s);}

double norm_sq(vec v) {return v.x*v.x + v.y*v.y;}

double angle(PT a, PT o, PT b){  // returns angle aob in rad
    vec oa = tovec(o, a), ob = tovec(o, b);
    return acos(dot(oa, ob)/sqrt(norm_sq(oa)*norm_sq(ob)));
}

double dist_to_line(PT p, PT a, PT b, PT &c)
{
    // c = a + u * ab
    // projection : dot(ap,ab) / sq(ab)
    vec ap = tovec(a,p), ab = tovec(a,b);
    double u = dot(ap,ab) / norm_sq(ab);
    c = translate(a, scale(ab, u));
    return dist(p,c);
}

double cross(vec a, vec b) {return a.x*b.y - a.y*b.x;}

vector<PT> ConvexHull(vector<PT> Points) {
    //-------------- incremental alg. ---------
// upper hull
    sort(Points.begin(), Points.end());
    stack<PT> stk_up;
    stk_up.push(Points[0]);
    stk_up.push(Points[1]);
    for (int i=2; i<Points.size(); i++) {
        while ((stk_up.size() >= 2)) {
            PT p2, p3;
            p2 = stk_up.top();
            stk_up.pop();
            p3 = stk_up.top();
            if (!left(Points[i], p2, p3)){
                stk_up.push(p2);
                break;
            }
        }
        stk_up.push(Points[i]);
    }
// lower hull
    for (int i=0; i<Points.size(); i++) {
        Points[i].x = -Points[i].x;
        Points[i].y = -Points[i].y;
    }
    sort(Points.begin(), Points.end());
    stack<PT> stk_low;
    stk_low.push(Points[0]);
    stk_low.push(Points[1]);
    for (int i=2; i<Points.size(); i++) {
        while ((stk_low.size() >= 2)) {
            PT p2, p3;
            p2 = stk_low.top();
            stk_low.pop();
            p3 = stk_low.top();
            if (!left(Points[i], p2, p3)){
                stk_low.push(p2);
                break;
            }
        }
        stk_low.push(Points[i]);
    }

    // print convex hull - cw order from leftmost point
    vector<PT> CH;
    stk_low.pop();
    PT p;
    while (!stk_low.empty()) {
        p = stk_low.top();
        p.x = -p.x;
        p.y = -p.y;
        CH.push_back(p);
        stk_low.pop();
    }
    stk_up.pop();
    while (!stk_up.empty()) {
        CH.push_back(stk_up.top());
        stk_up.pop();
    }
    reverse(CH.begin(), CH.end());  // ccw -> cw
    return CH;
}

double findMin(vector<double> widths){
    if (widths.size() == 0) {
        return INF;
    }
    double min = widths[0];
    for (int i=1; i<widths.size(); i++) {
        if (min > widths[i]) min = widths[i];
    }
    return min;
}

int main()  {
    int points, x, y, cnt=0;
    cin >> points;
    while (points != 0) {
        vector<PT> input;
        while (points--)    {
            cin >> x >> y;
            input.push_back(PT(x, y));
        }

        vector<PT> ch = ConvexHull(input);

        //ch.size cannot be zero
        int low = 0, high=0;
        double min = ch[0].y;
        double max = ch[0].y;

        for (int i=1; i<ch.size(); i++) {
            if (ch[i].y < min)  {
                min = ch[i].y;
                low = i;
            }
            if (ch[i].y > max)  {
                max = ch[i].y;
                high = i;
            }
        }

        PT low_point = PT(ch[low].x - 1, ch[low].y);
        PT low_next_point =  ch[(low + 1)%ch.size()];
        PT high_point = PT(ch[high].x + 1, ch[high].y);
        PT high_next_point = ch[(high + 1)%ch.size()];
        double alpha = angle(low_point, ch[low], low_next_point);
        double beta = angle(high_point, ch[high], high_next_point);
        vector<double> widths;
        int iterator1 = low, iterator2 = high;

        PT dummy = PT();

        while (iterator1 != high || iterator2 != low)   {
            if (alpha<beta)   {
                beta -= alpha;
                widths.push_back(dist_to_line(ch[iterator2], ch[iterator1], ch[(iterator1 + 1)%ch.size()], dummy));
                alpha = PI - angle(ch[iterator1], ch[(iterator1 + 1)%ch.size()], ch[(iterator1 + 2)%ch.size()]);
                iterator1++;
                iterator1 = iterator1 % ch.size();
            }
            else    {
                alpha -= beta;
                widths.push_back(dist_to_line(ch[iterator1], ch[iterator2], ch[(iterator2 + 1)%ch.size()], dummy));
                beta = PI - angle(ch[iterator2], ch[(iterator2 + 1)%ch.size()], ch[(iterator2 + 2)%ch.size()]);
                iterator2++;
                iterator2 = iterator2 % ch.size();
            }
        }
        cout << "Case " << ++cnt << ": ";
        cout << fixed << setprecision(2) << ((round(findMin(widths)*100))/100);
        cout << endl;
        cin >> points;
    }
    return 0;
}