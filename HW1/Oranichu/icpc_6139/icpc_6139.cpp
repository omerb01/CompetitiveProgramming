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

int main() {
    int n, k ;
    while (cin >> n >> k) {

        int num, n1, n2;
        string letter;

        vector<int> neg, zeros, signs;

        for (unsigned i = 0; i < n; ++i) {
            cin >> num;
            if (num == 0) {
                zeros.push_back(i);
            } else if (num < 0) {
                neg.push_back(i);
            }
            signs.push_back(num);
        } // neg and zeros are sorted !

        for (int j = 0; j < k; ++j) {
            cin >> letter >> n1 >> n2;
            if (letter == "P") {
                n1--;
                n2--;

                auto neg_iter_low = lower_bound(neg.begin(), neg.end(), n1);
                auto zero_iter_low = lower_bound(zeros.begin(), zeros.end(), n1);

                auto neg_iter_high = upper_bound(neg.begin(), neg.end(), n2);
                auto zero_iter_high = upper_bound(zeros.begin(), zeros.end(), n2);

                if (zero_iter_high - zero_iter_low != 0) {
                    cout << "0";
                } else if ((neg_iter_high - neg_iter_low) % 2 == 0) {
                    cout << "+"; // even number of negs
                } else cout << "-";

            } else { // letter == "C"

                int index = n1 - 1, val = n2;

                if ((signs[index] > 0 && val > 0) ||
                    (signs[index] < 0 && val < 0) ||
                    (signs[index] == 0 && val == 0)) {

                    signs[index] = val;
                    continue;
                } // no need to change anything

                auto neg_iter = lower_bound(neg.begin(), neg.end(), index);
                auto zero_iter = lower_bound(zeros.begin(), zeros.end(), index);

                if (signs[index] > 0) {

                    if (val == 0) {
                        zeros.insert(zero_iter, index);
                    } else { // val < 0
                        neg.insert(neg_iter, index);
                    }

                } else if (signs[index] < 0) {

                    if (val == 0) {
                        zeros.insert(zero_iter, index);
                    } // otherwise he's positive no need to do anything special.
                    neg.erase(neg_iter);

                } else { //signs[index] == 0

                    if (val < 0) {
                        neg.insert(neg_iter, index);
                    }
                    zeros.erase(zero_iter);
                }

                signs[index] = val;

            }
        }

        cout << endl;
    }
    return 0;
}