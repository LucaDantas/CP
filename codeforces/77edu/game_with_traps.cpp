#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef pair<ii, int> iii;

vector<iii> traps(200010);
vector<int> soldiers(200010);
int m, n, k, t;

// bool path(int mx, int minag){
//   int last = 0;
//   for(int i = 0; i<k; i++){
//     mx -= (traps[i].first.first - last);
//     last = traps[i].first.first;
//     if(traps[i].second > minag) mx -= traps[i].first.second;
//     if(mx < 0) return false;
//   }
//   return true;
// }

int sorttraps(iii a, iii b){
  if(a.first.first > b.first.first) return 1;
  else return 0;
}

bool path(int price, int minag){
  int current = 0, i = 0, end;
  while(i < k){
    if(traps[i].second > minag){
      price -= traps[i].first.first - current - 1;
      current = traps[i].first.first - 1;
      end = traps[i].first.second;
      i++;
      while(i < k && traps[i].first.first <= end){
        if(traps[i].second > minag){
          end = max(end,traps[i].first.second);
        }
        i++;
      }
      price -= 2*(end-current);
    }
    else i++;
  }
  price -= n - current;
  if(price >= 0) return true;
  else return false;
}

int bsa(){
  sort(traps.begin(), traps.begin() + k, sorttraps);
  int beg = 0, end = 2*100000, mid;
  int ans = -1;
  while(beg <= end){
    mid = beg + (end - beg)/2;
    if(path(t, mid)){
      ans = mid;
      end = mid-1;
    }
    else beg = mid+1;
  }
  return ans;
}

void belongs(int mi){
  int hi = 0;
  for(int i = 0; i < m; i++){  
    if(soldiers[i] >= mi) hi++;
  }
  cout << hi << endl;
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
  int ans = bsa();
  if(ans == -1) cout << -1 << endl;
  else belongs(ans);
}
