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


bool isLegalQueenPlace(int board[8], int row, int col) {
    for (int i = 0; i < col; ++i) {
        if (board[i] == row) { // same row
            return false;
        }
        if (board[i] + i == row + col) { // lower diag on left
            return false;
        }

        if (board[i] - i == row - col) { // upper diag on left
            return false;
        }
    }
    return true;
}


void fillArr(int board[8], int sol_arr[72][8]) {
    static int i = 0;
    for (int j = 0; j < 8; ++j) {
        sol_arr[i][j] = board[j] + 1;
    }
    i++;
}

bool solveProb(int board[8], int sol_arr[72][8], int col) {
    if (col == 8) {
        fillArr(board, sol_arr);
        return true;
    }

    bool res = false;
    for (int row = 0; row < 8; ++row) {
        if (isLegalQueenPlace(board, row, col)) {
            board[col] = row;
            res = solveProb(board, sol_arr, col + 1) || res; // for backtracking
            board[col] = -1000; //backtracking
        }
    }

    return res;
}

int main() {

    int board[8] = {-1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000};
    int sol_arr[92][8]; //72 solutions

    //    ran the same program from introduction to CS and got all the possible solotions
    int col = 0;
    solveProb(board, sol_arr, col);
    int num_of_sets;
    cin >> num_of_sets;

    for (int i = 0; i < num_of_sets; ++i) {
        int counter = 1, x, y;

        cin >> x >> y;
        x--; // input is a number 1-9 we need 0-8.
        y--;

        cout << "SOLN       COLUMN" << endl;
        cout << " #      1 2 3 4 5 6 7 8" << endl;
        cout << endl;

        for (int j = 0; j < 92; ++j) {
            if (sol_arr[j][y] == x + 1) {
                if (counter <= 9) {
                    cout << " " << counter;
                } else {
                    cout << counter;
                }
                cout << "      ";

                for (int k = 0; k < 7; ++k) {
                    cout << sol_arr[j][k] << " ";
                }
                cout << sol_arr[j][7] << endl;
                counter++;
            }

        }

        if (i != num_of_sets - 1) {
            cout << endl;
        }
    }


}
