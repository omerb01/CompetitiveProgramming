
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
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;

string SA_str; // the input string, up to 100K characters
int n; // the length of input string
vi RA, tempRA; // rank array and temporary rank array
vi SA, tempSA; // suffix array and temporary suffix array
vi c; // for counting/radix sort
vi Phi,PLCP,LCP;

void countingSort(int k) { // O(n)
    int n = SA_str.length()-1;
    int i, sum, maxi = max(300, n); // up to 255 ASCII chars or length of n
    c.assign(maxi,0);
    for (i = 0; i < n; i++) // count the frequency of each integer rank
        c[i + k < n ? RA[i + k] : 0]++;
    for (i = sum = 0; i < maxi; i++) {
        int t = c[i]; c[i] = sum; sum += t; }
    for (i = 0; i < n; i++) // shuffle the suffix array if necessary
        tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
    for (i = 0; i < n; i++) // update the suffix array SA
        SA[i] = tempSA[i];
}

void constructSA() { // this version can go up to 100000 characters
    int n = SA_str.length()-1;
    RA.assign(n,0);
    tempRA.assign(n,0);
    SA.assign(n,0);
    tempSA.assign(n,0);
    int i, k, r;
    for (i = 0; i < n; i++) RA[i] = SA_str[i]; // initial rankings
    for (i = 0; i < n; i++) SA[i] = i; // initial SA: {0, 1, 2, ..., n-1}
    for (k = 1; k < n; k <<= 1) { // repeat sorting process log n times
        countingSort(k); // actually radix sort: sort based on the second item
        countingSort(0); // then (stable) sort based on the first item
        tempRA[SA[0]] = r = 0; // re-ranking; start from rank r = 0
        for (i = 1; i < n; i++) // compare adjacent suffixes
            tempRA[SA[i]] = // if same pair => same rank r; otherwise, increase r
                    (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
        for (i = 0; i < n; i++) // update the rank array RA
            RA[i] = tempRA[i];
        if (RA[SA[n-1]] == n-1) break; // nice optimization trick
    }
}

void computeLCP() {
    int i, L;
    n = SA_str.length()-1;
    Phi.assign(n,0);
    PLCP.assign(n,0);
    LCP.assign(n,0);
    Phi[SA[0]] = -1; // default value
    for (i = 1; i < n; i++) // compute Phi in O(n)
        Phi[SA[i]] = SA[i-1]; // remember which suffix is behind this suffix
    for (i = L = 0; i < n; i++) { // compute Permuted LCP in O(n)
        if (Phi[i] == -1) { PLCP[i] = 0; continue; } // special case
        while (SA_str[i + L] == SA_str[Phi[i] + L]) L++; // L increased max n times
        PLCP[i] = L;
        L = max(L-1, 0); // L decreased max n times
    }
    for (i = 0; i < n; i++) // compute LCP in O(n)
        LCP[i] = PLCP[SA[i]]; // put the permuted LCP to the correct position
}

string printString(int max, int index, string str)   {
    string to_print = "";
    while (max--)   {
        to_print += str[index];
        index++;
    }
    return to_print;
}

int main() {
    //ofstream out("strings.txt");
    string str1, str2, str;
    int isFirst=true;
    while (cin >> str1 >> str2) {
        string prev = "";
        if (!isFirst)   {
            string empty;
            getline(cin, empty);
            cout << endl;
        }
        isFirst=false;
        SA_str = str1 + "#" + str2 + "$";
        int end_of1 = str1.size();
        constructSA();
        computeLCP();
        vector<bool> isTwo;
        vector<bool> isDifferent;
        for (int i=0; i<SA.size(); i++) {
            if (SA[i] <= end_of1)   {
                isTwo.push_back(true);
            }
            else    {
                isTwo.push_back(false);
            }
        }
        isDifferent.push_back(false);
        for (int i=1; i<SA.size(); i++) {
            if (isTwo[i] != isTwo[i-1]) {
                isDifferent.push_back(true);
            }
            else    {
                isDifferent.push_back(false);
            }
        }
        /*for (int i=SA.size(); i>=1; i--) {
            if (isTwo[i-1] == true)    {
                isTwo[i] = true;
            }
        }*/
        int max = 0;
        for (int i=1; i<LCP.size(); i++)    {
            if (LCP[i] > max && isDifferent[i] == true)   {
                max = LCP[i];
            }
        }
        if (max > 0)    {
            for (int i=0; i<LCP.size(); i++)    {
                if (LCP[i] == max && isDifferent[i] == true)   {
                    string candidate = printString(max, SA[i], SA_str);
                    if (candidate != prev)  {
                        cout << candidate << endl;
                        prev = candidate;
                    }

                }
            }
        }
        else    {
            cout << "No common sequence." << endl;
        }
    }
    return 0;
}