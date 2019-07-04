#include <iostream>

using namespace std;

int main() {
    int n, l, w, h;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> l;
        cin >> w;
        cin >> h;
        if (l > 20 or w > 20 or h > 20) {
            cout << "Case " + to_string(i + 1) + ": bad" + "\n";
        } else {
            cout << "Case " + to_string(i + 1) + ": good" + "\n";
        }
    }

    return 0;
}