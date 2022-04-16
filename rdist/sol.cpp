#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cassert>
#include <iomanip>
#include <map>

using namespace std;

const int MAXV = 3e8 + 2, INF = 1e9 + 107, MAXQ = 250007;
struct query_t { int t, x, y, ans; string dx, dy; } queries[MAXQ];
vector<int> vecX, vecY, endX, endY;
pair<int, int> minByX[MAXQ], minByY[MAXQ];
set<int> setX, setY;
bool inTree[MAXQ];

int minY[MAXQ << 2], minXY[MAXQ << 2];

void modify(int rt, int lo, int hi, int x, int vy) {
	if (x < vecX[lo] || x > vecX[hi]) return;
	if (lo == hi) {
		assert(vecX[lo] == x);
		minY[rt] = vy, minXY[rt] = endX[lo] + vy;
		return;
	}
	int md = (lo + hi) >> 1, lc = rt << 1, rc = lc | 1;
	modify(lc, lo, md, x, vy), modify(rc, md + 1, hi, x, vy);
	minY[rt] = min(minY[lc], minY[rc]);
	minXY[rt] = min(minXY[lc], minXY[rc]);
}

int find_first_below(int rt, int lo, int hi, int y) {
	if (lo == hi) return lo;
	int md = (lo + hi) >> 1, lc = rt << 1, rc = lc | 1;
	if (minY[lc] <= y) return find_first_below(lc, lo, md, y);
	return find_first_below(rc, md + 1, hi, y);
}

