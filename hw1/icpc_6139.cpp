
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

int main() {
    int array_size, actions, temp;
    int a, b;
    while (scanf("%d", &array_size) != EOF) {
        string output = "";
        cin >> actions;
        vector<int> numbers;
        int count = 1;
        vector<int> zeros;
        vector<int> negatives;
        numbers.push_back(1);
        while (array_size--) {
            cin >> temp;
            numbers.push_back(temp);
            if (temp == 0) zeros.push_back(count);
            else if (temp < 0) negatives.push_back(count);
            count++;
        }
        string action;
        while (actions--) {
            cin >> action;
            cin >> a;
            cin >> b;
            if (action == "C") {
                int last_seen = numbers[a];
                if (last_seen == 0) {
                    vector<int>::iterator position = find(zeros.begin(),
                                                          zeros.end(), a);
                    zeros.erase(position);
                } else if (last_seen < 0) {
                    vector<int>::iterator position = find(negatives.begin(),
                                                          negatives.end(), a);
                    negatives.erase(position);
                }
                numbers[a] = b;
                if (b == 0) {
                    vector<int>::iterator it = lower_bound(zeros.begin(),
                                                           zeros.end(), a);
                    zeros.insert(it, a);
                } else if (b < 0) {
                    vector<int>::iterator it = lower_bound(negatives.begin(),
                                                           negatives.end(), a);
                    negatives.insert(it, a);
                }
            } else {
                //Check zeros
                auto lb = lower_bound(zeros.begin(), zeros.end(), a);
                auto up = upper_bound(zeros.begin(), zeros.end(), b);
                int count_zeros = 0;
                for (auto i=lb; i!=up; i++)  {
                    count_zeros++;
                }
                if (count_zeros != 0) output += "0";
                else {
                    //Check negatives
                    auto lb = lower_bound(negatives.begin(), negatives.end(), a);
                    auto up = upper_bound(negatives.begin(), negatives.end(), b);
                    int count_negs = 0;
                    for (auto i=lb; i!=up; i++)  {
                        count_negs++;
                    }
                    if (count_negs % 2 == 0) output += "+";
                    else output += "-";
                }

            }
        }
        cout << output << endl;
    }
    return 0;
}