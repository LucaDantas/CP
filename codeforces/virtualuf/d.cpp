#include<bits/stdc++.h>
using namespace std;
const long long maxn = 2e5 + 100;
long long a[maxn], b[maxn];
vector<long long> s;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	long long n;
	cin >> n;
	for(long long i = 0; i < n; i++)
		cin >> a[i];
	for(long long i = 0; i < n; i++)
		cin >> b[i];
	for(long long i = 0; i < n; i++)
		s.push_back(a[i] - b[i]);
	sort(s.begin(), s.end(), greater<long long>());
	long long l = 0, r = n-1, ans = 0;
	while(l < r && s[l] > 0){
		if(s[l] + s[r] > 0){
			ans += r-l;
			l++;
		}
		else r--;
	}
	cout << ans << endl;
}
