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
typedef vector<pair<int, string>> v_ex2;
typedef pair<int, int> pii;

template<typename T>
bool cmp(const T &a, const T &b) {
    return a.first > b.first;
}

int main() {
    int T;
    std::cin >> T;
    for (int i = 0; i < T; ++i) {
        int D;
        std::cin >> D;

        v_ex2 v_low, v_high;

        for (int j = 0; j < D; ++j) {
//            car input
            int low, high;
            string name;
            cin >> name >> low >> high;

            v_low.push_back(make_pair(low, name));
            v_high.push_back(make_pair(high, name));

        }

        sort(v_low.begin(), v_low.end());
        sort(v_high.begin(), v_high.end());


        int Q;
        std::cin >> Q;
        int num;

        vector<string> vl, vh, v_res;

        for (int j = 0; j < Q; ++j) {
            cin >> num;

            auto  low_b = lower_bound(v_low.begin(), v_low.end(), make_pair(num, ""), cmp<pair<int, string>>) ;
            for (auto k = low_b; k!= v_low.end() ; ++k){
                vl.push_back(k->second);
            }

            auto up_b = upper_bound(v_high.begin(), v_high.end(), make_pair(num, ""), cmp<pair<int, string>>);
            for (auto k = v_high.begin(); k < up_b ; ++k){
                vh.push_back(k->second);
            }

            std::set_intersection(vl.begin(), vl.end(),
                                  vh.begin(), vh.end(),
                                  back_inserter(v_res));

            if (v_res.size() == 1) {
                cout << v_res[0] << endl;

            } else
                cout << "UNDETERMINED" << endl;

        }


    }
    return 0;
}