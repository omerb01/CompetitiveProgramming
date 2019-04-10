
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

class query    {
public:
    int query_id;
    int first;
    int time;
    query(int query_id, int first)    {
        this->query_id = query_id;
        this->first = first;
        this->time = first;
        }
    void updateTime()    {
        this->time += this->first;
    }
};

struct compareQuery {
    bool operator()(query* const& q1, query* const& q2)   {
        if (q1->time < q2->time) return false;
        if (q1->time == q2->time && q1->query_id < q2->query_id) return false;
        return true;
    }
};

int main() {
    string action;
    int id, first;
    vector<query*> queries;
    cin >> action;
    while (action != "#")   {
        cin >> id;
        cin >> first;
        queries.push_back(new query(id, first));
        cin >> action;
    }
    priority_queue<query*, vector<query*>, compareQuery> heap(queries.begin(), queries.end());
    int iterations;
    cin >> iterations;
    if (!heap.empty())  {
        while (iterations--)    {
            query* temp2 = heap.top();
            heap.pop();
            cout << temp2->query_id << endl;
            temp2->updateTime();
            heap.push(temp2);
        }
    }
    return 0;
}