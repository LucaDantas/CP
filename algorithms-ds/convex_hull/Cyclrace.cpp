#include<cstdio>
#include<set>

constexpr int maxn = 5e4+10;

struct Line
{
	long long a, b;
	Line(long long _a, long long _b) : a(_a), b(_b) {}
	Line() {}
	bool operator<(Line L) {
		if(a == L.a) return b<L.b;
		return a<L.a;
	}
} cyclist[maxn];

auto cmp = [](Line L, Line M) { 
	if(L.a == M.a) return L.b<M.b;
	return L.a<M.a;
};

std::set<Line, decltype(cmp)> hull(cmp);

long long val(Line L, long long x) {return L.a*x + L.b;}
long long intersect(Line L, Line M) {return (M.b-L.b)/(L.a-M.a);}

void insert(Line L) {
	auto it = hull.lower_bound(L);
	if(it == hull.end() || it == hull.begin() || ((*it).a != L.a
		&& intersect(L, *it)) > intersect(*it, *prev(it))) {
		it = hull.insert(L).first;

		while(it != hull.begin() && prev(it) != hull.begin() &&
			(*prev(it)).a == L.a) hull.erase(prev(it));
		
		while(it != hull.begin() && prev(it) != hull.begin() &&
			intersect(L, *prev(it)) < intersect(*prev(it), *prev(prev(it))))
				hull.erase(prev(it));

		while(next(it) != hull.end() && next(next(it)) != hull.end() &&
			intersect(L, *next(it)) > intersect(L, *next(next(it))))
				hull.erase(next(it));
	}
}

Line query(long long x) {
	while(hull.size() >= 2 && val(*hull.begin(), x) <=
	 	val(*next(hull.begin()), x))
			hull.erase(hull.begin());
	return *hull.begin();
}

int main() {
	int n, q; scanf("%d %d", &n, &q);
	hull.insert(Line(0, 0));
	while(q--) {
		int k; scanf("%d", &k);
		if(k == 1) {
			int t, id, sp; scanf("%d %d %d", &t, &id, &sp);
			long long pos = val(cyclist[id], t);
			cyclist[id] = Line(sp, pos - 1ll*sp*t);
			insert(cyclist[id]);
		} else {
			int t; scanf("%d", &t);
			printf("%lld\n", val(query(t), 1ll*t));
		}
	}
}