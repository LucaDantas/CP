#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;

vector<ii> st;
vector<int> dp;

int main(){
    int n, p, siz = 0;
    cin >> n;
    while(n != 0){
        cin >> p;
        st.resize(n);
        for(int i = 0; i < n; i++){
            cin >> st[i].first >> st[i].second;
            siz += st[i].first;
        }
        dp.resize(p);
        fill(dp.begin() + 1, dp.end(), -1);
        dp[0] = 0;
        for(int i = 0; i < p; i++){
            if(dp[i] == -1) continue;
            for(ii itm : st){
                if(i+itm.second >= p) continue;
                dp[i+itm.second] = max(dp[i+itm.second], dp[i] + itm.first);
            }
        }
        cout << *max_element(dp.begin(), dp.end()) << " min." << endl;
        cin >> n;
    }
}