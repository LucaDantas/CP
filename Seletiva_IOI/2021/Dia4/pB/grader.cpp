/*
Esse checker retorna a quantidade de subsequencias crescentes maximais,
além do tamanho maximo de uma subsequencia crescente
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

constexpr int max_n = 1'000'000;
constexpr int max_ans = 1'000'000;

void fail() {
    printf("sequência incorreta\n");
    exit(0);
}


bool is_perm(int n, vector<int> a) {
    sort(begin(a), end(a));
    for (int i = 0; i < n; i++) {
        if (a[i] != i+1) return false;
    }
    return true;
}
struct Node {
    int val = 0;
    int cnt = 0;

    Node& add(Node const& rhs) {
        if (val == rhs.val) {
            cnt += rhs.cnt;
        }
        else if (val < rhs.val) {
            *this = rhs;
        }
        return *this;
    }

    static Node join(Node const& lhs, Node const& rhs) {
        Node r = lhs;
        r.add(rhs);
        return r;
    }

};

struct Seg {

    int n;
    vector<Node> tree;

    Seg(int n_) : n(n_), tree(n*2+2) {}

    inline Node get(int l, int r) {
        Node ans{};
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l&1) ans.add(tree[l++]);
            if(r&1) ans.add(tree[--r]);
        }
        return ans;
    }

    inline void upd(int p, Node val) {
        for(tree[p += n] = val; p > 1; p >>= 1) {
            tree[p >> 1] = Node::join(tree[p], tree[p^1]);
        }
    }

};

pair<int,int> count(vector<int> const& a) {
    int n = a.size();
    Seg b{n};
    for (auto i : a) {
        auto [d, cnt] = b.get(1, i);
        auto [at_val, at_cnt] = b.get(i, i+1);

        if (d+1 > at_val) {
            if (cnt == 0) cnt = 1;

            b.upd(i, {d+1, cnt});
        }
        else if (d+1 == at_val) {
            b.upd(i, {at_val, at_cnt + cnt});
        }

        if (b.get(1, n+1).cnt > max_n) {
            fail();
        }
    }

    return pair<int,int> (b.get(1, n+1).val , b.get(1,n+1).cnt);
}


int main(int argc, char** argv) {
    int N;
    scanf("%d" , &N);

    if (N > max_ans or N <= 0) fail();

    vector<int> a(N);
    for (auto& i : a) {
        try {
            scanf( "%d" , &i);
        }
        catch (exception& e) {
            fail();
        }
    }

    if (!is_perm(N, a)) fail();
    pair<int,int> x = count(a);
    printf("%d sequencias crescentes de tamanho maximo, com tamanho maximo = %d\n" , x.second, x.first);
    return 0;
}