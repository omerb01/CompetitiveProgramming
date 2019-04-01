#include <iostream>
#include <vector>
#include <set>
#include <list>

using namespace std;

int main() {
    int test_cases;

    cin >> test_cases;
    while (test_cases--) {
        int n, m;
        cin >> n >> m;

        vector<int> days(m, 0);
        for (int i = 0; i < m; i++) {
            cin >> days[i];
        }

        vector<int> last_used_index(n, 0);
        set<int> zero_indexes;
        vector<int> result(m, -1);
        bool is_no = false;
        int counter = 0;

        for (int i = 0; i < m; ++i) {
            if (days[i] == 0) {
                zero_indexes.insert(i);
            } else {
                int index = last_used_index[days[i] - 1];
                auto it = zero_indexes.lower_bound(index);
                if (it == zero_indexes.end()) {
                    is_no = true;
                    break;
                }
                result[*it] = days[i];
                zero_indexes.erase(it);
                last_used_index[days[i] - 1] = i;
            }
        }

        if (is_no) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            for (auto i = zero_indexes.begin(); i != zero_indexes.end(); i++) result[*i] = 0;
            for (int i = 0; i < m; ++i) {
                if(result[i] != -1) cout << result[i] << " ";
            }
            cout << "\n";
        }
    }
}