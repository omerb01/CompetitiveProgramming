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
typedef vector<vector<int>> vvi;
typedef vector<int> vi;
typedef pair<int, int> pii;


bool topological_sort(const vvi &g, vi &order) {
    // compute indegree of all nodes
    vi indegree(g.size(), 0);
    for (int v = 0; v < g.size(); v++) for (int u : g[v]) indegree[u]++;
    // order sources first
    order = vector<int>();
    for (int v = 0; v < g.size(); v++) if (indegree[v] == 0) order.push_back(v);
    // go over the ordered nodes and remove outgoing edges,
    // add new sources to the ordering
    for (int i = 0; i < order.size(); i++)
        for (int u : g[order[i]]) {
            indegree[u]--;
            if (indegree[u] == 0) order.push_back(u);
        }
    return order.size() == g.size();
}


int main() {

    vvi g;

    for (int j = 0; j < 26; ++j) {
        g.push_back(vector<int>());
    }

    string w1, w2;
    bitset<26> used;

    cin >> w1 >> w2;
    while (w1 != "#" && w2 != "#") {
        for (int i = 0; i < w1.length() && i < w2.length(); ++i) {
            if (w1[i] != w2[i]) {
                used.set(static_cast<size_t>(w1[i] - 'A'));
                used.set(static_cast<size_t>(w2[i] - 'A'));
                g[w1[i] - 'A'].push_back(w2[i] - 'A');
                break;
            }
        }

        w1 = w2;
        cin >> w2;

    }
    vi order;
    topological_sort(g, order);

    for (int k = 0; k < 26; ++k) {
        if (used[k]) {
            cout << (char)((char)order[k] + 'A');
        }
    }

    cout << endl;

    return 0;
}