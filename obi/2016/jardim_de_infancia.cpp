#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int sq(int x) {
	return x*x;
}

// int sign(int x) {
// 	return (x < 0)? 1 : -1;
// }

struct Pt {
	int x, y;
	Pt(int _x, int _y) : x(_x), y(_y) {}
	Pt() {}
	Pt operator+(Pt a) {
		return Pt(x+a.x, y+a.y);
	}
	Pt operator-(Pt a) {
		return Pt(x-a.x, y-a.y);
	}
	int operator*(Pt a) { // dot -> cos(theta)
		return x * a.x + y * a.y;
	}
	int operator/(Pt a) { // cross -> sin(theta)
		return x * a.y - y * a.x;
	}
	int operator%(Pt a) { // return the square of the distance
		return sq(a.x - x) + sq(a.y - y);
	}
	bool operator==(Pt a) {
		return x == a.x && y == a.y;
	}
	bool operator!=(Pt a) {
		return x != a.x || y != a.y;
	}
	friend ostream& operator<<(ostream& os, const Pt& a) {
		return os << a.x << ' ' << a.y;
	}
} pt[8];

int main() {
	for(int i = 1; i <= 7; i++) {
		int x, y; scanf("%d %d", &x, &y);
		pt[i] = Pt(x, y);
	}
	bool ok = 1;
	if((pt[2] - pt[1])*(pt[3] - pt[1]) <= 0) ok = 0;
	
	if(pt[1]%pt[3] != pt[1]%pt[2]) ok = 0;
	
	if((pt[3] - pt[2])/(pt[4] - pt[2]) != 0) ok = 0;
	if((pt[3] - pt[2])/(pt[5] - pt[2]) != 0) ok = 0;
	
	if((pt[2] + pt[3]) != (pt[4] + pt[5])) ok = 0;
	
	if(pt[2]%pt[3] <= pt[4]%pt[5]) ok = 0;
	
	if((pt[3] - pt[4])*(pt[6] - pt[4]) != 0) ok = 0;
	if((pt[3] - pt[5])*(pt[7] - pt[5]) != 0) ok = 0;
	
	if(pt[4]%pt[6] != pt[5]%pt[7]) ok = 0;
	
	// if(sign((pt[3] - pt[2])/(pt[1] - pt[2])) == sign((pt[3] - pt[2])/(pt[6] - pt[2]))) ok = 0;
	if(1ll * ((pt[3] - pt[2])/(pt[1] - pt[2])) * ((pt[3] - pt[2])/(pt[6] - pt[2])) >= 0) ok = 0;

	puts(ok?"S":"N");
}