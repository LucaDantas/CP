#include "longesttrip.h"
#include <bits/stdc++.h>
using namespace std; 

mt19937 rng(random_device{}());

int get(vector<int> a, const vector<int>& b) {
    if(a.size() == 1) return a.back();
    vector<int> a2;
    while(a.size() > a2.size())
        a2.push_back(a.back()), a.pop_back();
    reverse(a2.begin(), a2.end());
    if(are_connected(a, b))
        return get(a, b);
    return get(a2, b);
}

void ajusta(vector<int>& a, int a1) {
    vector<int> aux;
    while(a.back() != a1) {
        aux.push_back(a.back());
        a.pop_back();
    }
    reverse(aux.begin(), aux.end());
    for(int x : a)
        aux.push_back(x);
    a = aux;
}

vector<int> longest_trip(int N, int D)
{
    vector<int> perm(N); iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end(), rng);
    vector<int> a = { perm.back() }; perm.pop_back();
    vector<int> b;
    bool topos_disconexos = 1;
    while(perm.size()) {
        int x = perm.back();
        perm.pop_back();

        if(are_connected({x}, {a.back()})) {
            a.push_back(x);
            topos_disconexos = b.size() == 0;
        } else if(topos_disconexos) {
            b.push_back(x);
        } else {
            if(are_connected({x}, {b.back()})) {
                b.push_back(x);
                topos_disconexos = 1;
            } else {
                reverse(b.begin(), b.end());
                for(int k : b)
                    a.push_back(k);
                if(b.size() == 1)
                    topos_disconexos = 1;
                b.clear();
                b.push_back(x);
            }
        }
    }

    if(!b.size()) return a;

    for(int i = 0; i < 2; i++, reverse(a.begin(), a.end())) {
        for(int j = 0; j < 2; j++, reverse(b.begin(), b.end())) {
            if(are_connected({a.back()}, {b.front()})) {
                for(int x : b)
                    a.push_back(x);
                return a;
            }
        }
    }

    if(!are_connected(a, b))
        return a.size() > b.size() ? a : b;

    int a1 = get(a, b);
    int b1 = get(b, {a1});

    ajusta(a, a1);
    ajusta(b, b1);

    reverse(b.begin(), b.end());
    
    for(int x : b)
        a.push_back(x);
    b.clear();

    return a;
}
