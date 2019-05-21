#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print_image(const vector<vector<int>> &image) {
    int h = image.size();
    int w = image[0].size();
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cout << image[i][j];
        }
        cout << endl;
    }
}

void insert_hex(vector<vector<int>> &image, int i, int j, char hex) {
    if (hex == '0') {
        image[i][j] = 0;
        image[i][j + 1] = 0;
        image[i][j + 2] = 0;
        image[i][j + 3] = 0;
    } else if (hex == '1') {
        image[i][j] = 0;
        image[i][j + 1] = 0;
        image[i][j + 2] = 0;
        image[i][j + 3] = 1;
    } else if (hex == '2') {
        image[i][j] = 0;
        image[i][j + 1] = 0;
        image[i][j + 2] = 1;
        image[i][j + 3] = 0;
    } else if (hex == '3') {
        image[i][j] = 0;
        image[i][j + 1] = 0;
        image[i][j + 2] = 1;
        image[i][j + 3] = 1;
    } else if (hex == '4') {
        image[i][j] = 0;
        image[i][j + 1] = 1;
        image[i][j + 2] = 0;
        image[i][j + 3] = 0;
    } else if (hex == '5') {
        image[i][j] = 0;
        image[i][j + 1] = 1;
        image[i][j + 2] = 0;
        image[i][j + 3] = 1;
    } else if (hex == '6') {
        image[i][j] = 0;
        image[i][j + 1] = 1;
        image[i][j + 2] = 1;
        image[i][j + 3] = 0;
    } else if (hex == '7') {
        image[i][j] = 0;
        image[i][j + 1] = 1;
        image[i][j + 2] = 1;
        image[i][j + 3] = 1;
    } else if (hex == '8') {
        image[i][j] = 1;
        image[i][j + 1] = 0;
        image[i][j + 2] = 0;
        image[i][j + 3] = 0;
    } else if (hex == '9') {
        image[i][j] = 1;
        image[i][j + 1] = 0;
        image[i][j + 2] = 0;
        image[i][j + 3] = 1;
    } else if (hex == 'a') {
        image[i][j] = 1;
        image[i][j + 1] = 0;
        image[i][j + 2] = 1;
        image[i][j + 3] = 0;
    } else if (hex == 'b') {
        image[i][j] = 1;
        image[i][j + 1] = 0;
        image[i][j + 2] = 1;
        image[i][j + 3] = 1;
    } else if (hex == 'c') {
        image[i][j] = 1;
        image[i][j + 1] = 1;
        image[i][j + 2] = 0;
        image[i][j + 3] = 0;
    } else if (hex == 'd') {
        image[i][j] = 1;
        image[i][j + 1] = 1;
        image[i][j + 2] = 0;
        image[i][j + 3] = 1;
    } else if (hex == 'e') {
        image[i][j] = 1;
        image[i][j + 1] = 1;
        image[i][j + 2] = 1;
        image[i][j + 3] = 0;
    } else if (hex == 'f') {
        image[i][j] = 1;
        image[i][j + 1] = 1;
        image[i][j + 2] = 1;
        image[i][j + 3] = 1;
    }
}

void mark(vector<vector<int>> &image, int i, int j, int from, int to) {
    int h = image.size();
    int w = image[0].size();

    if (image[i][j] == from) image[i][j] = to;

    if (i != 0 && image[i - 1][j] == from) mark(image, i - 1, j, from, to);
    if (j != 0 && image[i][j - 1] == from) mark(image, i, j - 1, from, to);
    if (j != w - 1 && image[i][j + 1] == from) mark(image, i, j + 1, from, to);
    if (i != h - 1 && image[i + 1][j] == from) mark(image, i + 1, j, from, to);
}

pair<int, int> find_one(vector<vector<int>> &image, int i, int j) {
    int h = image.size();
    int w = image[0].size();

    if (image[i][j] == 1) return pair<int, int>(i, j);

    if (i != h - 1)
        return find_one(image, i + 1, j);
    else if (j != w - 1)
        return find_one(image, 0, j + 1);

    return pair<int, int>(-1, -1);
}

void find_zero(vector<vector<int>> &image, int i, int j, pair<int, int> &result, bool &check) {
    int h = image.size();
    int w = image[0].size();

    if (image[i][j] == 0) {
        result = pair<int, int>(i, j);
        check = false;
    }

    if (image[i][j] == 3) image[i][j] = 4;

    if (check && i != 0 && (image[i - 1][j] == 3 || image[i - 1][j] == 0)) find_zero(image, i - 1, j, result, check);
    if (check && j != 0 && (image[i][j - 1] == 3 || image[i][j - 1] == 0)) find_zero(image, i, j - 1, result, check);
    if (check && j != w - 1 && (image[i][j + 1] == 3 || image[i][j + 1] == 0))
        find_zero(image, i, j + 1, result, check);
    if (check && i != h - 1 && (image[i + 1][j] == 3 || image[i + 1][j] == 0))
        find_zero(image, i + 1, j, result, check);

}

char get_char(int num) {
    char c = '$';
    if (num == 0) c = 'W';
    else if (num == 1) c = 'A';
    else if (num == 2) c = 'K';
    else if (num == 3) c = 'J';
    else if (num == 4) c = 'S';
    else if (num == 5) c = 'D';

    return c;
}

int main() {
    int t = 1;
    int h, w;
    while (cin >> h >> w) {
        if (h == 0 && w == 0) break;

        vector<vector<int>> image(h, vector<int>(w * 4, 0));
        for (int i = 0; i < h; ++i) {
            string line;
            cin >> line;
            for (int j = 0; j < w; ++j) {
                insert_hex(image, i, j * 4, line[j]);
            }
        }
        w *= 4;

        for (int j = 0; j < w - 1; ++j) {
            if (image[0][j] == 0)
                mark(image, 0, j, 0, 2);
        }
        for (int i = 0; i < h - 1; ++i) {
            if (image[i][0] == 0)
                mark(image, i, 0, 0, 2);
        }
        for (int i = 0; i < h - 1; ++i) {
            if (image[i][w - 1] == 0)
                mark(image, i, w - 1, 0, 2);
        }
        for (int j = 0; j < w - 1; ++j) {
            if (image[h - 1][j] == 0)
                mark(image, h - 1, j, 0, 2);
        }

        vector<char> chars = vector<char>();

        pair<int, int> one = find_one(image, 0, 0);
        while (one != pair<int, int>(-1, -1)) {
            mark(image, one.first, one.second, 1, 3);
            int counter = 0;
            pair<int, int> zero = pair<int, int>(-1, -1);
            bool check = true;
            find_zero(image, one.first, one.second, zero, check);
            mark(image, one.first, one.second, 4, 3);
            while (zero != pair<int, int>(-1, -1)) {
                mark(image, zero.first, zero.second, 0, 2);
                counter++;
                zero = pair<int, int>(-1, -1);
                check = true;
                find_zero(image, one.first, one.second, zero, check);
                mark(image, one.first, one.second, 4, 3);
            }

            chars.push_back(get_char(counter));
            one = find_one(image, 0, 0);
        }

        cout << "Case " << t++ << ": ";
        sort(chars.begin(), chars.end());
        for (int k = 0; k < chars.size(); ++k) {
            cout << chars[k];
        }
        cout << endl;
    }
    return 0;
}