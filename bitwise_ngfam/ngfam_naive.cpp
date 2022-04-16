#include <bits/stdc++.h>

using namespace std;

const int MAX_VAL = 1<<14;
const int mod = 1e9 + 7;

void add(int &x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    const vector<int> EMPTY_VEC(MAX_VAL);
    
    vector<vector<int>> f(1, EMPTY_VEC);
    f[0][0] = 1; 

    int Q; cin >> Q;
    f.reserve(Q);

    while(Q--) {
        string query; cin >> query;

        if (query == "REMOVE") {
            f.pop_back();
        } else if (query == "QUERY") {
            int x; cin >> x;
            cout << f.back()[x] << "\n";
        } else {
            f.push_back(EMPTY_VEC);

            auto &src = f[f.size() - 2];
            auto &dst = f[f.size() - 1];

            int x; cin >> x;
            for(int i = 0; i < MAX_VAL; ++i) {
                add(dst[i], src[i]);
                if (query == "XOR") add(dst[i^x], src[i]);
                else if (query == "AND") add(dst[i&x], src[i]);
                else if (query == "OR") add(dst[i|x], src[i]);
            }
        }
    }

    return 0;
}