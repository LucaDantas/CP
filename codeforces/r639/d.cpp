#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(int i=(a); i < (b); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 1e3 + 100;

int n, m; 

//the idea of this question is to find the number of connected components of the grid that 
//can be represented as a graph, then we need no check if any of those components is not
//"convex", that follows the same definition as in polygons

bool cor[maxn][maxn];
int pai[maxn][maxn];
const pii nxt[] = {{1,0}, {0,1}, {-1,0}, {0,-1}};

void dfs(int fam, int i, int j){
	pai[i][j] = fam;
	for(auto it : nxt){
		int pi = i+it.ff;
		int pj = j+it.ss;
		if(pi < 0 || pj < 0 || pi > n || pj > n) continue; //check if it's inside the limits
		if(cor[pi][pj] && !pai[pi][pj]){ //if it is black and has no parent set
			dfs(fam, pi, pj);
		}
	}
}

bool check(void){
	bool seen[maxn], row = true, column = true;
	
	//check if there is an non-convex row
	for(int i = 0; i < n; i++){
		clr(seen, 0);
		int last = 0;
		for(int j = 0; j < m; j++){
			if(!cor[i][j] && last != 0){
				if(seen[last]) return false;
				seen[last] = 1;
				last = 0;
			}
			else last = pai[i][j];
		}
		if(seen[last]) return false;
	}
	
	//check if there is a non-convex column
	for(int j = 0; j < m; j++){
		clr(seen, 0);
		int last = 0;
		for(int i = 0; i < n; i++){
			if(!cor[i][j] && last != 0){
				if(seen[last]) return false;
				seen[last] = 1;
				last = 0;
			}
			else last = pai[i][j];
		}
		if(seen[last]) return false;
	}
	
	
	//check if there is at least one row all-white
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(cor[i][j]) row = false;
		}
		if(row) break;
	}
	
	//check if there is at least one column all-white
	for(int j = 0; j < m; j++){
		for(int i = 0; i < n; i++){
			if(cor[i][j]) column = false;
		}
		if(column) break;
	}
	if((row && !column) || (!row && column)) return false;	
	return true;
}

int main(void){
	FAST;
	cin >> n >> m;
	
	for(int i = 0; i < n; i++){
		string s; cin >> s;
		for(int j = 0; j < m; j++){
			if(s[j] == '#') cor[i][j] = 1;
		} 
	}
	
	//sets the family of each group
	int fam = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(cor[i][j] && !pai[i][j]){ //if it is black and has no parent set
				dfs(++fam, i, j);
			}
		}
	}
	
	//check if there's any concav connected component - valid rows/columns
	if(!check()) cout << "-1\n";
	else cout << fam << '\n';
}
