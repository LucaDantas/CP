#include "souvenirs.h"
#include <bits/stdc++.h>
using namespace std;

void buy_souvenirs(int N, long long P0) {
    vector<pair<vector<int>, long long>> queries(N);
    queries[0] = {{0}, P0};
    vector<long long> P(N); // if we know the value we assign it here, if we don't know it's 0
    P[0] = P0;
    vector<int> cnt(N); // how many times each item was queried

    vector<int> known_heads = {0};
    int discovered = N; // up until which point from the back we know the values of

    auto update_query = [&](int head) {
        assert(head < discovered);
        auto &[arr, sum] = queries[head];
        while(arr.back() >= discovered) {
            sum -= P[arr.back()];
            arr.pop_back();
            assert(arr.size() >= 1);
        }
    };

    auto get_query_value = [&](int head) {
        update_query(head);
        long long sum = queries[head].second;
        int sz = (int) queries[head].first.size();
        return (sum+sz-1) / sz - 1;
    };

    auto get_true_value = [&](int head) {
        update_query(head);
        return queries[head].second;
    };

    auto update_cnts = [&](vector<int> res) {
        for(int x : res)
            cnt[x]++;
    };

    while(discovered != 0) {
        int last_head = known_heads.back();
        // printf("last head %d\n", last_head);

        if(discovered == last_head+1) {
            P[last_head] = get_true_value(last_head); // just do the sum minus the values of all the others which we already know
            discovered--;
            known_heads.pop_back();
            continue;
        }

        long long query_value = get_query_value(last_head);
        // printf("query_value %d\n", query_value);
        pair<vector<int>, long long> res = transaction(query_value);
        update_cnts(res.first);
        int new_head = res.first.front();
        // printf("new head %d\n", new_head);
        assert(new_head < discovered);

        queries[new_head] = {res.first, query_value - res.second};
        known_heads.push_back(new_head);
    }

    for(int i = 0; i < N; i++)
        while(cnt[i] < i) {
            ++cnt[i];
            transaction(P[i]);
        }
}
