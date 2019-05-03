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
typedef pair<int, int> pii;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;

// input: digraph (g), source (s)
// output: distances from s (dist)
void Dijkstra(const vvii &g, int s, vi &dist) {
    dist = vi(g.size(), INF);
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> q;
    q.push({0, s});
    while (!q.empty()) {
        ii front = q.top();
        q.pop();
        int d = front.first, u = front.second;
        if (d > dist[u])
            continue; // We may have found a shorter way to get to u after inserting it to q.
        // In that case, we want to ignore the previous insertion to q.
        for (ii next : g[u]) {
            int v = next.first, w = next.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                q.push({dist[v], v});
            }
        }
    }
}

int main() {
    int test_cases;
    cin >> test_cases;

    string empty_line;
    for (int i = 0; i < test_cases; ++i) {
        getline(cin, empty_line);

        int N, E, T, M;
        cin >> N >> E >> T >> M;

        vvii g;

        for (int k = 0; k < N; ++k) {   // init graph
            g.push_back(vii());
        }

        for (int j = 0; j < M; ++j) {
            int a, b, dist;
            cin >> a >> b >> dist;

            g[b-1].push_back(make_pair(a-1, dist));

        }

        vi dists_vec;

        Dijkstra(g, E-1, dists_vec);

        int counter = 0;
        for (int l = 0; l < N; ++l) {
            if (dists_vec[l] <= T) {
                counter++;
            }
        }

        cout << counter;
        if (i != test_cases-1) {
            cout << endl << endl;
        }
        else cout << endl;

    }
    return 0;
}
