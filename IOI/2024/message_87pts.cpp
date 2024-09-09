/*
 * 87 points
 *
 * Using the bits trick from arquipelago to divide everyone into one of 16 groups with 4 queries
 * such that each good bit is in one group. Then use a single extra query
 * to decide who is the healthy one from each group and the last bit remaining
 * from this query to encode whether the message is a multiple of 16 or not
 * if it is not remove the last continuous subgroup of healthy bits of the message,
 * as they are encoded in this way alongside the is_full bit to indicate they are not
 * part of the message and should be ignored
 */

#include "message.h"
#include <bits/stdc++.h>
using namespace std;

array<vector<int>, 16> get_groups(vector<vector<bool>> responses) {
    vector<int> group_label(31);
    for(int message = 0; message < 4; message++)
        for(int i = 0; i < 31; i++)
            if(responses[message][i])
                group_label[i] |= 1 << message;

    array<vector<int>, 16> groups;
    for(int i = 0; i < 31; i++)
        groups[group_label[i]].push_back(i);

    return groups;
}

vector<int> get_initial_alive(array<vector<int>, 16> &groups) {
    vector<int> alive;

    // need to do an initial pass through to get the empty ones
    for(int i = 0; i < 16; i++) {
        if(groups[i].size() == 1) {
            // then this bit is certainly good
            alive.push_back(groups[i][0]);
        }
    }

    return alive;
}

// send single message to indicate which element is the active one of each group
vector<bool> encode_selection(array<vector<int>, 16> &groups, vector<bool> &C, bool is_full) {
    vector<int> alive = get_initial_alive(groups); // stores the current bits that were already deemed as active
    vector<bool> selection_packet(31);

    for(int i = 0; i < 16; i++) {
        if(groups[i].size() != 1) {
            int index_healthy = -1; // index of the healthy bit within the group

            for(int j = 0; j < (int)groups[i].size(); j++)
                if(!C[groups[i][j]])
                    index_healthy = j;

            assert(index_healthy != -1);

            for(int j = 1; j < (int)groups[i].size(); j++) {
                if(j == index_healthy)
                    selection_packet[alive.back()] = 1;
                alive.pop_back();
            }

            alive.push_back(groups[i][index_healthy]);
        }
    }

    selection_packet[alive.back()] = is_full;

    return selection_packet;
}

vector<int> decode_selection(array<vector<int>, 16> &groups, vector<bool> selection_message, bool &is_full) {
    vector<int> alive = get_initial_alive(groups);

    vector<int> healthy = alive;

    for(int i = 0; i < 16; i++) {
        if(groups[i].size() != 1) {

            int healthy_here = groups[i][0];
            for(int j = 1; j < (int)groups[i].size(); j++) {
                if(selection_message[alive.back()])
                    healthy_here = groups[i][j];
                alive.pop_back();
            }

            healthy.push_back(healthy_here);
            alive.push_back(healthy_here);
        }
    }

    sort(healthy.begin(), healthy.end());

    is_full = selection_message[alive.back()];

    return healthy;
}

void send_message(vector<bool> M, vector<bool> C) {
    vector<int> healthy;
    for(int i = 0; i < 31; i++)
        if(!C[i]) healthy.push_back(i);

    vector<vector<bool>> group_division_responses;

    // divides them into 16 groups such that each healthy bit is at most part of one group
    // and the corrupted bits are dispersed into some of those groups
    for(int message = 0; message < 4; message++) {
        vector<bool> packet(31, 0);
        for(int i = 0; i < 16; i++)
            packet[healthy[i]] = i & (1 << message);

        group_division_responses.push_back(send_packet(packet));
    }

    array<vector<int>, 16> groups = get_groups(group_division_responses);

    send_packet(encode_selection(groups, C, !(M.size() % 16)));

    for(int i = 0; i < M.size(); i += 16) {
        vector<bool> packet(31);
        int last = 0;
        for(int j = 0; j < 16; j++) {
            if(i+j < M.size()) {
                packet[healthy[j]] = M[i+j];
                last = M[i+j];
            } else {
                packet[healthy[j]] = !last;
            }
        }
        send_packet(packet);
    }
}

vector<bool> receive_message(vector<vector<bool>> R) {
    array<vector<int>,16> groups = get_groups(vector<vector<bool>>(R.begin(), R.begin()+4));

    vector<bool> selection_message = R[4];
    bool is_full = 0;
    vector<int> healthy = decode_selection(groups, selection_message, is_full);

    vector<bool> message;
    for(int i = 5; i < R.size(); i++) {
        for(int j = 0; j < 16; j++)
            message.push_back(R[i][healthy[j]]);
    }

    int last = 0, sz = 0;
    for(int j = 0; j < 16; j++)
        if(R.back()[healthy[j]] != last)
            last ^= 1, sz = 1;
        else
            sz++;

    while(!is_full && sz--)
        message.pop_back();
    return message;
}
