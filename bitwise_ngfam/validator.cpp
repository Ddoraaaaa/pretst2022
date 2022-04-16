#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_VAL = (1<<14);

    int Q = inf.readInt(1, 10000, "Q");
    inf.readEoln();

    int cnt = 0;

    for(int i = 0; i < Q; ++i) {
        string type = inf.readWord();
        bool validType = (type == "AND" || type == "OR" || type == "XOR" || type == "REMOVE" || type == "QUERY");
        ensuref(validType, "Not valid query type", i+1);
        if (type != "REMOVE") {
            inf.readSpace();
            int x = inf.readInt(0, MAX_VAL-1, "x");
            cnt++;
        } else {
            cnt--;
            ensuref(cnt >= 0, "More removes than added", i+1);
        }
        inf.readEoln();
    }

    inf.readEof();

    return 0;
}