#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

struct Event
{
	int x, y1, y2, t;
	bool operator<(Event a) { return x < a.x; }
} evt[2*maxn];

struct Comp {
    bool operator() (const Event& i, const Event& j) const {
        return i.y1 < j.y1;
    }
};

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		array<int,4> coord;
		for(int& x : coord)
			scanf("%d", &x);
		evt[2*i] = {coord[0], coord[3], coord[1], 0};
		evt[2*i+1] = {coord[2], coord[3], coord[1], 1};
	}
	sort(evt, evt+2*n);
	int ans = n;
	set<Event, Comp> st;
	st.insert(evt[0]);
	for(int i = 0; i < 2*n; i++) {
		auto it = st.upper_bound(evt[i]);
		int fim = -0x3f3f3f3f;
		if(it != st.begin())
			fim = (*(--it)).y2;
		if(fim >= evt[i].y2) st.erase(it);
		if(fim > evt[i].y2) --ans;
		if(!evt[i].t) st.insert(evt[i]);
	}
	printf("%d\n", ans);
}