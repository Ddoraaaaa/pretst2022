#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 400005;
const int limit = 2e9;

struct Query {
	int type;
	int x, y;
	int d[2];
} query[N];

int n, q;
set<int> input[2];
vector<int> axesX;
set<int> axesY[N];
vector<ll> coor[2];
int bound[N][4];
pair<int, int> change[N][4];
map<int, int> curBound[4];
ll point[N][2][2][2];
int d[] = {1, -1};

struct IT {
	ll node[4 * N], value[4 * N];
	int signX, signY;
	void init(int u, int v) {
		signX = d[u];
		signY = d[v];
		for (int i = 0; i <= 4 * (n + 1); i++) {
			node[i] = value[i] = -1e18;
		}
	}
	void update(int id, int l, int r, int i, ll x) {
		if (l > i || r < i) return;
		if (l == r) {
			node[id] = signX * coor[0][i] + signY * x;
			value[id] = signY * x;
			return;
		}
		int mid = (l + r) >> 1;
		update(id << 1, l, mid, i, x);
		update(id << 1 | 1, mid + 1, r, i, x);
		node[id] = max(node[id << 1], node[id << 1 | 1]);
		value[id] = max(value[id << 1], value[id << 1 | 1]);
	}
	ll get(int id, int l, int r, int i, int j) {
		if (l > j || r < i || i > j) return -1e18;
		if (l >= i && r <= j) {
			return node[id];
		}
		int mid = (l + r) >> 1;
		return max(get(id << 1, l, mid, i, j), get(id << 1 | 1, mid + 1, r, i, j));
	}
	int findL(int id, int l, int r, ll x) {
		if (l == r) {
			return l;
		} else {
			int mid = (l + r) >> 1;
			if (value[id << 1] + -signY * x >= 0) {
				return findL(id << 1, l, mid, x);
			} else if (value[id << 1 | 1] + -signY * x >= 0) {
				return findL(id << 1 | 1, mid + 1, r, x);
			} else {
				return 1e9;
			}
		}
	}
	int findR(int id, int l, int r, ll x) {
		if (l == r) {
			return l;
		} else {
			int mid = (l + r) >> 1;
			if (value[id << 1 | 1] + -signY * x >= 0) {
				return findR(id << 1 | 1, mid + 1, r, x);
			} else if (value[id << 1] + -signY * x >= 0) {
				return findR(id << 1, l, mid, x);
			} else {
				return -1e9;
			}
		}
	}
} st[2][2];


int findId(int x, int dir) {
	return lower_bound(coor[dir].begin(), coor[dir].end(), x) - coor[dir].begin();
}

void ins(int dir, int x, int y, int u, int v) {
	point[x][dir][u][v] = y;
	point[y][dir ^ 1][v][u] = x;
	if (dir == 1) {
		swap(x, y);
		swap(u, v);
	}
	st[u][v].update(1, 0, n, x, coor[1][y]);
}

void del(int dir, int x, int y, int u, int v) {
	point[x][dir][u][v] = d[v ^ 1] * 1e18;
	point[y][dir ^ 1][v][u] = d[u ^ 1] * 1e18;
	if (dir == 1) {
		swap(x, y);
		swap(u, v);
	}
	st[u][v].update(1, 0, n, x, d[v ^ 1] * 1e18);
}

