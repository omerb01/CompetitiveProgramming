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
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;

void bfs(const vvi& g, int s, vector<int>& d ) {
    queue<int> q;
    q.push(s);
    vector<bool> visible (g.size(),false);
    visible[s]=true;
    d.assign(g.size(),0);
    d[s] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) if (!visible[v]) {
                visible[v] = true;
                d[v] = d[u]+1;
                q.push(v);
            }
    }
}


int main() {
    int a,b;
    int test = 1;
    while (cin >> a >> b)   {
        if (a==0 && b==0) break;
        vector<vector<int>> graph;
        vector<int> isExist;
        for (int i=0; i<=100; i++)  {
            graph.push_back(vector<int>());
            isExist.push_back(0);
        }
        graph[a].push_back(b);
        isExist[a] = 1;
        while (cin >> a >> b)   {
            if (a==0 && b==0) break;
            graph[a].push_back(b);
            isExist[a] = 1;
        }
        int countVertex = 0;
        int sumLength = 0;
        for (int i=1; i<=100; i++)  {
            if (isExist[i]==1)  {
                countVertex++;
                vector<int> distances;
                bfs(graph, i, distances);
                for (int j=1; j<=100 ; j++) {
                    if (j!=i) sumLength += distances[j];
                }
            }
        }
        double numVertex = (double)countVertex;
        double length = ((double)sumLength) / ((numVertex*numVertex) - numVertex);
        printf("Case %d: average length between pages = %.3f clicks\n", test, length);
        test++;
    }


    return 0;
}