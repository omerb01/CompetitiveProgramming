
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

bool main_comp(pair<string, int> comb1, pair<string, int> comb2)	{
	if (comb1.first.size() < comb2.first.size()) return true;
	else	{
		if (comb1.first.size() > comb2.first.size()) return false;
		else	{
			//sizes are equal
			if (comb1.first < comb2.first) return true;
			else	{
				if (comb1.first > comb2.first) return false;
				else	{
					//lexicographical equally
					return comb1.second < comb2.second;
				}
			}
		}
	}
}

int main() {
    vector<pair<string, int>> dict;
	int NumWords;
	string temp;
    cin >> NumWords;
    int i=1;
    while (i<=NumWords)	{
    	cin >> temp;
    	dict.push_back(make_pair(temp, i++));
    }
    sort(dict.begin(), dict.end(), main_comp);
    int test_cases;
    string sub_string;
    cin >> test_cases;
    while (test_cases--)	{
    	cin >> sub_string;
    	int word_count = 0;
    	vector<int> answer;
    	for (auto comb = dict.begin(); comb!=dict.end(); comb++)	{
    		//*comb
    		if (comb->first.find(sub_string) != std::string::npos)	{
    			answer.push_back(comb->second);
				word_count++;
    			if (word_count == 10) break;			//TOP10 achieved!
    		}
    	}
    	if (word_count)	{
    		for (int i=0; i<answer.size(); i++)	{
    			if (i>0)	{
    				cout << " ";
    			}
    			cout << answer[i];
    		}
    	}
    	else	{
    		cout << "-1";
    	}
    	cout << endl;
    }
    return 0;
}