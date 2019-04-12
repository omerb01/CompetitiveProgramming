
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

struct participant  {
public:
    int index;
    int leftToGive;
    participant(int index, int leftToGive)    {
        this->index = index;
        this->leftToGive = leftToGive;
    }
};

struct compareParticipant {
    bool operator()(participant* const& q1, participant* const& q2)   {
        if (q1->leftToGive > q2->leftToGive) return false;
        if (q1->leftToGive == q2->leftToGive && q1->index < q2->index) return false;
        return true;
    }
};

int main()  {
    int test_cases;
    cin >> test_cases;
    while (test_cases--)    {
        int price, ppl, temp, shouldPerPpl, activePpl;
        cin >> price;
        cin >> ppl;
        vector<int> willing;
        vector<int> actual;
        vector<participant*> leftToGive;
        int i=0;
        while (i<ppl)   {
            cin >> temp;
            willing.push_back(temp);
            actual.push_back(0);
            leftToGive.push_back(new participant(i, temp));
            i++;
        }
        activePpl = ppl;
        while (price > 0)   {
            priority_queue<participant*, vector<participant*>, compareParticipant> heap(leftToGive.begin(), leftToGive.end());
            participant* current = heap.top();
            //Trigger for stopping - the most "rich" guy has 0 in account
            if (willing[current->index] == 0) {
                break;
            }
            shouldPerPpl = (price / ppl == 0)? 1 : price / ppl;
            while (heap.size() > 0 && price > 0) {
                participant* current = heap.top();
                heap.pop();
                if (willing[current->index] > shouldPerPpl) {
                    willing[current->index] -= shouldPerPpl;
                    leftToGive[current->index]->leftToGive -= shouldPerPpl;
                    actual[current->index] += shouldPerPpl;
                    price -= shouldPerPpl;
                }
                else if (willing[current->index] >= 0)   {
                    actual[current->index] += willing[current->index];
                    price -= willing[current->index];
                    willing[current->index] = 0;
                    leftToGive[current->index]->leftToGive = 0;
                    activePpl--;
                }
            }
        }
        if (price > 0) {
            cout << "IMPOSSIBLE" << endl;
        }
        else    {
            for (int i=0; i<actual.size(); i++) {
                cout << actual[i];
                if (i != actual.size() - 1) cout << " ";
            }
            cout << endl;
        }
    }
    return 0;
}