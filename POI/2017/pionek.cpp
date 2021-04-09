#include <cstdio>
#include <algorithm>

constexpr int maxn = 2e5+10;

struct Vector
{
	int x, y;
	Vector(int a = 0, int b = 0) : x(a), y(b) {}
	bool half() { return y < 0 || (y == 0 && x < 0); }
	long long operator%(Vector v) { return 1ll * x * v.y - 1ll * y * v.x; }
	long long operator*(Vector v) { return 1ll * x * v.x + 1ll * y * v.y; }
	Vector operator-(Vector v) { return Vector(x - v.x, y - v.y); }
	Vector operator+(Vector v) { return Vector(x + v.x, y + v.y); }
	void operator+=(Vector v) { x += v.x; y += v.y; }
	void operator-=(Vector v) { x -= v.x; y -= v.y; }
	bool operator<(Vector v) { 
		if(this->half() != v.half()) return this->half() < v.half();
		return (*this)%v > 0;
	}
	long long get() { return 1ll*x*x + 1ll*y*y; }
	bool operator==(Vector v) { return x == v.x && y == v.y; }
} vetores[maxn];

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		int x, y; scanf("%d %d", &x, &y);
		if(!x && !y) { --n, --i; continue; }
		vetores[i] = Vector(x, y);
	}
	std::sort(vetores, vetores+n);
	long long ans = 0;
	Vector now;
	for(int i = 0, ptr = 0; i < n; i++) {
		for(; (vetores[i]%vetores[ptr%n] > 0 || (vetores[i]%vetores[ptr%n]==0 && vetores[i].half() == vetores[ptr%n].half() && ptr < n)) && ptr - i < n; ++ptr)
			now += vetores[ptr%n], ans = std::max(ans, now.get());
		now -= vetores[i];
		ans = std::max(ans, now.get());
	}
	printf("%lld\n", ans);
}
