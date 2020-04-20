#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair
#define f first
#define s second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define max3(x, y, z) max(x, max(y, z))
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<


const int ten_9 = (int)1e9;
const pii pos[] = { mp(0,0), mp((int)5e8, (int)5e8), mp((int)-5e8, (int)5e8), mp((int)5e8, (int)-5e8), mp((int)-5e8, (int)-5e8) };
const string gud = "HIT", fim = "CENTER", bad = "MISS";

string query(int x, int y){
	cout << x _ y << endl;
	string rid;
	cin >> rid;
	return rid;
}

int rand(int a, int b){
	return a + rand()%(b-a+1);
}

int32_t main(){
	FAST;
	int t, a, b;
	cin >> t >> a >> b;
	rep(tt, 1, t+1){
		string resp = "MISS";
		int guessx = 0;
		int guessy = 0;
		//while(resp[0] == 'M'){
			//guessx = rand(-ten_9, ten_9);
			//guessy = rand(-ten_9, ten_9);
			//resp = query(guessx, guessy);
		//}
		//if(resp[0] == 'C'){
			//continue;
		//}
		
		rep(i, 0, 5){
			resp = query(pos[i].f, pos[i].s);
			if(resp[0] == 'C') break;
			if(resp[0] == 'H'){
				guessx = pos[i].f;
				guessy = pos[i].s;
				break;
			}
		}
		if(resp[0] == 'C') continue;
		
		//Right border
		int l = guessx, r = ten_9, ans = 0;
		while(l <= r){
			int mid = l + ((r-l)>>1);
			string ret = query(mid, guessy);
			if(ret == fim) continue;
			if(ret == gud){
				ans = mid;
				l = mid+1;
			}
			else
				r = mid-1;
		}
		int right = ans;
		
		//Left border
		l = -ten_9, r = guessx;
		while(l <= r){
			int mid = l + ((r-l)>>1);
			string ret = query(mid, guessy);
			if(ret == fim) continue;
			if(ret == gud){
				ans = mid;
				r = mid-1;
			}
			else
				l = mid+1;
		}
		int left = ans;
		
		//Top border
		l = guessy, r = ten_9;
		while(l <= r){
			int mid = l + ((r-l)>>1);
			string ret = query(guessx, mid);
			if(ret == fim) continue;
			if(ret == gud){
				ans = mid;
				l = mid+1;
			}
			else
				r = mid-1;
		}
		int up = ans;
		
		//Bottom border
		l = -ten_9, r = guessy;
		while(l <= r){
			int mid = l + ((r-l)>>1);
			string ret = query(guessx, mid);
			if(ret == fim) continue;
			if(ret == gud){
				ans = mid;
				r = mid-1;
			}
			else
				l = mid+1;
		}
		int down = ans;
		
		int cx = left + ((right-left)>>1);
		int cy = down + ((up-down)>>1);
		
		query(cx, cy);
	}
}
