#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        string s;
        cin >> n >> s;
        map<pair<int,int>,int> vis;
        pair<int, int> cur = {0,0};
        vis[cur] = 0;
        int l = -1, r = n;
        for(int i = 0; i < n; i++){
            if(s[i] == 'L') cur.first--;
            if(s[i] == 'R') cur.first++;
            if(s[i] == 'U') cur.second++;
            if(s[i] == 'D') cur.second--;
            if(vis.count(cur)){
                if(i-vis[cur] < r-l){
                    r = i;
                    l = vis[cur];
                }
            }
            vis[cur] = i+1;
        }
        if(l == -1) cout << -1 << endl;
        else cout << l + 1 << ' ' << r + 1 << endl;
    }
    return 0;
}