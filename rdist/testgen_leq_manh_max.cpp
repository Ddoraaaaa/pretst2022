/*
40 tests

Type
Q
1 x y
2 u v >= <=

subtask 1 (15%): all x coordinates are equal
subtask 2 (15%): q<=1000
subtask 3 (20%): all add queries comes before ask queries
subtask 4 (20%): all x and y are different
subtask 5 (30%): q<=2.5e5
*/

#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int NumberOfTests=40, NumberOfSubtasks=5;
char TestName[]="./tests/test00.inp";
ofstream outp;
int  Subtasks[]=	{0,		15,		15,		20,		20,		30		}, Deno=100;

int  MaxN[]=		{0,		250000, 1000,	250000,	250000, 250000 	};
int  MaxDifX[]=		{0,		1, 		1000, 	250000, 250000,	250000 	};
bool Shuffle12[]=	{0, 	1, 		1, 		0, 		1,		1 		};
bool Alldiff[]=		{0, 	0, 		0, 		0, 		1,		0 		};

vector<int> GenCoords(int cnt, int cntdif)
{
	vector<int> possibleCoords, shift, res;
	{
		map<int, int> temp; temp.clear();
		while(temp.size()<cntdif)
		{
			temp[rnd.next(100000000)]=1;
		}
		for(auto i:temp)
		{
			possibleCoords.push_back(i.first);
		}
		for(int i=1; i<=cntdif-1; i++) shift.push_back(1);
		for(int i=1; i<=cnt-cntdif; i++) shift.push_back(0);
		shuffle(shift.begin(), shift.end());
	}
	for(int i=0; i<cnt; i++)
	{
		res.push_back(possibleCoords.back());
		if(i<cnt-1&&shift[i]) possibleCoords.pop_back();
	}
	shuffle(res.begin(), res.end());
	return res;
}

void Gen(int pos, int Subtask, int maxN, int maxdifX, bool shuffle12, bool alldiff)
{
	outp<<Subtask<<endl;

	//Gen number of queries Q, Q1, Q2
	int Q=rnd.wnext(maxN, pos*pos)+1;
	if(pos*2>Subtasks[Subtask]) Q=maxN;
	int Q1=rnd.next(Q)+1, Q2=Q-Q1;

	outp<<Q<<endl;

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
	int cnttype1, cnttype2;
	if(pos*3>Subtasks[Subtask]) cnttype1=rnd.wnext(Q*2/3, 2), cnttype2=Q-cnttype1;
	else cnttype1=rnd.next(Q), cnttype2=Q-cnttype1;
	for(int i=1; i<=cnttype1; i++) types.push_back(1);
	for(int i=1; i<=cnttype2; i++) types.push_back(2);
	if(shuffle12) shuffle(types.begin(), types.end());

	//Output queries
	for(int i=0; i<Q; i++)
	{
		outp<<types[i]<<" "<<coordX[i]<<" "<<coordY[i];
		if(types[i]==2) outp<<" "<<rnd.next("<=|>=")<<" "<<rnd.next("<=|>=");
		outp<<endl;
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
    		TestName[12]=CurTest/10+'0', TestName[13]=CurTest%10+'0';
    		outp.open(TestName);
    		Gen(test, Subtask, MaxN[Subtask], MaxDifX[Subtask], Shuffle12[Subtask], Alldiff[Subtask]);
    		outp.close();
    	}
    }

    return 0;
}