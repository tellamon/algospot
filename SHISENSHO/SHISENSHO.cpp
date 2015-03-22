#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//for debugging
#define D(...) do{ printf(__VA_ARGS__ ); } while( false )
//#define D(...) do{  } while( false )

int H, W, endX, endY;
vector<string> rows;

bool check( int x, int y, int xd, int yd, int cnt)
{
    if(x + xd == ex && y + yd == ey) {
        return true;
    }
    bool changeY = false;
    bool changeX = false;

    //check boundary

    if(0 != yd) {
        if(y + yd < 0 || y + yd > H) {
            changeX = true;
        }else if('.' != rows[y+yd][x]){
            changeX = true;
        }
    }

    if((changeX || changeY) && cnt == 1)
        return false;
    if(changeX && x == endX)
        return false;
    if(changeY && y == endY)
        return false;

    if(changeX) {
        if( x < endX)
            check(x, y, 1, 0, cnt - 1);
        if( x > endX)
            check(x, y, -1, 0, cnt - 1);


    return false;
}

int solve(int H, int W, const vector<string> & rows)
{
    int count = 0;
    // for all tiles
    for(int sy = 0; sy < H; ++sy){
        for(int sx = 0; sx < W - 1; ++sx) {
            // for tiles from start pos
            if(get(sy,sx) != '.') {
                for(int ey = sy; ey < H; ++ey){
                    for(int ex = sx+1; ex < W; ++ex) {
                        if(rows[sy][sx] == rows[ey][ex]) {
                            endX = ex;
                            endY = ey;
                            if(check(sx, sy, -1, 0, 3))
                                count++;
                            else if(check(sx, sy, 1, 0, 3))
                                count++;
                            else if(check(sx, sy, 0, -1, 3))
                                count++;
                            else if(check(sx, sy, 0, 1, 3))
                                count++;
                        }
                    }
                }
            }

        }
    }
}

int main() {
    int N;
    string l;
    getline(cin, l);
    N = atoi(l.c_str());
    while(N--) {
        rows.clear();
        cin >> H >> W;
        D("%d, %d\n", H, W);
        for(int h = 0; h < H; ++h) {
            cin >> l;
            rows.push_back(l);
        }     

        cout << solve(H,W,rows) << std::endl;   
    }
}
}
