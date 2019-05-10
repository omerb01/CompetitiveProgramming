#include <iostream>
#include <vector>
#include <map>

using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

bool topological_sort(const vvi &g, vi &order) {
    // compute indegree of all nodes
    vi indegree(g.size(), 0);
    for (int v = 0; v < g.size(); v++) for (int u : g[v]) indegree[u]++;
    // order sources first
    order = vector<int>();
    for (int v = 0; v < g.size(); v++) if (indegree[v] == 0) order.push_back(v);
    // go over the ordered nodes and remove outgoing edges,
    // add new sources to the ordering
    for (int i = 0; i < order.size(); i++)
        for (int u : g[order[i]]) {
            indegree[u]--;
            if (indegree[u] == 0) order.push_back(u);
        }
    return order.size() == g.size();
}

bool insert_char(vector<char> &vec, char c) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == c) return false;
    }
    vec.push_back(c);
    return true;
}

int get_char_index(const vector<char> &vec, char c) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == c) return i;
    }
    return -1;
}

int main() {
    vector<string> words;
    string word;
    vector<char> chars;
    while (cin >> word) {
        if (word == "#") break;
        words.push_back(word);
        for (int i = 0; i < word.size(); ++i) insert_char(chars, word[i]);
    }

    vvi g(chars.size(), vi());
    for (int i = 0; i < words.size() - 1; ++i) {
        string word1 = words[i];
        string word2 = words[i + 1];
        int index = 0;
        while (index < word1.size() && index < word2.size() && word1[index] == word2[index]) index++;
        if (index >= word1.size() || index >= word2.size()) continue;
        g[get_char_index(chars, word1[index])].push_back(get_char_index(chars, word2[index]));
    }

    vi order;
    topological_sort(g, order);
    for (int i = 0; i < order.size(); ++i) {
        cout << chars[order[i]];
    }

    cout << endl;

    return 0;
}