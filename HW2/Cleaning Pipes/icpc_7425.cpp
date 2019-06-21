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
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

typedef enum {
    CLOCKWISE,
    OPPOSITE,
    COLLINEAR
} Orientation;

// To find orientation of ordered triplet (p1, p2, p3).
Orientation orientation(pii p1, pii p2, pii p3)
{
    int val = (p2.second - p1.second) * (p3.first - p2.first) -
              (p2.first - p1.first) * (p3.second - p2.second);

    if (val == 0) return COLLINEAR;  // colinear

    return (val > 0)? CLOCKWISE: OPPOSITE; // clock or counterclock wise
}

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(pii p, pii q, pii r)
{
    if (q.first <= max(p.first, r.first) && q.first >= min(p.first, r.first) &&
        q.second <= max(p.second, r.second) && q.second >= min(p.second, r.second))
        return true;

    return false;
}

bool isCollision(pii a, pii b, pii c, pii d)    {
    Orientation comb1 = orientation(a, b, c);
    Orientation comb2 = orientation(a, b, d);
    Orientation comb3 = orientation(a, c, d);
    Orientation comb4 = orientation(b, c, d);

    //Different orientation for line 1 and 1 of of dots in line 2 (and the opposite)
    if (comb1!=comb2 && comb3 !=comb4)   {
        return true;
    }

    bool comb1_onSeg = onSegment(a, c, b);
    bool comb2_onSeg = onSegment(a, d, b);
    bool comb3_onSeg = onSegment(c, d, a);
    bool comb4_onSeg = onSegment(c, d, b);

    if ((comb1 == COLLINEAR && comb1_onSeg) || (comb2 == COLLINEAR && comb2_onSeg) || (comb3 == COLLINEAR && comb3_onSeg) || (comb4 == COLLINEAR && comb4_onSeg))   {
        return true;
    }

    return false;
}

bool DFS(vvi &graph, vector<int> &dis, int current, int distance)   {
    //visited
    if (dis[current] != -1) {
        return dis[current] == distance;
    }

    //not visited - mark and follow neighbours
    dis[current] = distance;
    for (int i=0; i<graph[current].size(); i++) {
        if (!DFS(graph, dis, graph[current][i], distance^1))   {
            return false;
        }
    }
    return true;
}

void bfs(const vvi& g, int s, vector<int>& distances) {
    queue<int> q; q.push(s);
    vector<bool> visible (g.size(),false);
    visible[s]=true;
    int dis=0;
    distances[0] = dis;     //init distance source -> source
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) if (!visible[v]) {
                visible[v] = true;
                q.push(v);
                distances[v]=(distances[u] + 1);    //v has been found by u
            }}}

/*bool isGraphBipartite(vvi& graph, vector<int>& distances)   {
    bool isBipartire = true;
    for (int v=0; v<graph.size(); v++)  {
        for (int u=0; u<graph[v].size(); u++)   {
            if (distances[u]%2 == distances[v]%2) isBipartire = false;
        }
    }
    return isBipartire;
}*/

int main()  {
    int wells_count, pipes_count;
    while (scanf("%d %d", &wells_count, &pipes_count) != EOF) {
        int x,y,z;
        vector<pii> wells;
        vector<pair<pii, pii>> pipes;   //(Start point , End point)
        while (wells_count--)   {
            cin >> x >> y;
            wells.push_back(make_pair(x,y));
        }
        int pipes_size = pipes_count;
        while (pipes_count--)   {
            cin >> z >> x >> y;
            pii end_point = make_pair(x, y);
            pii start_point = wells[z-1];
            pipes.push_back(make_pair(start_point, end_point));
        }
        vvi graph(pipes_size, vector<int>());
        for (int i=0; i<pipes_size; i++)    {
            for (int j=i+1; j<pipes_size; j++)  {
                if (pipes[i].first.first == pipes[j].first.first &&  pipes[i].first.second == pipes[j].first.second)    {
                    continue;
                }
                if (isCollision(pipes[i].first, pipes[i].second, pipes[j].first, pipes[j].second))  {
                    graph[i].emplace_back(j);
                    graph[j].emplace_back(i);
                }
            }
        }
        int isPossible = true;
        vector<int> dis;
        for (int i = 0; i < pipes_size; i++) {
            dis.push_back(-1);
        }

        for (int i = 0; i < pipes_size; ++i) {
            if (dis[i] == -1)
                isPossible = isPossible && DFS(graph, dis, i, 0);
        }
        if (isPossible)
            cout << "possible" << endl;
        else
            cout << "impossible" << endl;
        /*vector<int> distances(pipes_size, -1);
        for (int i=0; i<pipes_size; i++)    {
            if (distances[i]==-1)  bfs(graph, i, distances);
        }
        if (isGraphBipartite(graph, distances)) cout << "possible" << endl;
        else cout << "impossible" << endl;*/
    }
}