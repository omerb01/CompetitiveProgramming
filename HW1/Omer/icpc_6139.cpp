#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    while (cin >> n >> k) {
        vector<int> pos;
        vector<int> neg;
        vector<int> zer;
        vector<int> seq(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            int x;
            cin >> x;
            if (x > 0) pos.push_back(i);
            else if (x < 0) neg.push_back(i);
            else if (x == 0) zer.push_back(i);
            seq[i] = x;
        }

        for (int m = 0; m < k; m++) {
            char cmd;
            cin >> cmd;

            if (cmd == 'C') {
                int i, x;
                cin >> i >> x;
                if (seq[i] > 0) {
                    if (x > 0) {

                    } else if (x < 0) {
                        pos.erase(lower_bound(pos.begin(), pos.end(), i));
                        neg.insert(lower_bound(neg.begin(), neg.end(), i), i);
                    } else if (x == 0) {
                        pos.erase(lower_bound(pos.begin(), pos.end(), i));
                        zer.insert(lower_bound(zer.begin(), zer.end(), i), i);
                    }
                } else if (seq[i] < 0) {
                    if (x > 0) {
                        neg.erase(lower_bound(neg.begin(), neg.end(), i));
                        pos.insert(lower_bound(pos.begin(), pos.end(), i), i);
                    } else if (x < 0) {

                    } else if (x == 0) {
                        neg.erase(lower_bound(neg.begin(), neg.end(), i));
                        zer.insert(lower_bound(zer.begin(), zer.end(), i), i);
                    }
                } else if (seq[i] == 0) {
                    if (x > 0) {
                        zer.erase(lower_bound(zer.begin(), zer.end(), i));
                        pos.insert(lower_bound(pos.begin(), pos.end(), i), i);
                    } else if (x < 0) {
                        zer.erase(lower_bound(zer.begin(), zer.end(), i));
                        neg.insert(lower_bound(neg.begin(), neg.end(), i), i);
                    } else if (x == 0) {

                    }
                }
                seq[i] = x;
            }

            if (cmd == 'P') {
                int i, j;
                cin >> i >> j;

                int poses, negs, zeros;
                auto it1 = lower_bound(pos.begin(), pos.end(), i);
                auto it2 = upper_bound(pos.begin(), pos.end(), j);
                poses = it2 - it1;
                it1 = lower_bound(neg.begin(), neg.end(), i);
                it2 = upper_bound(neg.begin(), neg.end(), j);
                negs = it2 - it1;
                it1 = lower_bound(zer.begin(), zer.end(), i);
                it2 = upper_bound(zer.begin(), zer.end(), j);
                zeros = it2 - it1;

                if (zeros != 0) cout << "0";
                else if (negs % 2 != 0) cout << "-";
                else cout << "+";
            }
        }

        cout << "\n";
    }

    return 0;
}