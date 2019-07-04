#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

bool check(const string &str) {
    int left = 0;
    int right = str.length() - 1;
    while (left < right) {
        if (str[left] != str[right]) return false;
        left++;
        right--;
    }
    return true;
}

int main() {
    string line;

    getline(cin, line);
    while (line != "DONE") {

        string parsed;
        for (int i = 0; i < line.length(); i++) {
            if (!(line[i] == '.' || line[i] == ',' || line[i] == '!' || line[i] == '?' || line[i] == ' '))
                parsed += line[i];
        }
        transform(parsed.begin(), parsed.end(), parsed.begin(), ::tolower);

        if (check(parsed)) cout << "You won't be eaten!" << endl;
        else cout << "Uh oh.." << endl;

        getline(cin, line);
    }

    return 0;
}