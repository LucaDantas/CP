/*
ID: luca1001
TASK: friday
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

bool is_leap(int n){
	if(n % 4 == 0 && (n % 400 == 0 || n % 100 != 0)) return true;
	return false;
}

int main(){
	ofstream fout("friday.out");
	ifstream fin ("friday.in");
	int n; fin >> n;
	vi days(7);
	int now = 5;
	vi month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	for(int ano = 1900; ano < 1900+n; ano++){
		for(int mes = 0; mes < 12; mes++){
			days[now]++;
			now = (now+month[mes])%7;
			if(mes == 1 && is_leap(ano)) now = (now+1)%7;
		}
	}
	fout << days[5];
	for(int i = 6; i < 5+7; i++)
		fout << ' ' << days[i%7];
	fout << endl;
	return 0;
}
