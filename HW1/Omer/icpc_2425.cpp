#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
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
        if (d > dist[u]) continue; // We may have found a shorter way to get to u after inserting it to q.
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
    int tests;
    cin >> tests;
    while (tests--) {
        string line;
        getline(cin, line);

        int n, e, t, m;
        cin >> n >> e >> t >> m;

        vvii g(n, vii());
        for (int i = 0; i < m; ++i) {
            int a, b, x;
            cin >> a >> b >> x;
            g[b - 1].push_back(ii(a - 1, x));
        }

        vi dist;
        Dijkstra(g, e - 1, dist);

        int counter = 0;
        for (int i = 0; i < n; ++i) {
            if (dist[i] <= t) counter++;
        }

        cout << counter << endl;
        if (tests != 0) cout << endl;
    }
    return 0;
}