/*
40 tests

Type
Q
1 x y
2 u v

subtask 1 (15%): Q<=500
subtask 2 (20%): all add queries comes before ask queries
subtask 3 (25%): Q<=5000
subtask 4 (40%): Q<=1e5
*/

#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int NumberOfTests=40, NumberOfSubtasks=4;
char TestName[]="./tests/test00.inp";
ofstream outp;
int  Subtasks[]=	{0,		15,		20,		25,		40		}, Deno=100;

int  MaxN[]=		{0,		500, 	100000,	5000,	100000 	};
int  MaxDifX[]=		{0,		500,	100000, 5000,	100000	};
bool Shuffle12[]=	{0, 	1, 		1, 		0, 		1,		};
bool Alldiff[]=		{0, 	1, 		1, 		1, 		1,		};

vector<int> GenCoords(int cnt, int cntdif)
{
	// cout<<cntdif<<endl;
	vector<int> possibleCoords, shift, res;
	{
		map<int, int> temp; temp.clear();
		while(temp.size()<cntdif)
		{
			temp[rnd.next(1000000000)]=1;
		}
		// cout<<temp.size()<<" "<<cntdif<<" "<<rnd.next(1000000000)<<endl;
		for(auto i:temp)
		{
			possibleCoords.push_back(i.first);
		}
		for(int i=1; i<=cntdif; i++) shift.push_back(1);
		for(int i=1; i<=cnt-cntdif; i++) shift.push_back(0);
		shuffle(shift.begin(), shift.end());
	}
	for(int i=0; i<cnt; i++)
	{
		res.push_back(possibleCoords.back());
		if(shift[i]) possibleCoords.pop_back();
	}
	shuffle(res.begin(), res.end());
	return res;
}

void Gen(int pos, int Subtask, int maxN, int maxdifX, bool shuffle12, bool alldiff)
{
	outp<<Subtask<<endl;
    // cout<<pos<<endl;

	//Gen number of queries Q, Q1, Q2
	int Q=rnd.wnext(maxN, pos*pos)+1;
	if(pos*2>Subtasks[Subtask]) Q=maxN;
	int Q1=rnd.next(Q)+1, Q2=Q-Q1;

	outp<<Q<<endl;

	// cout<<Q<<endl;
	//Gen all x coordinates
	int cntdifX=rnd.wnext(min(Q, maxdifX), log2(Subtasks[Subtask]*2-pos))+1;
	if(alldiff) cntdifX=Q;
	vector<int> coordX=GenCoords(Q, cntdifX);

	//Gen all y coordinates
	int cntdifY=rnd.wnext(Q, log2(Subtasks[Subtask]*2-pos))+1;
	if(alldiff) cntdifY=Q;
	vector<int> coordY=GenCoords(Q, cntdifY);

	//Gen types of coordinates
	vector<int> types;
	int cnttype1=rnd.next(Q), cnttype2=Q-cnttype1;
	for(int i=1; i<=cnttype1; i++) types.push_back(1);
	for(int i=1; i<=cnttype2; i++) types.push_back(2);
	if(shuffle12) shuffle(types.begin(), types.end());

	//Output queries

	for(int i=0; i<Q; i++)
	{
		outp<<types[i]<<" "<<coordX[i]<<" "<<coordY[i]<<endl;
	}
}

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    for(int i=1; i<=NumberOfSubtasks; i++) Subtasks[i]=NumberOfTests*Subtasks[i]/Deno;

    int CurTest=0;
    for(int Subtask=1; Subtask<=NumberOfSubtasks; Subtask++)
    {
    	for(int test=1; test<=Subtasks[Subtask]; test++, CurTest++)
    	{
    		// cout<<CurTest<<" "<<Subtasks[Subtask]<<endl;
    		TestName[12]=CurTest/10+'0', TestName[13]=CurTest%10+'0';
    		outp.open(TestName);
    		Gen(test, Subtask, MaxN[Subtask], MaxDifX[Subtask], Shuffle12[Subtask], Alldiff[Subtask]);
    		outp.close();
    		// cout<<CurTest<<" "<<Subtasks[Subtask]<<endl;
    	}
    }

    return 0;
}