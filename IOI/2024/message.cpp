#include <bits/stdc++.h>
#include "message.h"
using namespace std;

void send_message(vector<bool> M, vector<bool> C) {
    vector<vector<bool>> bits_sent(66, vector<bool>(31));

    bool last = !M.back();
    while(M.size() < 1025)
        M.push_back(last);

    vector<int> dist_next(31);
    for(int i = 0; i < 31; i++) {
        if(C[i]) continue;
        dist_next[i] = 1;
        while(C[(i + dist_next[i]) % 31])
            ++dist_next[i];
    }

    int ptr = 0; // ptr to the position of the message being currently sent
    for(int i = 0; i < 31; i++) {
        if(C[i]) continue;
        bits_sent[dist_next[i]-1][i] = true;
        for(int j = dist_next[i]; j < 66 && ptr < 1025; j++, ptr++)
            bits_sent[j][i] = M[ptr];
    }

    for(int i = 0; i < 66; i++)
        send_packet(bits_sent[i]);
}

vector<int> getNextPointers(const vector<vector<bool>> &R) {
    vector<int> nxt(31); // position this index points to, used to find cycle

    for(int i = 0; i < 31; i++) {
        int dist = 0;
        while(!R[dist][i] && dist < 31)
            dist++;

        dist++; // the distance is 1 more than the index (0-indexed) of the first position that has 1

        if(dist < 31)
            nxt[i] = (i + dist) % 31;
        else
            nxt[i] = -1;
    }

    return nxt;
}

vector<int> getHealthyBits(vector<int> nxt) {
    // finds healthy bits by finding the cycle of size 16 on this functional graph

    vector<int> longest(31);

    int start; // first valid bit, find others from this one

    for(int i = 0; i < 31; i++) {
        if(nxt[i] == -1) continue;
        if(nxt[i] < i && longest[i] >= 15) {
            start = nxt[i];
            break;
        }

        longest[nxt[i]] = max(longest[nxt[i]], longest[i]+1);
    }

    vector<int> healthy = {start};
    while(healthy.size() < 16)
        healthy.push_back(nxt[healthy.back()]); // adds the index that the last healthy points to

    return healthy;
}

vector<bool> receive_message(vector<vector<bool>> R) {
    vector<int> healthy = getHealthyBits(getNextPointers(R));

    vector<bool> M;
    for(int x : healthy) {
        int first_active = 0;
        while(!R[first_active][x])
            first_active++;

        for(int i = first_active + 1; i < 66; i++)
            M.push_back(R[i][x]);
    }

    bool last = M.back();
    while(M.back() == last)
        M.pop_back();

    return M;
}
