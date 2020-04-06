#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define MAXN 1e5 + 100
#define INF 1e9 + 100

int solve(int n, int x){
    set<int> v;
    int act = 1;
    for(int i = 0, a; i < n; i++){
        scanf("%d", &a);
        v.insert(a);
    }
    for(auto it : v){
        // cout << it << endl;
        if(it == act){
            // cout << "YEY" << endl;
            act++;
            continue;
        }
        while(it != act){
            if(x > 0){
                x--;
                act++;
            }
            else{
                // cout << "OPA" << endl;
                return act-1;
            }
        }
        act++;
    }
    // cout << "OI" << endl;
    return act + x - 1;
}

int main(){
    int t;
    scanf("%d", &t);
    for(int i = 0, n, x; i < t; i++){
        scanf("%d%d", &n, &x);
        printf("%d\n",solve(n, x));
    }
    return 0;
}