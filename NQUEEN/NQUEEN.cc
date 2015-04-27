#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <stack>
#include <string.h>

using namespace std;
struct my_pt{
	int x;
	int y;

	my_pt(int _x, int _y) :
	x(_x),
	y(_y){

	}
};
//for debugging
#define D(...) do{ printf(__VA_ARGS__ ); } while( false )
//#define D(...) do{  } while( false )

int B[12][12];
int V[12][12][12];	//visited flag
int N = 0;

bool findEmpty(int vIdx, int sx, int sy, int& ex, int& ey)
{
	ex = -1;
	ey = -1;
	for(int py = sy; py < N; ++py){
		int px = sy;
		if(py != sy)
			px = 0;
		for(; px < N; ++px) {
			//find empty X,Y
			
			if(0 == B[py][px] && 0 == V[vIdx][py][px]) {
				V[vIdx][py][px] = 1;
				ex = px;
				ey = py;
				return true;
			}
		}
	}
	return false;
}

void putQueen(int x, int y, bool put)
{
	for(int sy = 0; sy < N; ++sy) {
        for(int sx = 0; sx < N; ++sx) {
			if(sy == y || sx == x)
				if(put)
					B[sy][sx]++;
				else
					B[sy][sx]--;
		}
	}
	for(int sy = y-1; sy >= 0; --sy) {
        for(int sx = x-1; sx >= 0; --sx) {
			if(abs(sx-sy) != abs(x-y))	continue;
				if(put)
					B[sy][sx]++;
				else
					B[sy][sx]--;
		}
	}
	for(int sy = y-1; sy >= 0; --sy) {
        for(int sx = x+1; sx < N; ++sx) {
			if(abs(sx-sy) != abs(x-y))	continue;
				if(put)
					B[sy][sx]++;
				else
					B[sy][sx]--;
		}
	}
	for(int sy = y+1; sy < N; ++sy) {
        for(int sx = x-1; sx >= 0; --sx) {
			if(abs(sx-sy) != abs(x-y))	continue;
				if(put)
					B[sy][sx]++;
				else
					B[sy][sx]--;
		}
	}
	for(int sy = y+1; sy < N; ++sy) {
        for(int sx = x+1; sx < N; ++sx) {
			if(abs(sx-sy) != abs(x-y))	continue;
				if(put)
					B[sy][sx]++;
				else
					B[sy][sx]--;
		}
	}

}

int solve(int N)
{
    //D("solve H%d, W%d, rows%d", H, W,(int)rows.size());
    int P = 0;
 
    // for all tiles
	memset(B, 0, 12*12*sizeof(int));
	memset(V, 0, 12*12*12*sizeof(int));

	std::stack<my_pt> q_pos;
	int sx = 0;
	int sy = 0;
	D("sx:%d, sy:%d\n", sx, sy);
	while(true) {
		//find empty X,Y
		int ex,ey;
		if(findEmpty(q_pos.size(), 0,0,ex,ey))
		{
			if(q_pos.size() +1 == N){
				++P;
			}else {
				
				D("PUT:[%d]%d,%d\n",q_pos.size(), ex,ey);
				q_pos.push(my_pt(ex,ey));
				putQueen(ex,ey, true);
				sx = 0;
				sy = ey + 1;
				continue;
			}
		}

		if(q_pos.empty())
			break;
		sx = q_pos.top().x;
		sy = q_pos.top().y;
		D("POP:[%d]%d,%d\n", q_pos.size(), sx,sy);
		putQueen(sx,sy, false);
		memset(V[q_pos.size()], 0, 12*12*sizeof(int));
		//++sx;
		//if(sx == N) {
		//	sx = 0;
		//	++sy;
		//	if(sy == N)
		//		break;
		//}
		q_pos.pop(); 
	}

    return P;
}

int main() {
    
    ifstream in_stream("input.txt");
    //istream& in_stream = cin;
    int C;
    string l;
    getline(in_stream, l);
    C = atoi(l.c_str());
    while(C--) {
		
        in_stream >> N;
        cout << solve(N) << std::endl;   
    }
}