/*
ID: luca1001
TASK: gift1
LANG: C++                 
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define f first
#define s second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

int main(){
	ofstream fout("gift1.out");
	ifstream fin ("gift1.in");
	int n;
	fin >> n;
	map<string, int> acc;
	vector<string> names(n);
	for(int i = 0; i < n; i++){
		fin >> names[i];
		acc[names[i]] = 0;
	}
	for(int i = 0, a, b; i < n; i++){
		string name;
		fin >> name;
		fin >> a >> b;
		if(b)
			acc[name] -= (a - a%b);
		for(int p = 0; p < b; p++){
			string rec;
			fin >> rec;
			acc[rec] += a/b;
		}
	}
	for(auto p : names)
		fout << p << ' ' << acc[p] << '\n';
	return 0;
}
