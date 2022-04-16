#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const int MAX_VAL = 1<<14;

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    registerGen(argc, argv, 1);

    int q = opt<int>("q");
    int remove = opt<int>("r");
    int seed = opt<int>("s");    
    int fixedType = opt<int>("t");
    
    assert(remove * 2 < q);
    int ask = rnd.next(1, q - remove*2);
    int add = q - ask - remove;
    
    cout << q << "\n";

    vector<pair<string,int>> addQueries;
    for(int i = 0; i < add; ++i) {
        int type = 1 + rnd.next(3);
        if (fixedType != 0) type = fixedType;
        int x = rnd.next(0, MAX_VAL-1);
        if (type == 1) addQueries.emplace_back("XOR", x);
        else if (type == 2) addQueries.emplace_back("AND", x);
        else addQueries.emplace_back("OR", x);
    }
    vector<int> posRemove(add);
    for(int i = 0; i < remove; ++i) {
        posRemove[rnd.next(i, add-1)]++;
    }

    vector<pair<string,int>> sequenceQuery;
    for(int i = 0; i < addQueries.size(); ++i) {
        sequenceQuery.emplace_back(addQueries[i]);
        while(posRemove[i]--) sequenceQuery.emplace_back("REMOVE", -1);
    }

    vector<int> posAsk(sequenceQuery.size());

    posAsk[add+remove-1]++;
    for(int i = 0; i < ask-1; ++i) {
        posAsk[rnd.next(0, add+remove-1)]++;
    }

    vector<pair<string,int>> finalQueries;
    for(int i = 0; i < sequenceQuery.size(); ++i) {
        finalQueries.push_back(sequenceQuery[i]);
        while(posAsk[i]--) {
            int x = rnd.next(0, MAX_VAL-1);
            finalQueries.emplace_back("QUERY", x);
        }
    }

    for(auto [s, v]: finalQueries) {
        if (s == "REMOVE") cout << s << "\n";
        else cout << s << " " << v << "\n";
    }

    return 0;
}