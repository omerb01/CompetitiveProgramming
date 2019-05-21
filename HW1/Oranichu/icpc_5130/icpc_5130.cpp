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

#define DEBUG 0

#define HEX_SIZE 4

#define  H 202
#define  W 52*HEX_SIZE

#define INIT_MARK        0
#define INIT_SHAPE       1
#define SPACE_SEEN       2
#define BACKGROUND_MARK  -1

char temp_chars[4]= {'^','&','*','#'};

int grid[H][W];

void init_grid() {
    for (auto &i : grid) {
        for (int &j : i) {
            j = INIT_MARK;
        }
    }
}

void print_grid(int h, int w) {
    if (!DEBUG) {
        return;
    }
    cout << " ******************" << endl;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w * HEX_SIZE; j++) {
            if (grid[i][j] == BACKGROUND_MARK) {
                cout << "@";
            } else if (grid[i][j] >= 10) {
                cout << temp_chars[grid[i][j] - 10];
            }else {
                cout << grid[i][j];
            }
        }
        cout << endl;
    }
    cout << " ******************" << endl;

}

void fillBin(int i, int j, int num) {
    for (int k = 0; k < HEX_SIZE; ++k) {
        grid[i][j * HEX_SIZE + HEX_SIZE - k - 1] = num % 2;
        num /= 2;
    }
}

void mark(int h, int w, int i, int j, int color, int type) {
    if (i < 0 || j < 0 || i >= h || j >= w * HEX_SIZE) {
        return;
    }
    if (grid[i][j] != color) {
        return;
    }

    grid[i][j] = type;

    mark(h, w, i - 1, j, color, type); // up
    mark(h, w, i + 1, j, color, type); // down
    mark(h, w, i, j - 1, color, type); // left
    mark(h, w, i, j + 1, color, type); // right

}

int convertChar(char c) {
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    return c - '0';
}

int main() {
    int h, w, case_num = 1;
    char c;
    cin >> h >> w;
    while (h != 0 || w != 0) {
        init_grid();
        int shape_conter = 2; // first shape will be num 3

        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                cin >> c;
                fillBin(i, j, convertChar(c));
            }
        }

        for (int i = 0; i < h; i++) { // mark all backgroud using frame
                    mark(h, w, i, 0, INIT_MARK, BACKGROUND_MARK);
                    mark(h, w, i, w*HEX_SIZE -1, INIT_MARK, BACKGROUND_MARK);
        }

        for (int i = 0; i < w*HEX_SIZE; i++) { // mark all backgroud using frame
            mark(h, w, 0, i, INIT_MARK, BACKGROUND_MARK);
            mark(h, w, h-1, i, INIT_MARK, BACKGROUND_MARK);
        }

        print_grid(h,w);

        for (int i = 0; i < h; i++) { // mark all shapes
            for (int j = 0; j < w * HEX_SIZE; j++) {
                if (grid[i][j] == INIT_SHAPE) {
                    mark(h, w, i, j, INIT_SHAPE, ++shape_conter);
                }
            }
        }

        print_grid(h,w);

        int holes[shape_conter + 1];
        for (int k = 3; k <= shape_conter; ++k) {
            holes[k] = 0;
        }

        for (int i = 0; i < h; i++) { // mark holes
            for (int j = 0; j < w * HEX_SIZE; j++) {
                if (grid[i][j] == INIT_MARK) {
                    int shape_num = grid[i][j - 1];
                    print_grid(h, w);
                    mark(h, w, i, j, INIT_MARK, SPACE_SEEN);
                    print_grid(h, w);
                    holes[shape_num]++;
                }
            }
        }

        int letters[6] = {0, 0, 0, 0, 0, 0};
        char letters_chars[6] = {'A', 'D', 'J', 'K', 'S', 'W'};

        for (int l = 3; l <= shape_conter; ++l) {
            switch (holes[l]) {
                case 0:
                    letters[5]++;
                    break;
                case 1:
                    letters[0]++;
                    break;
                case 2:
                    letters[3]++;
                    break;
                case 3:
                    letters[2]++;
                    break;
                case 4:
                    letters[4]++;
                    break;
                case 5:
                    letters[1]++;
                    break;
            }
        }

        cout << "Case " << case_num++ << ": ";
        for (int m = 0; m < 6; ++m) {
            for (int i = 0; i < letters[m]; ++i) {
                cout << letters_chars[m];
            }
        }
        cout << endl;

        cin >> h >> w;
    }

    return 0;
}

