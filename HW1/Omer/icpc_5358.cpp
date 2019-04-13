#include <iostream>
#include <vector>
#include <list>

using namespace std;

void rec(int curr_col, int given_row, int given_col, vector<int> board, vector<int> rows, vector<int> upd,
         vector<int> downd, list<vector<int>>& results) {
    if (curr_col == 8) {
        results.push_back(board);
        return;
    }

    if (curr_col != given_col) {
        for (int i = 0; i < 8; ++i) {
            if (rows[i] == 1 || upd[7 - curr_col + i] == 1 || downd[i + curr_col] == 1) continue;
            board[curr_col] = i;
            rows[i] = 1;
            upd[7 - curr_col + i] = 1;
            downd[i + curr_col] = 1;
            rec(curr_col + 1, given_row, given_col, board, rows, upd, downd, results);
            board[curr_col] = -1;
            rows[i] = 0;
            upd[7 - curr_col + i] = 0;
            downd[i + curr_col] = 0;
        }
    } else {
        if (rows[given_row] == 1 || upd[7 - curr_col + given_row] == 1 || downd[given_row + curr_col] == 1) return;
        board[curr_col] = given_row;
        rows[given_row] = 1;
        upd[7 - curr_col + given_row] = 1;
        downd[given_row + curr_col] = 1;
        rec(curr_col + 1, given_row, given_col, board, rows, upd, downd, results);
    }
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        string line;
        getline(cin, line);

        int row, col;
        cin >> row >> col;

        vector<int> board(8, -1);

        vector<int> rows(8, 0);
        vector<int> upd(15, 0);
        vector<int> downd(15, 0);

        list<vector<int>> results;

        rec(0, row - 1, col - 1, board, rows, upd, downd, results);

        int x = 0;

        cout << "SOLN       COLUMN" << endl;
        cout << " #      1 2 3 4 5 6 7 8" << endl << endl;
        int counteri = 0;
        for (auto i = results.begin(); i != results.end(); i++) {
            printf("%2d      ", ++counteri);
            int counterj = 0;
            for (auto j = i->begin(); j != i->end(); j++) {
                cout << (*j) + 1;
                if (++counterj != 8) cout << " ";
            }
            cout << endl;
        }
        if (n != 0) cout << endl;
    }
    return 0;
}