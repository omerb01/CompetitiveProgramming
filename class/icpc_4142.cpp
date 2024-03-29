#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int d;
        cin >> d;

        vector<pair<int, int>> highs(d);
        vector<pair<int, int>> lows(d);
        map<int, string> dict;
        for (int i = 0; i < d; ++i) {
            string name;
            int l, h;
            cin >> name >> l >> h;
            dict[i] = name;
            lows[i] = pair<int, int>(l, i);
            highs[i] = pair<int, int>(h, i);
        }

        sort(lows.begin(), lows.end());
        sort(highs.begin(), highs.end());

        int q;
        cin >> q;

        for (int i = 0; i < q; ++i) {
            int p;
            cin >> p;
            auto it_l = lower_bound(lows.begin(), lows.end(), pair<int, int>(p, 10001));
            auto it_h = lower_bound(highs.begin(), highs.end(), pair<int, int>(p, -1));

            int greater_num = it_l - lows.begin();
            int smaller_num = highs.end() - it_h;

            if (smaller_num == 0 || greater_num == 0 || (smaller_num > 1 && greater_num > 1)) {
                cout << "UNDETERMINED" << endl;
                continue;
            }

            bool check = false;
            if (greater_num == 1) {
                int curr_index = (--it_l)->second;
                for (auto j = it_h; j != highs.end(); j++) {
                    if (j->second == curr_index) {
                        cout << dict[curr_index] << endl;
                        check = true;
                        break;
                    }
                }
            } else if (smaller_num == 1) {
                int curr_index = it_h->second;
                for (auto j = lows.begin(); j != it_l; j++) {
                    if (j->second == curr_index) {
                        cout << dict[curr_index] << endl;
                        check = true;
                        break;
                    }
                }
            }

            if(!check) cout << "UNDETERMINED" << endl;
        }

        if (t != 0) cout << endl;
    }

    return 0;
}