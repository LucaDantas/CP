#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define endl '\n'
#define ll long long
#define f first
#define s second
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define debug(x) cout << "DEBUG " << x << endl
#define debug2(x, y) cout << "DEBUG " << x << " " << y << endl
#define debug3(x, y, z) cout << "DEBUG " << x << " " << y << " " << z<< endl
#define debug4(x, y, z, o) cout << "DEBUG " << x << " " << y << " " << z<< " " << o << endl
#define max3(x, y, z) max(x, max(y, z))

const int maxn = 1e5 + 100;

int a[maxn];

vector<pair<int, int> > divisors;

int min_prime_fact[1010];
vector<int> pr; // list of prime numbers
pair<int, int> pai[1000100];

vector<vector<int> > g(1000100);

int visited[1000100]; // Vetor de visitados
int depth[1000100];	//Depth of the nodes from the starting one

void sieve(int n=1000){

    for(int i = 2; i <= n; ++i){
        if(min_prime_fact[i] == 0){ // prime!
            min_prime_fact[i] = i; // itself
            pr.push_back(i);
        }
        // for all primes less than or eq i, 
        //fill their product by i into min_prime_fact
        for(int j = 0; j < (int)pr.size(); j++){
            if(pr[j] > min_prime_fact[i]) break; //
            if(i * pr[j] > n) break; // out of range
            min_prime_fact[i * pr[j]] = pr[j];
        }
    }
}

int norm(int k){
	//cout << pr.size() << endl;
	for(auto i : pr){
		while(k % (i*i) == 0) k /= i*i;
	}
	return k;
}

pair<int, int> div(int k){
	int p1 = 1, p2 = 1;
	for(auto i : pr){
		if(k % i == 0) p1 = i;
		p2 = k/p1;
	}
	return make_pair(p1,p2);
}

//int bfs(int node){
	
//}

//bool isFather(int fat, int ps, pair<int, int> f){
	//if(ps != f.s) return false;
	//if(f.f == fat) return true;
	//return false;
//}
int pass = 0;

bool isFather(int v, int u){
	return pai[u].second == pass && pai[u].first == v;
}

int bfs(int u){
	pass++;
    queue<int> q; // Fila da BFS
    //int u = i; // Vertice current
    //int beg = u;
    depth[u] = 0;
    q.push(u); // Dou inicio a fila
    visited[u] = pass;
    //pai[u].s = pass;
    //pai[u].f = -1;
    

    while(!q.empty()){ // Enquanto nao estiver vazia
        u = q.front(); // Recuperando o proximo vertice
        //visited[u] = pass; // Marco-o como visitado
        q.pop(); // Retiro-o da fila

        for(int i = 0; i < (int)g[u].size(); i++){  // Para cada adjacente do vertice,
            if(visited[g[u][i]] != pass){   // Se nao foi visitado ainda,
                q.push(g[u][i]); // Visite
                visited[g[u][i]] = pass;
                depth[g[u][i]] = depth[u]+1;
                pai[g[u][i]].s = pass;
				pai[g[u][i]].f = u;
			}
            else if(!isFather(g[u][i], u)){
				//debug(pass);
				//cout << "KKK" << endl;
				return depth[u]+ depth[g[u][i]] +1;
			}
			//if(dist[v].second == pass && !isfather(v, u)){
				//return dist[v].first + dist[u].first + 1;
			//}
			//if(dist[v].second != pass && !isfather(v, u)){
				//pai[v].first = u;
				//pai[v].second = pass;
				//q.push(v);
				//dist[v].first = dist[u].first+1;
				//dist[v].second = pass;
			//}
		}
    }
	return -1;
}

int32_t main(){
	FAST;
	sieve();	
	int n;
	cin >> n;
	divisors.resize(n);
	for(int i = 0; i < n; i++)
		cin >> a[i];
	for(int i = 0; i < n; i++)
		a[i] = norm(a[i]);
	for(int i = 0; i < n; i++){
		if(a[i] == 1){
			//debug("oi");
			cout << 1 << endl;
			return 0;
		}
		//mx = max(mx, a[i]);
	}
	set<int> seen;
	for(int i = 0; i < n; i++){
		seen.insert(a[i]);
	}
	if((int)seen.size() != n){
		cout << 2 << endl;
		return 0;
	}
	//for(auto p : pr)
		//cout << p << ' ';
	for(int i = 0; i < n; i++)
		divisors[i] = div(a[i]);
	for(auto it : divisors){
		//for(auto k : g[it.f]){
			//if(k == it.s){
				//cout << 2 << endl;
				//return 0;
			//}
		//}
		g[it.f].pb(it.s);
		g[it.s].pb(it.f);
	}
	//for(int i = 0; i < n; i++)
		//cout << divisors[i].f << ' ' << divisors[i].s << endl;
	
	//for(auto it : divisors){
		//cout << it.f << ' ';
		//for(auto k : g[it.f])
			//cout << k << ' ';
		//cout << endl;
	//}
	int mincycle = INT_MAX;
	int ok = bfs(1);
	if(ok != -1)
		mincycle = min(mincycle, ok);
	//cout << ok << endl << endl;
	for(auto i : pr){
		ok = bfs(i);
		if(ok == -1) continue;
		mincycle = min(mincycle, ok);
	}
	if(mincycle == INT_MAX) cout << -1 << endl;
	else cout << mincycle << endl;
}
