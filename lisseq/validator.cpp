#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
	
	int L=inf.readInt(1, 1000000000-100);
	inf.readSpace();
	inf.readInt(L+99, L+99);
	inf.readSpace();
	inf.readInt(100, 100);
	inf.readEof();
}
