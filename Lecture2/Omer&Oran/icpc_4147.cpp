#include <iostream>
#include <vector>
#include <math.h>


using namespace std;

int main() {
    int t;

    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<int> tour(pow(2, n) + 1, 1);
        int player;
        for (int i = 0; i < m; ++i) {
            cin >> player;
            tour[player] = 0;
        }

        int counter = 0;
        while (tour.size() != 3) {
            vector<int> new_tour(((tour.size() - 1) / 2) + 1, 0);
            for (int i = 1; i < tour.size(); i += 2) {
                if (tour[i] == 0 && tour[i + 1] == 0) {
                    new_tour[i / 2 + 1] = 0;
                }
                if (tour[i] == 0 && tour[i + 1] == 1) {
                    new_tour[i / 2 + 1] = 1;
                    counter++;
                }
                if (tour[i] == 1 && tour[i + 1] == 0) {
                    new_tour[i / 2 + 1] = 1;
                    counter++;
                }
                if (tour[i] == 1 && tour[i + 1] == 1) {
                    new_tour[i / 2 + 1] = 1;
                }
            }
            tour = new_tour;
        }

        if ((tour[1] == 0 && tour[2] == 1) || (tour[1] == 1 && tour[2] == 0)) counter++;
        cout << counter << "\n";
    }
    return 0;
}