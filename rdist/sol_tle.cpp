#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int T, Q; cin >> T >> Q;
	vector<pair<int, int>> P;
	int maxx = 0, maxy = 0;
	while (Q--) {
		int t, x, y;
		cin >> t >> x >> y;
		x *= 2, y *= 2;

		maxx = max(maxx, x), maxy = max(maxy, y);

		if (t == 1) P.emplace_back(x, y);
		else {
			string dx, dy;
			cin >> dx >> dy;

			int lx, rx, ly, ry;
			if (dx == "<=") lx = 0, rx = x;
			else lx = x, rx = maxx;
			if (dy == "<=") ly = 0, ry = y;
			else ly = y, ry = maxy;

			int ans = -2;
			for (int i = 0; i < P.size(); ++i) {
				int d = 1e9;
				for (int u = lx; u <= rx; ++u) {
					for (int v = ly; v <= ry; ++v) {
						bool ok = 1;
						for (int j = 0; j < P.size() && ok; ++j) {
							if (abs(u - P[j].first) < abs(u - P[i].first)) ok = 0;
							if (abs(v - P[j].second) < abs(v - P[i].second)) ok = 0;
						}
						if (ok) d = min(d, abs(u - x) + abs(v - y));
					}
				}
				// cout << x << ' ' << y << ": " << i << ' ' << d << endl;
				if (d < 1e9) ans = max(ans, d);
			}
			cout << ans * 0.5 << endl;
		}
	}
}