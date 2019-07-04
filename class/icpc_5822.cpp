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

int main() {
    int cities, kalpi, temp;
    int const_cities;
    cin >> cities;
    vector<pii> amount;
    map<int, int> cities_to_orig;
    cin >> kalpi;
    while (cities != -1 || kalpi != -1) {
        const_cities = cities;
        while (cities--)    {
            cin >> temp;
            amount.push_back(make_pair(temp, 1));
        }
        priority_queue<pii> elections(amount.begin(), amount.end());
        kalpi -= const_cities;
        while (kalpi--) {
            pii temp = elections.top();
            elections.pop();
            temp.second = temp.second + 1;
            temp.first = temp.first * (temp.second-1) / temp.second;
            while (temp.first >= elections.top().first && kalpi > 0) {
                temp.second = temp.second + 1;
                temp.first = temp.first * (temp.second-1) / temp.second;
            }
            elections.push(temp);
        }
        cout << elections.top().first << endl;
        string line="";
        getline(cin, line);
        amount.clear();
        cin >> cities;
        cin >> kalpi;
    }
    return 0;
}