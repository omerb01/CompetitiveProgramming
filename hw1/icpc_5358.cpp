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
#include <fstream>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;

#define INITIAL -100

int countSols;

void printSolution(vector<int> board)   {
    countSols++;
    printf("%2d      ", countSols);
    for (int i=1; i<=8; i++)    {
        cout << board[i];
        if (i != 8) {
            cout << " ";
        }
    }
    cout << endl;
}

bool isLegal(vector<int> board, int row, int col)   {
    //position validation
    for (int i=1; i<=8; i++)    {
        if (board[i] == row) return false;
        if (board[i]-i == row-col) return false;
        if (board[i]+i == row+col) return false;
    }
    return true;
}

void solutionFinder(vector<int> board, int col) {
    if (col == 9)   {
        printSolution(board);
        return;
    }
    if (board[col] == INITIAL) {
        for (int row = 1; row <= 8; row++) {
            if (!isLegal(board, row, col)) {
                continue;
            }
            board[col] = row;
            solutionFinder(board, col + 1);
            board[col] = INITIAL;
        }
    }
    else    {
        solutionFinder(board, col+1);
    }
}

int main() {
    int datasets, row, col;
    string str;
    vector<int> board;
    cin >> datasets;
    while (datasets--)  {
        board.clear();
        for (int i=1; i<=9; i++) {
            board.push_back(INITIAL);
        }
        getline(cin, str);
        cin >> row;
        cin >> col;
        board[col] = row;
        cout << "SOLN       COLUMN" << endl;
        cout << " #      1 2 3 4 5 6 7 8" << endl << endl;
        countSols = 0;
        solutionFinder(board, 1);
        if (datasets != 0)  cout << endl;
    }
    return 0;
}