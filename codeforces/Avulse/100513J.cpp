#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; } 
template<typename T, size_t N> ostream& operator<<(ostream &os, const array<T, N> &v) { os << '['; string sep = ""; for (int i = 0; i < N; i++) os << sep << v[i], sep = ", "; return os << ']'; }                                                                                                                       
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }                                                                                                                       
template<typename A> ostream& operator<<(ostream &os, const set<A> &s) { os << '{'; string sep = ""; for (const auto &x : s) os << sep << x, sep = ", "; return os << '}'; }                                                                                                                          
template<typename A, typename B> ostream& operator<<(ostream &os, const map<A, B> &m) { os << '{'; string sep = ""; for (const auto &x : m) os << sep << x.first << " -> " << x.second, sep = ", "; return os << '}'; }                                                                               
                                                                                                                                                   
#ifdef MY_DEBUG_FLAG                                                                                                                               
void debug() { cerr << endl; }                                                                                                                     
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << I; if(sizeof...(F)) cerr << ", "; debug(F...);}                      
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") == ", debug(__VA_ARGS__)                                                                   
#else                                                                                                                                              
#define db(...)                                                                                                                                    
#endif

#define sz(a) (int)(a.size())
#define all(a) a.begin(), a.end()

int main() {
    int n, s, t; scanf("%d %d %d", &n, &s, &t);

    vector<array<int,3>> ativos = {{s, 0, 0}}, prox;

    int now = 0;

    vector<int> p(n+1);

    auto upd = [&](int time) -> void {
        while(now < time) { // atualizo os valores quando anda o dia
            for(auto& [val, cansaco, id] : ativos)
                cansaco >>= 1;
            sort(all(prox));

            // db(ativos, prox);

            static vector<array<int,3>> aux; aux.clear();

            int ptr = 0;
            for(int i = 0; i < sz(ativos); i++) {
                for(; ptr < sz(prox) && prox[ptr][0] < ativos[i][0]; ptr++) {
                    while(sz(aux) && prox[ptr][1] <= aux.back()[1])
                        aux.pop_back();
                    aux.push_back(prox[ptr]);
                }
                while(sz(aux) && ativos[i][1] <= aux.back()[1])
                    aux.pop_back();
                aux.push_back(ativos[i]);
            }

            for(; ptr < sz(prox); ptr++) {
                while(sz(aux) && prox[ptr][1] <= aux.back()[1])
                    aux.pop_back();
                aux.push_back(prox[ptr]);
            }

            // db(aux);

            now++;

            ativos = aux;
            prox.clear();

            // db(ativos);
        }
    };

    for(int i = 1; i <= n; i++) {
        int d, l, r; scanf("%d %d %d", &d, &l, &r);

        upd(d);

        auto it = lower_bound(all(ativos), array<int,3>{l, 0, 0});
        if(it != ativos.end())
            prox.push_back({r - it->at(1), it->at(1) + t, i}), p[i] = it->at(2);
    }
    upd(now+1); // so pra mergear prox e ativos

    vector<int> ans;
    ans.push_back(ativos.back()[2]);
    while(ans.back())
        ans.push_back(p[ans.back()]);
    ans.pop_back();
    reverse(all(ans));

    printf("%d %d\n", ativos.back()[0], sz(ans));
    for(int x : ans)
        printf("%d ", x);
    puts("");
}
