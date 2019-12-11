#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef pair<ii, int> iii;

vector<iii> traps(200010);
vector<int> soldiers(200010);
int m, n, k, t;

bool path(int mx, int minag){
  int last = 0;
  for(int i = 0; i<k; i++){
    mx -= (traps[i].first.first - last);
    last = traps[i].first.first;
    if(traps[i].second > minag) mx -= traps[i].first.second;
    if(mx < 0) return false;
  }
  return true;
}

int bsa(){
  int beg = 0, end = 2*100000, mid;
  int ans = -1;
  while(beg <= end){
    mid = beg + (end - beg)/2;

  }
}

int main(){
  int l, r, d;
  cin >> m >> n >> k >> t;
  for(int i = 0; i < m; i++) cin >> soldiers[i];
  for(int i = 0; i < k; i++){
    cin >> l >> r >> d;
    traps[i].first.first = l;
    traps[i].first.second = ((r - l) << 1) + 2;
    traps[i].second = d;
  }

}