int get_min(int rt, int lo, int hi, int l, int r) {
	if (hi < l || r < lo) return INF;
	if (l <= lo && hi <= r) return minXY[rt];

	int md = (lo + hi) >> 1, lc = rt << 1, rc = lc | 1;
	int ret = INF;
	ret = min(ret, get_min(lc, lo, md, l, r));
	ret = min(ret, get_min(rc, md + 1, hi, l, r));
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int T, Q;
	cin >> T >> Q;
	bool nonEmpty = false;
	for (int i = 0; i < Q; ++i) {
		cin >> queries[i].t >> queries[i].x >> queries[i].y;
		if (queries[i].t == 2) cin >> queries[i].dx >> queries[i].dy;
		queries[i].x *= 2, queries[i].y *= 2;
		nonEmpty |= queries[i].t == 1;
	}
	if (not nonEmpty) {
		for (int i = 0; i < Q; ++i) puts("-1");
		return 0;
	}

	for (int d = 0; d < 4; ++d) {
		int maxx = 0;
		for (int i = 0; i < Q; ++i) maxx = max(maxx, queries[i].x);
		for (int i = 0; i < Q; ++i) {
			queries[i].x = maxx - queries[i].x;
			if (queries[i].t == 2) queries[i].dx[0] ^= ('<' ^ '>');

			swap(queries[i].x, queries[i].y);
			if (queries[i].t == 2) swap(queries[i].dx, queries[i].dy);
		}

		vecX.clear(), vecY.clear();
		for (int i = 0; i < Q; ++i) {
			if (queries[i].t == 1) {
				vecX.push_back(queries[i].x);
				vecY.push_back(queries[i].y);
			}
		}

		sort(vecX.begin(), vecX.end()), vecX.erase(unique(vecX.begin(), vecX.end()), vecX.end());
		sort(vecY.begin(), vecY.end()), vecY.erase(unique(vecY.begin(), vecY.end()), vecY.end());

		endX.assign(vecX.size(), INF), endY.assign(vecY.size(), INF);
		setX.clear(), setY.clear();
		setX.insert(INF), setY.insert(INF);
		for (int i = 0; i <= vecX.size(); ++i) minByX[i] = make_pair(INF, -1);
		for (int i = 0; i <= vecY.size(); ++i) minByY[i] = make_pair(INF, -1);
		for (int i = 0; i < Q; ++i) inTree[i] = 0;
		for (int i = 0; i < vecX.size() * 4 + 10; ++i) minY[i] = minXY[i] = INF;

		assert(not vecX.empty());

		vector<int> toChange;
		vector<pair<int, int>> changes;
		for (int i = 0; i < Q; ++i) {
			// cout << "i = " << i << endl;
			int x = queries[i].x, y = queries[i].y;
			if (queries[i].t == 1) {
				int ix = lower_bound(vecX.begin(), vecX.end(), x) - vecX.begin();
				int iy = lower_bound(vecY.begin(), vecY.end(), y) - vecY.begin();
				if (minByX[ix].first <= y && minByY[iy].first <= x) continue;

				toChange.clear();

				if (minByX[ix].second < 0) {
					auto it = setX.insert(x).first;
					endX[ix] = ((*it) + (*next(it))) / 2;
					if (it != setX.begin()) {
						int p = lower_bound(vecX.begin(), vecX.end(), *prev(it)) - vecX.begin();
						endX[p] = (x + vecX[p]) / 2;
						if (inTree[minByX[p].second]) toChange.push_back(minByX[p].second);
					}
					minByX[ix] = make_pair(y, i);
				} else if (minByX[ix].first > y) {
					if (inTree[minByX[ix].second]) toChange.push_back(minByX[ix].second);
					minByX[ix] = make_pair(y, i);
				}

				if (minByY[iy].second < 0) {
					auto it = setY.insert(y).first;
					endY[iy] = ((*it) + (*next(it))) / 2;
					if (it != setY.begin()) {
						int p = lower_bound(vecY.begin(), vecY.end(), *prev(it)) - vecY.begin();
						endY[p] = (y + vecY[p]) / 2;
						if (inTree[minByY[p].second]) toChange.push_back(minByY[p].second);
					}
					minByY[iy] = make_pair(x, i);
				} else if (minByY[iy].first > x){
					if (inTree[minByY[iy].second]) toChange.push_back(minByY[iy].second);
					minByY[iy] = make_pair(x, i);
				}

				toChange.push_back(i);
				changes.clear();

				for (int j : toChange) if (inTree[j]) {
					changes.emplace_back(queries[j].x, INF);
					inTree[j] = false;
				}

				for (int j : toChange) {
					int jx = lower_bound(vecX.begin(), vecX.end(), queries[j].x) - vecX.begin();
					int jy = lower_bound(vecY.begin(), vecY.end(), queries[j].y) - vecY.begin();
					if (not (minByX[jx].second == j and minByY[jy].second == j)) continue;
					inTree[j] = true;
					for (int k = int(changes.size()) - 1; true; --k) {
						if (k < 0) {
							changes.emplace_back(queries[j].x, endY[jy]);
							break;
						}
						if (changes[k].first == queries[j].x) {
							changes[k].second = endY[jy];
							break;
						}
					}
				}

				// for (auto [x, y] : changes) cout << "modify " << x << ' ' << y << endl;
				for (auto p : changes) modify(1, 0, vecX.size() - 1, p.first, p.second);
			} else if (queries[i].dx == "<=" && queries[i].dy == "<=") {
				if (setX.size() == 1) {
					queries[i].ans = -2;
					continue;
				}

				set<int>::iterator it_x, it_y;

				int ans = -2;

				if (endX[lower_bound(vecX.begin(), vecX.end(), *setX.begin()) - vecX.begin()] <= x) {
					for (it_x = prev(setX.lower_bound(x)); endX[lower_bound(vecX.begin(), vecX.end(), *it_x) - vecX.begin()] > x; --it_x);
					int lid = find_first_below(1, 0, vecX.size() - 1, y);
					int rid = lower_bound(vecX.begin(), vecX.end(), *it_x) - vecX.begin();
					// cout << vecX[lid] << ' ' << vecX[rid] << endl;
					assert(lid > rid || minByX[lid].first <= y && endX[rid] <= x);
					ans = max(ans, x + y - get_min(1, 0, vecX.size() - 1, lid, rid));
				}

				for (it_x = setX.lower_bound(x); it_x != setX.begin() && ((*prev(it_x)) + (*it_x)) / 2 > x; --it_x);
				// for (auto k : setX) cout << k << ' '; cout << "| " << *it_x << endl;
				for (assert(it_x != prev(setX.end())); ((*it_x) + (*next(it_x))) / 2 >= x; --it_x) {
					int ix = lower_bound(vecX.begin(), vecX.end(), *it_x) - vecX.begin();
					it_y = setY.find(minByX[ix].first);
					if (not (it_y != setY.begin() && ((*prev(it_y)) + (*it_y)) / 2 > y)) {
						ans = max(ans, y - min(((*it_y) + (*next(it_y))) / 2, y));
					}
					if (it_x == setX.begin()) break;
				}

				for (it_y = setY.lower_bound(y); it_y != setY.begin() && ((*prev(it_y)) + (*it_y)) / 2 > y; --it_y);
				for (assert(it_y != prev(setY.end())); ((*it_y) + (*next(it_y))) / 2 >= y; --it_y) {
					int iy = lower_bound(vecY.begin(), vecY.end(), *it_y) - vecY.begin();
					it_x = setX.find(minByY[iy].first);
					if (not (it_x != setX.begin() && ((*prev(it_x)) + (*it_x)) / 2 > x)) {
						ans = max(ans, x - min(((*it_x) + (*next(it_x))) / 2, x));
					}
					if (it_y == setY.begin()) break;
				}

				queries[i].ans = ans;
			}
		}
	}

	cout << fixed << setprecision(1);
	for (int i = 0; i < Q; ++i) {
		if (queries[i].t == 2) {
			cout << queries[i].ans * 0.5 << '\n';
		}
	}
}