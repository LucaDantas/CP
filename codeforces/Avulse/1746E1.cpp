#include <bits/stdc++.h>
using namespace std;

mt19937 rng(random_device{}());

int query(vector<int> v) {
    printf("? %ld", v.size());
    for(int x : v)
        printf(" %d", x);
    puts("");
    fflush(stdout);
    char s[5];
    scanf(" %s", s);
    return strcmp(s, "YES") == 0;
}

void db(vector<int> v) { printf("DEBUG VECTOR: "); for(int x : v) printf("%d ", x); puts(""); }

void answer(int x) { printf("! %d\n", x); fflush(stdout); char s[5]; scanf(" %s", s); if(strcmp(s, ":)") == 0) exit(0); }

int main() {
    int n; scanf("%d", &n);

    vector<int> ft(n), tf;
    vector<int> grp(n+1);
    iota(ft.begin(), ft.end(), 1);

    int queries = 0;
    while(ft.size() + tf.size() > 2) {
        assert(queries++ < 40);
        vector<int> qr[2]{}, total = tf;
        qr[0].clear(), qr[1].clear();
        for(int x : ft)
            total.push_back(x);
        
        shuffle(total.begin(), total.end(), rng);

        for(int i = 0; i < (int)total.size(); i++)
            grp[total[i]] = i&1;

        for(int i = 0; i < (int)total.size(); i++)
            qr[i&1].push_back(total[i]);
        
        int ans = query(qr[0]) | (query(qr[1]) << 1);

        if(ans == 1 || ans == 2) {
            ft.clear(), tf.clear();
            ft = qr[ans-1]; // his last answer was tt, therefore we can categorize it as ft
            continue;
        }

        ans >>= 1;
        
        vector<int> new_ft;

        tf = qr[!ans];
        for(int x : ft)
            if(grp[x] == ans)
                new_ft.push_back(x);
        ft = new_ft;
    }
    for(int x : ft)
        answer(x);
    for(int x : tf)
        answer(x);
}
