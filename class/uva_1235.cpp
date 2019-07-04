//
// Created by avish on 6/18/2019.
//

// This file contains implementations of some well-known graph algorithms.
// Written by Nofar Carmeli. Some code is based on the book Competitive Programming 3 by Steven and Felix Halim.

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <fstream>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;


/********** Min Spanning Tree **********/


struct unionfind {
    vector<int> rank;
    vector<int> parent;

    unionfind(int size) {
        rank = vector<int>(size, 0);
        parent = vector<int>(size);
        for (int i = 0; i < size; i++) parent[i] = i;
    }

    int find(int x) {
        int tmp = x;
        while (x != parent[x]) x = parent[x];
        while (tmp != x) {
            int remember = parent[tmp];
            parent[tmp] = x;
            tmp = remember;
        }
        return x;
    }

    void unite(int p, int q) {
        p = find(p);
        q = find(q);
        if (q == p) return;
        if (rank[p] < rank[q]) parent[p] = q;
        else parent[q] = p;
        if (rank[p] == rank[q]) rank[p]++;
    }
};


// input: edges v1->v2 of the form (weight,(v1,v2)),
//        number of nodes (n), all nodes are between 0 and n-1.
// output: weight of a minimum spanning tree.
// time: O(ElogV).
int Kruskal(vector<iii> &edges, int n) {
    sort(edges.begin(), edges.end());
    int mst_cost = 0;
    unionfind components(n);
    for (iii e : edges) {
        if (components.find(e.second.first) !=
            components.find(e.second.second)) {
            mst_cost += e.first;
            components.unite(e.second.first, e.second.second);
        }
    }
    return mst_cost;
}

int calc(string v1, string v2) {
    int sum =0 ;
    for (int i =0 ; i<4 ; i++) {
        sum += min (abs(v1[i]-v2[i]),10-abs(v1[i]-v2[i]));
    }
    return sum;
}

int main() {
        int t;
        cin >> t;
        for (int i=0;i<t;i++) {
            int n;
            vector<iii> e;
            vector<string> v;
            //v.push_back("0000");
            cin >> n;
            for (int j = 0; j <n; ++j) {
                string curr;
                cin >> curr;
                for (int k = 0; k < v.size() ; ++k) {
                    int dist = calc(v[k],curr);
                    e.push_back(make_pair(dist,make_pair(j,k)));
                    e.push_back(make_pair(dist,make_pair(k,j)));

                }
                v.push_back(curr);

            }

            int min=calc("0000", v[0]);
            for (int i=1; i<v.size(); i++)  {
                if (calc("0000", v[i]) < min) min = calc("0000", v[i]);
            }

            cout << Kruskal(e,v.size()) + min << endl;
        }
        return 0;
}