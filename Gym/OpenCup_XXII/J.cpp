#include<bits/stdc++.h>
using namespace std;
const long long inf = (long long) 1e18 + 10;
const int inf1 = (int) 1e9 + 10;
#define int long long
#define dbl long double
#define endl '\n'
#define sc second
#define fr first
#define mp make_pair
#define pb push_back
#define all(x) x.begin(), x.end()
const int maxn = 22;

int n, k, a[maxn][maxn], n1;
vector<int> qtsm[maxn][maxn], qteq[maxn][maxn], qrysm[maxn][maxn], qryeq[maxn][maxn];

void sol1(int i, int j, int pfcur, int pfmn, int mss) {
    if(i+j-2 > n-1) return;
    if(i > n || j > n) return;
    pfcur+= a[i][j];
    pfmn = min(pfmn,pfcur);
    mss = max(mss, pfcur-pfmn);
    if(mss > k) return;

    if(i+j-2 == n-1) {
        //add this path
        // cout << " pf " << i << " " << j << " " << pfcur << " " << pfmn << " " << mss << endl;

        if(mss < k) {
            qtsm[i][j].pb(pfcur-pfmn);
        }
        else {
            qteq[i][j].pb(pfcur-pfmn);
        }
    }

    sol1(i+1,j,pfcur,pfmn,mss);
    sol1(i,j+1,pfcur,pfmn,mss);
}

void sol2(int i, int j, int sfcur, int sfmn, int mss) {
    if(n-i+n-j > n-1) return;
    if(i < 1 || j < 1) return;

    if(n-i+n-j == n-1) {
        if(mss < k) {
            qrysm[i][j].pb(sfcur-sfmn);
        }
        else {
            qryeq[i][j].pb(sfcur-sfmn);
        }
    }
    sfcur+= a[i][j];
    sfmn = min(sfmn,sfcur);
    mss = max(mss, sfcur-sfmn);
    if(mss > k) return;

    sol2(i-1,j,sfcur,sfmn,mss);
    sol2(i,j-1,sfcur,sfmn,mss);
}
int dp1[maxn][maxn][2],dp2[maxn][maxn][2];
void sol10(int i, int j, int foi) {
    if(i+j-2 > n-1) return;
    if(i > n || j > n) return;
    if(a[i][j] > k) return;
    if(a[i][j] == k) foi = 1;

    if(i+j-2 == n-1) {
        dp1[i][j][foi]++;
    }

    sol10(i+1,j,foi);
    sol10(i,j+1,foi);
}

void sol20(int i, int j, int foi) {
    if(n-i+n-j > n-1) return;
    if(i < 1 || j < 1) return;

    if(n-i+n-j == n-1) {
        dp2[i][j][foi]++;
    }

    if(a[i][j] > k) return;
    if(a[i][j] == k) foi = 1;
    sol20(i-1,j,foi);
    sol20(i,j-1,foi);
}

void solve() {
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    if(n == 1) {
        if(a[1][1] == k) cout << 1 << endl;
        else cout << 0 << endl;
        return;
    }

    if(k < 0) {
        sol10(1,1,0);
        sol20(n,n,0);
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(i+j-2 != n-1) continue;
                ans+= dp1[i][j][0]*dp2[i][j][1];
                ans+= dp1[i][j][1]*dp2[i][j][0];
                ans+= dp1[i][j][1]*dp2[i][j][1];
            }
        }
        cout << ans << endl;
        return;
    }

    sol1(1,1,0,0,0);
    sol2(n,n,0,0,0);

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(i+j-2 != n-1) continue;
            vector<int> cc; cc.pb(0);
            for(auto x : qtsm[i][j]) cc.pb(k-x);
            for(auto x : qteq[i][j]) cc.pb(k-x);
            for(auto x : qrysm[i][j]) cc.pb(x);
            for(auto x : qryeq[i][j]) cc.pb(x);
            sort(all(cc));
            cc.erase(unique(all(cc)),cc.end());
            vector<int> pfsm(cc.size()+2,0), pfeq(cc.size()+2,0);
            for(auto x : qrysm[i][j]) {
                x = upper_bound(all(cc),x)-cc.begin();
                pfsm[x]++;
            }
            for(auto x : qryeq[i][j]) {
                x = upper_bound(all(cc),x)-cc.begin();
                pfeq[x]++;
            }
            for(int i = 1; i < pfsm.size(); i++) {
                pfsm[i]+= pfsm[i-1];
                pfeq[i]+= pfeq[i-1];
            }

            for(auto x : qtsm[i][j]) {
                int l = 0; l = upper_bound(all(cc),l) - cc.begin();
                int r = k-x; r = upper_bound(all(cc),r) - cc.begin();
                ans+= pfeq[min((int) pfeq.size()-1,r)];
                if(l != 0) ans-= pfeq[min((int) pfeq.size()-1,l-1)];

                l = k-x; l = upper_bound(all(cc),l) - cc.begin();
                r = k-x; r = upper_bound(all(cc),r) - cc.begin();
                ans+= pfsm[min((int) pfsm.size()-1,r)];
                if(l != 0) ans-= pfsm[min((int) pfsm.size()-1,l-1)];
            }

            for(auto x : qteq[i][j]) {
                int l = 0; l = upper_bound(all(cc),l) - cc.begin();
                int r = k-x; r = upper_bound(all(cc),r) - cc.begin();
                ans+= pfeq[min((int) pfeq.size()-1,r)];
                if(l != 0) ans-= pfeq[min((int) pfeq.size()-1,l-1)];

                l = 0; l = upper_bound(all(cc),l) - cc.begin();
                r = k-x; r = upper_bound(all(cc),r) - cc.begin();
                ans+= pfsm[min((int) pfsm.size()-1,r)];
                if(l != 0) ans-= pfsm[min((int) pfsm.size()-1,l-1)];
            }
        }

    }
    cout << ans << endl;
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0);

    // freopen("in.in", "r", stdin);
    // freopen("out.out", "w", stdout);
    int tt = 1;
    // cin >> tt;
    while(tt--) {
        solve();
    }

}
