#include <cstdio>
#include <cstring>
#include <algorithm>

constexpr int maxn = 4e5+10, inf = 0x3f3f3f3f;

int min(int a, int b) { return a < b ? a : b; }
void min_self(int& a, int b) { a = a < b ? a : b; }

char* s[maxn];
char aux[maxn];
int a, b, t = 1;

struct Node {
	int filho[26], val, pai, vis;
	Node() : val(inf), pai(0), vis(0) { memset(filho, 0, sizeof filho); }
} trie[maxn<<1];

int insert(int id, int depth, int& hm, int sz) {
	if(depth == sz) return (hm = id, trie[t].val);

	++trie[id].vis;

	if(!trie[id].filho[ aux[depth]-'a' ]) {
		trie[id].filho[ aux[depth]-'a' ] = ++t;
		trie[t].pai = id;
		trie[t].val = trie[id].val + a;
	}

	int opa = insert(trie[id].filho[ aux[depth]-'a' ], depth+1, hm, sz);

	return min(opa, trie[id].val + trie[id].vis * b);
}

void upd(int id, int depth) {
	if(!depth) return;
	min_self(trie[trie[id].pai].val, trie[id].val + a);
	upd(trie[id].pai, depth-1);
}

int get(int id, int depth, int sz) {
	if(depth == sz) return trie[id].val;

	if(!trie[id].filho[ aux[depth]-'a' ]) {
		trie[id].filho[ aux[depth]-'a' ] = ++t;
		trie[t].pai = id;
		trie[t].val = trie[id].val + a;
	}

	return get(trie[id].filho[ aux[depth]-'a' ], depth+1, sz);
}

int main() {
	trie[1].val = 0;

	int n; scanf("%d %d %d", &n, &a, &b);
	for(int i = 0; i < n; i++) {
		scanf(" %s", aux);

		s[i] = new char[strlen(aux)+1];
		strcpy(s[i], aux);
	}

	std::sort(s, s+n, [](const char* A, const char* B) { return strcmp(A, B) < 0; });

	for(int i = 0; i < n; i++) {
		strcpy(aux, s[i]);

		int id = 0, val = insert(1, 0, id, (int)(strlen(aux)));

		trie[id].val = val;

		upd(id, (int)(strlen(aux)));
	}

	int q; scanf("%d", &q);
	while(q--) {
		scanf(" %s", aux);
		printf("%d\n", get(1, 0, (int)strlen(aux)));
	}
}
