#include <bits/stdc++.h>
using namespace std;

#define l first
#define r second

constexpr int maxn = 1e6+10;

string s;

vector<pair<int,int>> itv;

struct NodeAns {
    int l, r, sz;
};

NodeAns solve(int x) {
    if(itv[x].l == itv[x].r) return {1, 1, 1};
    auto itvL = solve(x+1), itvR = solve(upper_bound(itv.begin(), itv.end(), pair<int,int>(itv[x+1].r, 0x3f3f3f3f)) - itv.begin());
    if(s[itv[x].l-1] == 'x') // caso de max
    return {itvL.l + itvR.l, max(itvL.r + itvR.sz, itvL.sz + itvR.r), itvL.sz + itvR.sz};
    else // caso de min
    return {min(itvL.l, itvR.l), itvL.r + itvR.r - 1, itvL.sz + itvR.sz};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> s;
    vector<int> open;
    for(int i = 0; i < (int)s.size(); i++)
        if(s[i] == '(') open.push_back(i);
        else if(s[i] == ')') itv.push_back({open.back(), i}), open.pop_back();
        else if(s[i] == '?') itv.push_back({i, i}); // intervals with same beginning and end are question marks
    sort(itv.begin(), itv.end()); // sorts by the opening bracket
    auto [l, r, sz] = solve(0);
    printf("%d\n", r-l+1);
}
