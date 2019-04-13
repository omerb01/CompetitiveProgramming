#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int find_min_index(vector<int> &arr) {
    int min = arr[0];
    int min_index = 0;
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] < min) {
            min = arr[i];
            min_index = i;
        }
    }
    return min_index;
}

int main() {
    int tests;

    cin >> tests;
    while (tests--) {
        int n, p;
        cin >> p >> n;

        vector<pair<int, int>> arr(n);
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            sum += a;
            arr[i] = pair<int, int>(a, -i);
        }

        if (sum < p) {
            cout << "IMPOSSIBLE" << endl;
            continue;
        }

        sort(arr.begin(), arr.end());
        vector<double> results(n, 0);

        for (int i = 0; i < n; ++i) {
            int min_index = arr[i].second * -1;
            int balanced = p / (n - i);

            if (arr[i].first < balanced) {
                results[min_index] = arr[i].first;
                p -= arr[i].first;
            } else {
                results[min_index] = balanced;
                p -= balanced;
            }
        }

        for (int i = 0; i < n; ++i) {
            cout << results[i];
            if (i != n - 1) cout << " ";
            else cout << endl;
        }
    }

    return 0;
}