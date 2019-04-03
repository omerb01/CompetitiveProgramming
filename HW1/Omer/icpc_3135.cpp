#include <iostream>
#include <set>
#include <map>

using namespace std;
typedef pair<int, int> pii;

int main() {
    set<pii> regs;
    map<int, int> dict;
    string line;

    cin >> line;
    while (line != "#") {
        int q_num, period;
        cin >> q_num >> period;
        regs.insert(pii(period, q_num));
        dict[q_num] = period;
        cin >> line;
    }

    int k;
    cin >> k;

    int time = 0;
    for (int i = 0; i < k; i++) {
        auto it = regs.upper_bound(pii(time, 0));
        time = it->first;
        pii new_r = pii(it->first + dict[it->second], it->second);
        cout << it->second << "\n";

        regs.erase(it);
        regs.insert(new_r);
    }

    return 0;
}