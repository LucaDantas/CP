#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
#define pii pair<int, int>

const int maxn = 1e5 + 100;
const ll INF = LONG_LONG_MAX;

int a[maxn], b[maxn], c[maxn];

ll dif(int va, int vb){
	ll p = va-vb;
	return p*p;
}

ll val(int va, int vb, int vc){
	ll ret = dif(va,vb) + dif(va,vc) + dif(vb,vc);
	return ret;
}

void solve(){
	int na,nb,nc;
	cin >> na >> nb >> nc;
	for(int i = 0; i < na; i++)
		cin >> a[i];
	for(int i = 0; i < nb; i++)
		cin >> b[i];
	for(int i = 0; i < nc; i++)
		cin >> c[i];
	sort(a, a+na);
	sort(b, b+nb);
	sort(c, c+nc);
	//i points to a, j points to b, k points to c
	int i = 0, j = 0, k = 0;
	ll ans = INF;
	while(true){
		if(i == na-1 && j == nb-1 && k == nc-1){
			ans = min(ans, val(a[i], b[j], c[k]));
			break;
		}
		else if(i == na-1 && j == nb-1){
			ans = min(ans, val(a[i], b[j], c[k]));
			k++;
		}
		else if(i == na-1 && k == nc-1){
			ans = min(ans, val(a[i], b[j], c[k]));
			j++;
		}
		else if(j == nb-1 && k == nc-1){
			ans = min(ans, val(a[i], b[j], c[k]));
			i++;
		}
		else if(i == na-1){
			ans = min(ans, val(a[i], b[j], c[k]));
			if(b[j] < c[k]) j++;
			else k++;
		}
		else if(j == nb-1){
			ans = min(ans, val(a[i], b[j], c[k]));
			if(a[i] < c[k]) i++;
			else k++;
		}
		else if(k == nc-1){
			ans = min(ans, val(a[i], b[j], c[k]));
			if(b[j] < a[i]) j++;
			else i++;
		}
		else{
			ans = min(ans, val(a[i], b[j], c[k]));
			if(a[i] < b[j] && a[i] < c[k]) i++;
			else if(b[j] < a[i] && b[j] < c[k]) j++;
			else k++;
		}
	}
	cout << ans << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin >> t;
	while(t--) solve();
}
