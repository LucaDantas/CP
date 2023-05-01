#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> seg(4 * N);
vector<int> v;

int n;

void build(int l, int r, int k) {
    if (l == r) {
        seg[k] = v[l];
        return;
    }
    int mid = (l + r) / 2;

    build(l, mid, 2*k);
    build(mid+1, r, 2*k+1);

    seg[k] = min(seg[2*k], seg[2*k+1]);
    return;
}

int query(int l, int r, int ll, int rr, int k) {
    if (ll <= l && r <= rr) {
        return seg[k];
    }
    if (r < ll || rr < l) {
        return INT_MAX;
    }
    int mid = (l + r) / 2;
    int left = query(l, mid, ll, rr, 2*k);
    int right = query(mid + 1, r, ll, rr, 2*k+1);
    return min(left, right);
}


int findLeft(int pos) {
    int l = 0, r = pos;
    
    while (l < r) {
        int mid = (l + r) / 2;
        if (query(0, n - 1, mid, pos, 1) < v[pos]) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    return l;
}

int findRight(int pos) {
    int l = pos, r = n - 1;
    while(l < r) {
        int mid = (l + r + 1) / 2;
        if (query(0, n - 1, pos, mid, 1) < v[pos]) {
            r = mid - 1;
        } else {
            l = mid;
        }
    }
    return l;
}



int main() {
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    build(0, n-1, 1);

    long long l, r, ans = -1;

    for (int i = 0; i < n; i++) {
        int ll = findLeft(i);
        int rr = findRight(i);
        if (ans < 1ll* v[i] * (rr - ll + 1)) {
            ans = 1ll * v[i] * (rr - ll + 1);
            l = ll;
            r = rr;
        }
    }
    cout << l + 1 << ' ' << r + 1 << ' ' << ans << '\n';
}