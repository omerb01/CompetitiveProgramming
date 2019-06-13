#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;

// input: weighted directed graph (g)
// output: the pairwise distances (d)
void FloydWarshall(const vvii &g, vvi &d) {
    // initialize distances according to the graph edges
    d.assign(g.size(), vi(g.size(), INF));
    for (int u = 0; u < g.size(); ++u) d[u][u] = 0;
    for (int u = 0; u < g.size(); ++u)
        for (ii e: g[u]) {
            int v = e.first;
            int w = e.second;
            d[u][v] = min(d[u][v], w);
        }
    // relax distances using the Floyd-Warshall algorithm
    for (int k = 0; k < g.size(); ++k)
        for (int u = 0; u < g.size(); ++u)
            for (int v = 0; v < g.size(); ++v)
                d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
}

void insert_input(vvii &g, int n) {
    for (int j = 0; j < n; ++j) {
        string line;
        cin >> line;
        for (int k = 0; k < n; ++k) {
            if (line[k] == 'Y') {
                g[j].push_back(ii(k, 1));
            }
        }
    }
}

void calc_dp(vector<vector<double>> &dp, int n, int r) {
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= r; j++)
            for (int k = j; k <= n * r; k++)
                dp[i][k] += double(dp[i - 1][k - j]) / double(r);
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case " << i << endl;

        int n, r;
        cin >> n >> r;

        vvii g = vvii(n, vii());
        insert_input(g, n);

        vvi d = vvi(n, vi(n, 0));
        FloydWarshall(g, d);

        vector<vector<double>> dp = vector<vector<double>>(101, vector<double>(10001, 0));
        calc_dp(dp, n, r);

        int c;
        cin >> c;
        for (int j = 0; j < c; ++j) {
            int a, b, m;
            cin >> a >> b >> m;

            int dist = d[a-1][b-1];
            double prob = 0;
            for (int k = 0; k <= m; ++k) {
                prob += dp[dist][k];
            }

            printf("%.6f\n", prob);
        }

        cout << endl;
    }
    return 0;
}