#include<bits/stdc++.h>

using namespace std;

vector<int> arr;

int main(){
    int t, n;
    cin >> t;
    while(t-- > 0){
        int mindist = 1000000;
        cin >> n;
        arr.resize(n);
        for(int i = 0; i < n; i++){
            cin >> arr[i];
        }
        vector<int>::iterator head = arr.begin(), tail = arr.begin();
        while(++tail < arr.end()){
            vector<int>::iterator it = find(head, tail, *(tail));
            if(it != arr.end()){
                int dist = tail - it;
                if(mindist > dist) mindist = dist+1;
                head = it;
            }
        }
        cout << mindist;
    }
}