#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef pair<int, int> pii;
#define MAX_X 10000

typedef struct segment_t {
    pii start;
    pii end;
} Segment;

int find_max_height(const vector<Segment> &b, int x) {
    int max = 0;
    for (int i = 0; i < b.size(); ++i) {
        if (b[i].start.first <= x && x < b[i].end.first) {
            int curr_height = b[i].start.second;
            if (curr_height > max) max = curr_height;
        }
    }
    return max;
}

int main() {
    vector<Segment> b;
    int l, h, r;
    while (cin >> l >> h >> r) {
        if (l == 0 && h == 0 && r == 0) break;
        b.push_back({pii(l, h), pii(r, h)});
    }

    vector<pii> result;
    int prev = 0, next = 0;
    for (int curr_x = 0; curr_x < MAX_X; ++curr_x) {
        next = find_max_height(b, curr_x);
        if (prev != next) {
            result.push_back(pii(curr_x, next));
        }
        prev = next;
    }

    for (int i = 0; i < result.size(); ++i) {
        cout << result[i].first << " " << result[i].second;
        if (i != result.size() - 1) cout << " ";
    }
    cout << endl;

    return 0;
}