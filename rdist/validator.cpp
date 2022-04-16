#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
	
	int Type=inf.readInt(1, 5);
	inf.readEoln();
	int Q=inf.readInt(1, 250000);
	inf.readEoln();
	for(int i=1; i<=Q; i++)
	{
		int type=inf.readInt(1, 2);
		inf.readSpace();
		inf.readInt(0, 1000000000);
		inf.readSpace();
		inf.readInt(0, 1000000000);
		if(type==2)
		{
		    inf.readSpace();
		    inf.readToken(">=|<=");
		    inf.readSpace();
		    inf.readToken(">=|<=");
		}
		inf.readEoln();
	}
	inf.readEof();
}
