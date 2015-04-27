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

using namespace std;

//for debugging
#define D(...) do{ printf(__VA_ARGS__ ); } while( false )
//#define D(...) do{  } while( false )

int H, W, endX, endY;
vector<string> rows;

bool check( int x, int y, int xd, int yd, int cnt)
{
    if(x + xd == endX && y + yd == endY) {
        return true;
    }

    if(y < 0 || y >= H)
        return false;
    
    if(x < 0 || x >= W)
        return false;

    bool changeY = false;
    bool changeX = false;

    //check boundary
    //D("%d, %d, %d, %d\n", x, y, xd, yd);
    if(0 != yd) {
        if(y + yd < 0 || y + yd >= H) {
            changeX = true;
        }else if('.' != rows[y+yd][x]){
            changeX = true;
        }
    }else if(0 != xd) {
        if(x + xd < 0 || x + xd >= W) {
            changeY = true;
        }else if('.' != rows[y][x+xd]){
            changeY = true;
        }
    }else
        assert(!"should not happen");


    if(changeX && x == endX)
        return false;
    if(changeY && y == endY)
        return false;

    if(x == endX && 0 != xd)    //??
        changeY = true;
    if(y == endY && 0 != yd)
        changeX = true;

    if((changeX || changeY) && cnt == 1)
        return false;

    if(changeX) {
        int new_xd = 0;
        if( x < endX)
            new_xd = 1;
        if( x > endX)
            new_xd = -1;
        bool res_one_way = check(x+new_xd, y, new_xd, 0, cnt - 1);
        
        if(res_one_way)
            return true;
        else{
            new_xd = -new_xd;
            return check(x+new_xd, y, new_xd, 0, cnt - 1);
        }
    }else if(changeY) {
        int new_yd = 0;
        if( y < endY)
            new_yd = 1;
        if( y > endY)
            new_yd = -1;
        bool res_one_way = check(x, y+new_yd, 0, new_yd, cnt - 1);
        
        if(res_one_way)
            return true;
        else {
            new_yd = -new_yd;
            return check(x, y+new_yd, 0, new_yd, cnt - 1);
        }
    }else {
		if('.' != rows[y+yd][x+xd])
			return false;
        return check(x + xd, y + yd, xd, yd, cnt);
	}
}

int solve(int H, int W, const vector<string> & rows)
{
    //D("solve H%d, W%d, rows%d", H, W,(int)rows.size());
    
    int count = 0;
    // for all tiles
    for(int sy = 0; sy < H; ++sy){
        for(int sx = 0; sx < W - 1; ++sx) {
            // for tiles from start pos
            char sCh = rows[sy][sx];
            if( sCh != '.') {
                for(int ey = sy; ey < H; ++ey){
                    int ex = sx+1;
                    if(ey != sy)
                        ex = 0;											
                    for(; ex < W; ++ex) {
                        //D("check ey%d, ex%d\n", ey, ex);
                        char eCh = rows[ey][ex];
                        if(sCh == eCh) {
                            //D("check sy%d, sx%d -> ey%d, ex%d\n", sy, sx, ey, ex);
                            endX = ex;
                            endY = ey;
                            if(check(sx, sy, -1, 0, 3)){
								D("found sy%d, sx%d -> ey%d, ex%d\n", sy, sx, ey, ex);
                                count++;
                            }else if(check(sx, sy, 1, 0, 3)){
								D("found sy%d, sx%d -> ey%d, ex%d\n", sy, sx, ey, ex);
                                count++;
							}
                            else if(check(sx, sy, 0, -1, 3)){
								D("found sy%d, sx%d -> ey%d, ex%d\n", sy, sx, ey, ex);
                                count++;
							}
                            else if(check(sx, sy, 0, 1, 3)){
								D("found sy%d, sx%d -> ey%d, ex%d\n", sy, sx, ey, ex);
                                count++;
							}
                        }
                    }
                }
            }
        }
    }
    return count;
}

int main() {
    
    ifstream in_stream("input.txt");
    //istream& in_stream = cin;
    int N;
    string l;
    getline(in_stream, l);
    N = atoi(l.c_str());
    while(N--) {
        rows.clear();
        in_stream >> H >> W;
        D("%d, %d\n", H, W);
        for(int h = 0; h < H; ++h) {
            in_stream >> l;
            D("line %s\n", l.c_str());
            rows.push_back(l);
        }
        cout << solve(H,W,rows) << std::endl;   
    }
}