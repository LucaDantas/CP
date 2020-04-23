#include<bits/stdc++.h>
using namespace std;
#define MAXN 100010
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(int i=(a); i < (b); i++) cout << v[i] << ' '

int bit[MAXN], a[MAXN];
int n;

void update(int x, int v){
	for (; x <= n; x += (x&-x))
        bit[x] += v;
}

int query(int x){
	int ans = 0;
	for (; x > 0; x -= (x&-x))
        ans += bit[x];
	return ans;
}

int main(){
	cin >> n;
	read(a, 1, n+1);
	for(int i = 1; i <= n; i++){
		update(i, a[i]);
	}
	for(int i = 1; i <= n; i++)
		cout << query(i) << ' ';
	cout << endl;
}
