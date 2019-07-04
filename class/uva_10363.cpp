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
    int n;

    cin >> n;
    while (n--) {
        int nx = 0;
        int no = 0;
        string line;
        char board[3][3];

        for (int i = 0; i < 3; i++) {
            cin >> line;
            for (int j = 0; j < 3; j++) {
                board[i][j] = line[j];
                if (line[j] == 'X') nx++;
                else if (line[j] == 'O') no++;
            }
        }

        int x_win_counter = 0;
        int o_win_counter = 0;

        //check rows:
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                if (board[i][0] == 'X') x_win_counter++;
                else if (board[i][0] == 'O') o_win_counter++;
            }
        }
        //check columns:
        for (int i = 0; i < 3; i++) {
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                if (board[0][i] == 'X') x_win_counter++;
                else if (board[0][i] == 'O') o_win_counter++;
            }
        }
        //check diags:
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == 'X') x_win_counter++;
            else if (board[0][0] == 'O') o_win_counter++;
        }
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == 'X') x_win_counter++;
            else if (board[0][2] == 'O') o_win_counter++;
        }

        bool isvalid = true;

        if (!(nx == no || nx == no + 1)) isvalid = false;
        if (nx == no && x_win_counter > 0) isvalid = false;
        if (nx == no + 1 && o_win_counter > 0) isvalid = false;

        if (isvalid) cout << "yes" << endl;
        else cout << "no" << endl;
    }

    return 0;
}