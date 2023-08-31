
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

// const int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};
// ll is kinda op pog use it ALWAYS
#define PI 3.1415926535897932384626433832795

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin.exceptions(cin.failbit);
	cout.precision(10);

	while (true) {
		double r;
		double m, c;
		cin >> r >> m >> c;
		if (r == 0 && m == 0 && c == 0) break;

		// r is radius
		// m is total points
		// c is points in the circle
		double trueArea = PI * r * r;

		double calculatedArea = c / m * (2*r * 2*r); // ratio * square size

		cout << trueArea << " " << calculatedArea << '\n';

	}
	
}