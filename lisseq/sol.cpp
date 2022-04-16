#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> solve(int X, int N) {
	if (X <= N) {
		vector<int> ans;
		for (int i = 0; i < X; ++i) ans.push_back(X - 1 - i);
		for (int i = X; i < N; ++i) ans.push_back(i);
		return ans;
	}

	const double golden_ratio = (1 + sqrt(5)) / 2;

	// assert(X > 100);
	for (int abs_da = 0; abs_da < 10000; ++abs_da) for (int sgn = -1; sgn <= 1; sgn += 2) {
		int cnt = 0;
		int a = X / golden_ratio + abs_da * sgn, b = X - a;

		vector<pair<int, int>> vec;
		while (a != b) {
			if (a < b) swap(a, b);
			vec.emplace_back(a, b);
			a -= b;
		}
		if (a & (a - 1)) continue;
		if (a != 1) continue;

		vector<int> ans;
		for (int k = 0; a >> k; ++k) {
			ans.push_back(2 * k + 1);
			ans.push_back(2 * k);
		}

		int p_a = ans.size() - 2, p_b = ans.size() - 1;	

		reverse(vec.begin(), vec.end());
		for (auto i : vec) {
			int c=i.first, d=i.second;
			if (p_a > p_b) swap(a, b), swap(p_a, p_b);


			int n = ans.size();
			int p_c = -1, p_d = -1;
			ans.push_back(-1), ans.push_back(-1);
			if (d == a) {
				ans[n] = ans[n - 1];
				ans[n - 1] = n + 1;
				ans[n + 1] = n;
				p_c = n + 1, p_d = n - 1;
			} else {
				ans[n] = n + 1;
				ans[n + 1] = n - 1;
				ans[p_a] = n;
				p_c = n, p_d = n + 1;
			}
			p_a = p_c, a = c;
			p_b = p_d, b = d;
		}

		if (ans.size() > N) continue;
		for (int i = ans.size(); i < N; ++i) ans.push_back(i);
		return ans;
	}
}

int main() {
	int L, R, N;
	cin >> L >> R >> N;
	for (int i = L; i <= R; ++i) {
		auto vec = solve(i, N);
		for (int k : vec) cout << k << ' ';
		cout << endl;
	}
}