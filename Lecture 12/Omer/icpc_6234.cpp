// This file contains implementations of some well-known graph algorithms.
// Written by Nofar Carmeli. Some code is based on the book Competitive Programming 3 by Steven and Felix Halim.

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <fstream>

using namespace std;

typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;

/********** Max Flow **********/


int augment(vvi& res, int s, int t, const vi& p, int minEdge) {
    // traverse the path from s to t according to p.
    // change the residuals on this path according to the min edge weight along this path.
    // return the amount of flow that was added.
    if (t == s) {
        return minEdge;
    } else if (p[t] != -1) {
        int f = augment(res, s, p[t], p, min(minEdge, res[p[t]][t]));
        res[p[t]][t] -= f;
        res[t][p[t]] += f;
        return f;
    }
    return 0;
}

// input: number of nodes (n), all nodes are between 0 and n-1,
//        edges v1->v2 of the form (weight,(v1,v2)), source (s) and target (t).
// output: max flow from s to t over the edges.
// time: O(VE^2) and O(EF).
int EdmondsKarp (int n, vector<iii>& edges, int s, int t) {
    // initialise adjacenty list and residuals adjacency matrix
    vvi res(n,vi(n,0));
    vvi adj(n);
    for (iii e : edges) {
        res[e.second.first][e.second.second] += e.first;
        adj[e.second.first].push_back(e.second.second);
        adj[e.second.second].push_back(e.second.first);
    }
    // while we can add flow
    int addedFlow, maxFlow = 0;
    do {
        // save to p the BFS tree from s to t using only edges with residuals
        vi dist(res.size(), INF);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        vi p(res.size(), -1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;
            for (int v : adj[u]) if (res[u][v] > 0 && dist[v] == INF) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                    p[v] = u;
                }
        }
        // add flow on the path between s to t according to p
        addedFlow = augment(res, s, t, p, INF);
        maxFlow += addedFlow;
    } while (addedFlow > 0);
    return maxFlow;
}

int getIndex (int i, int j, int length) {
    return (i*length) + j;
}

vector<pair<int, int>> getCharNeighbours(vector<string> input, char ch, int i, int j)   {
    vector<pair<int, int>> combinations;
    if (i>0)    {
        if (input[i-1][j] == ch)    {
            combinations.push_back(make_pair(i-1, j));
        }
    }
    if (j>0)    {
        if (input[i][j-1] == ch)    {
            combinations.push_back(make_pair(i, j-1));
        }
    }
    if (i<input.size()-1)   {
        if (input[i+1][j] == ch)    {
            combinations.push_back(make_pair(i+1, j));
        }
    }
    if (j<input[0].size()-1)    {
        if (input[i][j+1] == ch)    {
            combinations.push_back(make_pair(i, j+1));
        }
    }
    return combinations;
}

int main()  {
    //ofstream out("icpc6234.txt");
    string str;
    bool print= false;
    while (getline(cin, str))    {
        vector<string> input;
        vector<iii> weighted;
        input.push_back(str);;
        while (getline(cin, str)) {
            if (str.empty())    {
                break;
            }
            input.push_back(str);
        }
        int nodes = input.size() > 0 ? input.size() * input[0].length() : 0;
        int source = nodes++;
        int target = nodes++;
        vector<pair<int, int>> is_w;
        for (int i = 0; i < input.size(); i++) {
            for (int j = 0; j < input[0].size(); j++) {
                if (input[i][j] == 'W') {
                    int w_index_omer = getIndex(i, j, input[0].length());
                    weighted.push_back(make_pair(1, make_pair(source, w_index_omer)));
                    int new_w_index_omer = nodes++;
                    weighted.push_back(make_pair(1, make_pair(w_index_omer, new_w_index_omer)));
                    vector<pair<int, int>> good_neigh = getCharNeighbours(input,
                                                                          'I',
                                                                          i, j);
                    for (int k = 0; k < good_neigh.size(); k++) {
                        int neigh_index = getIndex(good_neigh[k].first,
                                                   good_neigh[k].second,
                                                   input[0].length());
                        weighted.push_back(
                                make_pair(1, make_pair(new_w_index_omer, neigh_index)));
                    }
                }
                if (input[i][j] == 'I') {
                    int i_index_omer = getIndex(i, j, input[0].length());
                    int new_i_index_omer = nodes++;
                    weighted.push_back(make_pair(1, make_pair(i_index_omer, new_i_index_omer)));
                    vector<pair<int, int>> good_neigh = getCharNeighbours(input,
                                                                          'N',
                                                                          i, j);
                    for (int k = 0; k < good_neigh.size(); k++) {
                        int neigh_index = getIndex(good_neigh[k].first,
                                                   good_neigh[k].second,
                                                   input[0].length());
                        weighted.push_back(make_pair(1, make_pair(new_i_index_omer, neigh_index)));
                    }
                }
                if (input[i][j] == 'N') {
                    int n_index_omer = getIndex(i, j, input[0].length());
                    int new_n_index_omer = nodes++;
                    weighted.push_back(make_pair(1, make_pair(n_index_omer, new_n_index_omer)));
                    weighted.push_back(make_pair(1, make_pair(new_n_index_omer, target)));
                }
            }
        }
        long long max_flow = EdmondsKarp(nodes, weighted, source, target);
        cout << max_flow << endl;
    }
    return 0;
}