#include<bits/stdc++.h>
using namespace std;

#define INF 1000100
#define endl '\n'

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int n, k, ans = INF;
	cin >> n >> k;
	int l=0, r=n-k-1;
	vector<int> pred(n);
	for(int i = 0; i < n; i++){
		cin >> pred[i];
	}
	sort(pred.begin(), pred.end());
	for(int i=0; i<=k; i++){
		ans = min(ans, pred[r+i] - pred[l+i]);
	}
	cout << ans << endl;
}
