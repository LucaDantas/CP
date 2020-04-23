#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 100;
int bit[maxn], a[maxn], n;

void update(int x, int v){
	for(; x <= n; x += (x&-x))
		bit[x] += v;
}

int query(int x){
	int ans = 0;
	for(; x > 0; x -= (x&-x))
		ans += bit[x];
	return ans;
}

int main(){
	int q;
	cin >> n >> q;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		update(i, a[i]);
	}
	while(q-- > 0){
		int event, lvl, p;
		cin >> event;
		if(event==1){
			cin >> lvl;
			cout << query(lvl) << endl;
		}
		else{
			cin >> lvl >> p;
			int d = p - a[lvl];
			a[lvl] = p;
			update(lvl, d);
		}
	}
}
