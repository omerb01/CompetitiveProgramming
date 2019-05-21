#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<pair<int, int>> points(n, pair<int, int>());
        int x, y;
        for (int i = 0; i < n; ++i) {
            cin >> x >> y;
            points[i] = pair<int, int>(x, y);
        }

        sort(points.begin(), points.end());

        int left = 0;
        int right = n - 1;

        int x_mid = (points[left].first + points[right].first) / 2;
        int y_mid = (points[left].second + points[right].second) / 2;

        while(left < right) {

            int curr_x_mid = (points[left].first + points[right].first) / 2;
            int curr_y_mid = (points[left].second + points[right].second) / 2;

            if (!(curr_x_mid == x_mid && curr_y_mid == y_mid)) {
                cout << "no" << endl;
                break;
            }

            left++;
            right--;
        }

        if (left >= right) cout << "yes" << endl;

    }
    return 0;
}