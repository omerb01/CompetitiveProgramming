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

bool sortFunc(const pair<pair<int, int>, int> &a,
              const pair<pair<int, int>, int> &b) {
    if (a.first.first < b.first.first) { //normal sort.
        return true;
    } else if (a.first.first == b.first.first) {
        return a.first.second > b.first.second; // will put first in list last
    }
    return false;
}

int main() {
    int num_of_cases;
    cin >> num_of_cases;

    for (int i = 0; i < num_of_cases; ++i) {
        int price, sum = 0, num_of_people;
        //    <<limit, index>, paid_for>
        vector<pair<pair<int, int>, int>> limits;
        cin >> price >> num_of_people;
        limits.reserve(static_cast<unsigned long long int>(num_of_people));

        for (int j = 0; j < num_of_people; ++j) {
            int limit;
            cin >> limit;
            limits.emplace_back(make_pair(limit, j), 0);
            sum += limit;
        }

        if (sum < price) {
            cout << "IMPOSSIBLE" << endl;
            continue;
        }

        sort(limits.begin(), limits.end(), sortFunc);

        int total_paid = 0, index = 0;

        while (total_paid < price) {
            int min_price = (price - total_paid) / (num_of_people - index);
            if (limits[index].first.first >= min_price) {
                limits[index].second = min_price;
                total_paid += min_price;
            } else {
                limits[index].second = limits[index].first.first;
                total_paid += limits[index].first.first;
            }

            index++;
        }

        for (int k = 0; limits.size() > 0; k++) {
            for (int j = 0; j < limits.size(); ++j) {
                if (limits[j].first.second == k) {
                    cout << limits[j].second;
                    limits.erase(limits.begin() + j);
                    if (k != num_of_people - 1) {
                        cout << " ";
                    }
                }
            }
        }
        cout << endl;
    }

    return 0;
}