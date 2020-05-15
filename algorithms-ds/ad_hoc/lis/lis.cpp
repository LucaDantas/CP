#include<bits/stdc++.h>
using namespace std;
#define pb push_back

vector<int> v, pilha, ans;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	v.resize(n);
	for(int i = 0; i < n; i++)
		cin >> v[i];
	for(int i = 0; i < n; i++){
		vector<int>::iterator it = lower_bound(pilha.begin(), pilha.end(), v[i]);
		if(it == pilha.end()){
			//if(!pilha.empty()) ans.pb(*(--pilha.end()));
			pilha.pb(v[i]);
			ans.pb(v[i]);
		}
		else
			*it = v[i];
	}	
	//if(!pilha.empty()) ans.pb(*(--pilha.end()));
	cout << pilha.size() << endl << endl;
	for(auto i : ans)
		cout << i << endl;
}
