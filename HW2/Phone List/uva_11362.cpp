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
typedef vector<string> vs;

int main() {
    int num_of_cases;
    cin >> num_of_cases;

    for (int i = 0; i < num_of_cases; ++i) {
        int phone_numbers;
        bool flag = false;
        cin >> phone_numbers;
        vs phone_arr;

        for (int j = 0; j < phone_numbers; ++j) {
            string phone;
            cin >> phone;
            phone_arr.push_back(phone);
        }

        sort(phone_arr.begin(), phone_arr.end());

        for (int j = 0; j < phone_numbers - 1; ++j) {
            if (phone_arr[j + 1].find(phone_arr[j]) != string::npos) {
                flag = true;
                break;
            }
        }
        if (flag) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }

    return 0;
}