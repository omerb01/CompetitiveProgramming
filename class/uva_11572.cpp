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
    int test_cases, n, num;
    map<int, int> last_show;
    cin >> test_cases;
    while (test_cases--)    {
        cin >> n;
        last_show.clear();
        int max_seq=0, current_seq=0, blocked=0;
        for (int i=1; i<=n; i++)    {
            cin >> num;
            if (last_show[num] == 0)    {
                current_seq++;
            }
            else    {
                blocked = max(blocked, last_show[num]);
                current_seq = i - blocked;
            }
            last_show[num] = i;
            max_seq = max(max_seq, current_seq);
        }
        cout << max_seq << endl;
    }
    return 0;
}