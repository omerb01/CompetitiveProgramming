#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <map>

using namespace std;

struct unionfind {
    vector<int> rank;
    vector<int> parent;
    vector<int> sizes;

    unionfind(int size) {
        rank = vector<int>(size, 0);
        parent = vector<int>(size);
        sizes = vector<int>(size, 1);
        for (int i = 0; i < size; i++)
            parent[i] = i;
    }

    int find(int x) {
        int tmp = x;
        while (x != parent[x]) x = parent[x];
        while (tmp != x)//for log*, not needed most of the time
        {
            int remember = parent[tmp];
            parent[tmp] = x;
            tmp = remember;
        }
        return x;
    }

    void Union(int p, int q) {
        p = find(p);
        q = find(q);
        if (q == p) {
            //alredy in the same group
            return;
        }
        if (rank[p] < rank[q]) {
            parent[p] = q;
            sizes[q] += sizes[p];
        } else {
            parent[q] = p;
            sizes[p] += sizes[q];
        }
        if (rank[p] == rank[q]) rank[p]++;
    }
};

int main() {
    int test_cases;
    cin >> test_cases;
    while (test_cases--) {
        int n;

        cin >> n;
        list<string> edges;
        map<string, int> m;
        int index = 0;

        for (int i = 0; i < n; i++) {
            string name1, name2;
            cin >> name1 >> name2;
            edges.push_back(name1);
            edges.push_back(name2);

            if (m.find(name1) == m.end()) {
                m.insert(pair<string, int>(name1, index++));
            }
            if (m.find(name2) == m.end()) {
                m.insert(pair<string, int>(name2, index++));
            }

        }

        unionfind uf(m.size());
        for (auto k = edges.begin(); k != edges.end(); k++) {
            string name1 = *k;
            k++;
            string name2 = *k;
            uf.Union(m.find(name1)->second, m.find(name2)->second);
            int x = uf.find(m.find(name1)->second);
            cout << uf.sizes[x] << endl;
        }
    }

    return 0;
}
