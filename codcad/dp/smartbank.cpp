#include<bits/stdc++.h>
using namespace std;

vector<pair<int, vector<int> > > dp;

int main(){
    int s;
    cin >> s;
    d.resize(s+1);
    dp[0].first = 1;
    dp[s-1].first = 0;
    for(int i = 0; i < s; i++){
        dp[i].second.resize(6);
    }
    for(int i = 0; i < 6; i++){
        cin >> dp[0].second[i];
    }
    for(int i = 0; i <= s; i++){
        for(int j = 0; j < 6; j++){
            if(i+j+1 > s) break;
            if()
        }
    }
}