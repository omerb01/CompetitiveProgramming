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

void createEdges(vvi& graph, vector<int> buttons, int current, vector<int>& isExist)   {
    if (isExist[current]) return;
    isExist[current] = 1;
    for (int i=0; i<buttons.size(); i++)    {
        graph[current].push_back((current+buttons[i])%10000);
        createEdges(graph, buttons, (current+buttons[i])%10000, isExist);
    }
}

int main(){
    int a,b,c, temp;
    int test = 1;
    while (cin >> a >> b >> c)  {
        if (a==0 && b==0 && c==0) break;
        vvi graph;
        vector<int> isExist;
        for (int i=0; i<=10000; i++)  {
            graph.push_back(vector<int>());
            isExist.push_back(0);
        }
        vector<int> buttons;
        for (int i=1; i<=c; i++)    {
            cin >> temp;
            buttons.push_back(temp);
        }
        createEdges(graph, buttons, a, isExist);
        vector<int> distances;
        bfs(graph, a, distances);
        if (distances[b] > 0)   {
            cout << "Case " << test << ": " << distances[b] << endl;
        }
        else    {
            cout << "Case " << test << ": Permanently Locked" << endl;
        }
        test++;
    }
    return 0;
}