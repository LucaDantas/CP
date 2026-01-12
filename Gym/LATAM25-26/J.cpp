#include <bits/stdc++.h>
using namespace std;

const string a = "ha", b = "boooo", c = "bravo";

bool equal(const string& s, const string& p, int idx) {
    if(idx + p.size() > s.size())
        return false;
    for(int i = 0; i < p.size(); i++)
        if(s[idx + i] != p[i]) return false;
    return true;
}

int main() {
    string s; cin >> s;
    int score = 0;
    for(int i = 0; i < s.size(); i++)
        score += equal(s, a, i) - equal(s, b, i) + 3*equal(s, c, i);
    printf("%d\n", score);
}