ll getAns(int x, int y, int dir, int dx, int dy) {
	int id = point[findId(x, dir)][dir][dx][dy];
	if (id >= 0 && id < coor[dir ^ 1].size()) {
		return d[dy ^ 1] * y + d[dy] * coor[dir ^ 1][id];
	} else {
		return -1e18;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
//	freopen("40.inp", "r", stdin);
//	freopen("40.out", "w", stdout);

	int subtask; cin >> subtask;
	cin >> q;
	for (int i = 1; i <= q; i++) {
		int type; cin >> type;
		if (type == 1) {
			int x, y; cin >> x >> y;
			query[i] = {type, x * 2, y * 2};
		} else {
			int x, y;; cin >> x >> y;
			string Dx; cin >> Dx;
			string Dy; cin >> Dy;
			query[i] = {type, x * 2, y * 2};
			query[i].d[0] = (Dx == "<=" ? 1 : 0);
			query[i].d[1] = (Dy == "<=" ? 1 : 0);
		}
	}

	for (int i = 1; i <= q; i++) {
		if (query[i].type == 1) {
			for (int j = 0; j < 4; j++) {
				change[i][j] = {-1, -1};
			}
			for (int j = 0; j <= 1; j++) {
				int val = (j == 0 ? query[i].x : query[i].y);
				if (input[j].find(val) == input[j].end()) {
					auto it = input[j].lower_bound(val);
					if (it != input[j].end()) {
						int tmp = (val + *it) / 2;
						curBound[1 + 2 * j][val] = tmp;
						change[i][0 + 2 * j] = {curBound[0 + 2 * j][*it], tmp};
						curBound[0 + 2 * j][*it] = tmp;
					} else {
						curBound[1 + 2 * j][val] = limit;
					}
					if (it != input[j].begin()) {
						it--; int tmp = (val + *it) / 2;
						curBound[0 + 2 * j][val] = tmp;
						change[i][1 + 2 * j] = {curBound[1 + 2 * j][*it], tmp};
						curBound[1 + 2 * j][*it] = tmp;
					} else {
						curBound[0 + 2 * j][val] = 0;
					}
					int tmp1 = curBound[0 + 2 * j][val];
					int tmp2 = curBound[1 + 2 * j][val];
					coor[j].push_back(tmp1);
					coor[j].push_back(tmp2);
					bound[i][0 + 2 * j] = tmp1;
					bound[i][1 + 2 * j] = tmp2;
					input[j].insert(val);
				} else {
					bound[i][0 + 2 * j] = curBound[0 + 2 * j][val];
					bound[i][1 + 2 * j] = curBound[1 + 2 * j][val];
				}
			}
		}
	}
	
	for (int i : input[0]) {
		axesX.push_back(i);
	}
	input[0].clear();
	
	for (int j = 0; j <= 1; j++) {
		sort(coor[j].begin(), coor[j].end());
		coor[j].erase(unique(coor[j].begin(), coor[j].end()), coor[j].end());
		for (int dir = 2 * j; dir <= 1 + 2 * j; dir++) {
			for (int i = 1; i <= q; i++) {
				if (change[i][dir].first != -1) {
					change[i][dir].first = findId(change[i][dir].first, j);
					change[i][dir].second = findId(change[i][dir].second, j);
				}
				bound[i][dir] = findId(bound[i][dir], j);
			}
		}
	}
 
	n = (int)coor[0].size() - 1;
	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= 1; j++) {
			st[i][j].init(i, j);
		}
	}
	for (int i = 0; i <= max((int)coor[0].size(), (int)coor[1].size()); i++) {
		for (int j = 0; j <= 1; j++) {
			for (int k = 0; k <= 1; k++) {
				point[i][0][j][k] = point[i][1][j][k] = d[k ^ 1] * 1e18;
			}
		}
	}

	set<int> cur[2];
	for (int i = 1; i <= q; i++) {
		if (query[i].type == 1) {
			input[0].insert(query[i].x);
			int id = lower_bound(axesX.begin(), axesX.end(), query[i].x) - axesX.begin();
			axesY[id].insert(query[i].y);
			for (int j = 0; j < 4; j++) {
				if (change[i][j].first != -1) {
					int dir = j / 2;
					int oldVal = change[i][j].first;
					int newVal = change[i][j].second;
					if (cur[dir].find(coor[dir][oldVal]) != cur[dir].end()) {
						cur[dir].erase(coor[dir][oldVal]);
					}
					cur[dir].insert(coor[dir][newVal]);
					int jj = (j >= 2 ? j - 2 : j);
					for (int k = 0; k <= 1; k++) {
						if (point[oldVal][dir][jj][k] != d[k ^ 1] * 1e18) {
							int other = point[oldVal][dir][jj][k];
							del(dir, oldVal, other, jj, k);
							ins(dir, newVal, other, jj, k);
						}
					}
				}
			}
			for (int j = 0; j < 4; j++) {
				cur[j / 2].insert(coor[j / 2][bound[i][j]]);
			}
			for (int j = 0; j <= 1; j++) {
				for (int k = 0; k <= 1; k++) {
					ll x = bound[i][j], y = bound[i][2 + k];
					ll Y = point[x][0][j][k];
					ll X = point[y][1][k][j];
					if (d[j] * x > d[j] * X && d[k] * y > d[k] * Y) {
						if (Y != d[k ^ 1] * 1e18) del(0, x, Y, j, k);
						if (X != d[j ^ 1] * 1e18) del(1, y, X, k, j);
						ins(0, x, y, j, k);
					}
				}
			}
		} else {
			ll ans = -2e18;
			int x = query[i].x, y = query[i].y;
			int dir[2], val[2];
			for (int j = 0; j <= 1; j++) {
				dir[j] = query[i].d[j];
			}
			val[0] = x; val[1] = y;
			for (int j = 0; j <= 1; j++) {
				if (dir[j] == 0) {
					auto it = cur[j].lower_bound(val[j]);
					if (it != cur[j].end() && *it == val[j]) {
						ans = max(ans, getAns(*it, val[j ^ 1], j, dir[j], dir[j ^ 1]));
					}
					if (it != cur[j].begin()) {
						it--;
						ans = max(ans, getAns(*it, val[j ^ 1], j, dir[j], dir[j ^ 1]));
					}
				} else {
					auto it = cur[j].lower_bound(val[j]);
					if (it != cur[j].end()) {
						ans = max(ans, getAns(*it, val[j ^ 1], j, dir[j], dir[j ^ 1]));
						if (*it == val[j]) {
							it++;
							if (it != cur[j].end()) {
								ans = max(ans, getAns(*it, val[j ^ 1], j, dir[j], dir[j ^ 1]));
							}
						}
					}
				}
			}
			int L, R;
			if (dir[0] == 0) {
				L = upper_bound(coor[0].begin(), coor[0].end(), x) - coor[0].begin();
				R = st[dir[0]][dir[1]].findR(1, 0, n, y);
			} else {
				L = st[dir[0]][dir[1]].findL(1, 0, n, y);
				R = lower_bound(coor[0].begin(), coor[0].end(), x) - coor[0].begin() - 1;
			}
			ans = max(ans, d[dir[0] ^ 1] * x + d[dir[1] ^ 1] * y + st[dir[0]][dir[1]].get(1, 0, n, L, R));
			
			if (ans > 0) {
				cout << fixed << setprecision(1) << (double)max(ans, 0LL) / 2.0 << "\n";
			} else {
				if ((int)cur[0].size() == 0 || (int)cur[1].size() == 0) {
					cout << -1 << "\n";
					continue;
				}
				int ok = 0;
				vector<pair<int, int>> seg[2];
				for (int j = 0; j <= 1; j++) {
					auto it = cur[j].lower_bound(val[j]);
					if (*it == val[j]) {
						auto it1 = it; it1++;
						if (it1 != cur[j].end()) {
							seg[j].push_back({*it, *it1});
						}
						it1 = it;
						if (it1 != cur[j].begin()) {
							it1--;
							seg[j].push_back({*it1, *it});
						}
					} else {
						auto it1 = it;
						if (it1 != cur[j].begin()) {
							it1--;
							seg[j].push_back({*it1, *it});
						}
					}
				} 
				for (auto j : seg[0]) {
					for (auto k : seg[1]) {
						int L = j.first, R = j.second;
						int D = k.first, U = k.second;
						auto it = input[0].lower_bound(L);
						if (it != input[0].end()) {
							int id = lower_bound(axesX.begin(), axesX.end(), *it) - axesX.begin();
							auto it1 = axesY[id].lower_bound(D);
							if (it1 != axesY[id].end()) {
								if (*it >= L && *it <= R && *it1 >= D && *it1 <= U) {
									ok = 1;
								}
							} 
						}
					}
				}
				if (ok == 1) {
					cout << "0.0\n";
				} else {
					cout << -1 << "\n";
				}
			}
		}
	}
}
