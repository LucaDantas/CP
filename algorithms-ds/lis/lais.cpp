#include<bits/stdc++.h>
using namespace std;

vector<int> v, pilha;

int main(){
	int n;
	cin >> n;
	v.resize(n);
	for(int i = 0; i < n; i++)
		cin >> v[i];
	for(int i = 0; i < n; i++){
		vector<int>::iterator it = upper_bound(pilha.begin(), pilha.end(), v[i]);
		if(it == pilha.end()) pilha.push_back(v[i]);
		else *it = v[i];
	}
	cout << pilha.size() << endl;
}
