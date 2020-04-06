#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define piii pair<int, pii>
#define MAXN 1e5 + 100
#define INF 1e9 + 100

vector<int> a;
set<int> ans;

bool check(int begin){
    set<int> seen;
    int m = 0, num = 0;
    while(++begin < a.size()){
        m = max(m, a[begin]);
        num++;
        if(seen.find(a[begin]) != seen.end()) return false;
        seen.insert(a[begin]);
    }
    if(num == m) return true;
    return false;
}

void find(int begin){
    set<int> seen;
    int m = begin, first = begin;
    while(++begin < a.size()){
        if(a[begin] <= first || seen.find(a[begin]) != seen.end()){
            break;
        }
        m = max(m, a[begin]);
        if(begin == m){
            if(check(begin)){
                ans.insert(begin);
            } 
            find(begin);
        }
        seen.insert(a[begin]);
    }
}

void solve(int n){
    a.resize(n+1);
    int mx = 0, num = 0;
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    find(0);
}

int main(){
    int t;
    scanf("%d", &t);
    for(int i = 0, n; i < t; i++){
        scanf("%d", &n);
        solve(n);
        printf("%d\n", (int)ans.size());
        for(auto it : ans){
            printf("%d %d\n", it, n-it);
        }
        ans.clear();
    }
    return 0;
}