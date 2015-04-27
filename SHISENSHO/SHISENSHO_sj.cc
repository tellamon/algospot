#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <string.h>

struct testCase
{
    int height;
    int width;
    std::vector<std::string> lines;
};

struct Tile
{
    int x;
    int y;
};

struct Map
{
    int width;
    int height;
    char buf[50][50];
    std::map<char, std::vector<Tile> > map;
    
};

void generate_map(testCase &data , Map &map)
{
    map.width = data.width;
    map.height = data.height;
    memset(map.buf, 0, map.width*map.height);
    
    for(int h = 0;h < data.height;++h)
    {
        std::string line = data.lines[h];
        for(auto it = line.begin();it!=line.end();++it)
        {
            Tile tile;
            tile.x =std::distance(line.begin(), it);
            tile.y =h;
            if ( (*it) != '.' )
                map.map[(*it)].push_back(tile);
            map.buf[tile.y][tile.x] = (*it);
        }
    }
}

bool calc_pair_seg_one(int x1, int y1, int x2, int y2, char buf[50][50])
{
    //std::cout << "[seg_one] (" << x1 << "," << y1 << ") , (" << x2 << "," << y2 << ")" << std::endl;
    if (x1 == x2)
    {
        int sy, dy;
        if (y1 > y2) { sy =y2; dy = y1; }
        else { sy = y1; dy = y2; }
        
        for(int y = sy+1;y < dy;++y)
        {
            if (buf[y][x1] != '.')
            {
                //std::cout << "[seg_one] block1 (" << x1 << "," << y << ") = " << buf[y][x1] << std::endl;
                return false;
            }
        }
        //std::cout << "[seg_one] matched1" << std::endl;
        return true;
    }
    else if (y1 == y2)
    {
        int sx, dx;
        if (x1 > x2) { sx =x2; dx = x1; }
        else { sx = x1; dx = x2; }
        
        for(int x = sx+1;x < dx;++x)
        {
            if (buf[y1][x] != '.')
            {
                //std::cout << "[seg_one] block2 (" << x << "," << y1 << ") = " << buf[y1][x] << std::endl;
                return false;
            }
        }
        //std::cout << "[seg_one] matched2" << std::endl;
        return true;
    }
    
    //std::cout << "[seg_one] not matched" << std::endl;
    return false;
}

bool calc_pair_seg_two_x(int x1, int y1, int x2, int y2, char buf[50][50])
{
    if (!calc_pair_seg_one(x1,y1,x2,y1,buf))
        return false;
    if (buf[y1][x2] != '.')
        return false;
    if (!calc_pair_seg_one(x2,y1,x2,y2,buf))
        return false;
    
    return true;
}

bool calc_pair_seg_two_y(int x1, int y1, int x2, int y2, char buf[50][50])
{
    if (!calc_pair_seg_one(x1,y1,x1,y2,buf))
        return false;
    if (buf[y2][x1] != '.')
        return false;
    if (!calc_pair_seg_one(x1,y2,x2,y2,buf))
        return false;
    
    return true;
}

bool calc_pair_seg_two(int x1, int y1, int x2, int y2, char buf[50][50])
{
    //std::cout << "[seg_two] (" << x1 << "," << y1 << ") , (" << x2 << "," << y2 << ")" << std::endl;
    if (calc_pair_seg_two_x(x1,y1,x2,y2,buf))
    {
        //std::cout << "[seg_two] matched1" << std::endl;
        return true;
    }
    if (calc_pair_seg_two_y(x1,y1,x2,y2,buf))
    {
        //std::cout << "[seg_two] matched2" << std::endl;
        return true;
    }
    //std::cout << "[seg_two] not matched" << std::endl;
    return false;
}

bool calc_pair_seg_three_x(int x1, int y1, int x2, int y2, char buf[50][50])
{
    for(int x=x1-1;x>=0;--x)
    {
        if (buf[y1][x] != '.')
            break;
        if (calc_pair_seg_two(x,y1,x2,y2,buf))
            return true;
    }
    
    for(int x=x1+1;x<50;++x)
    {
        if (buf[y1][x] != '.')
            break;
        if (calc_pair_seg_two(x,y1,x2,y2,buf))
            return true;
    }
    return false;
}

bool calc_pair_seg_three_y(int x1, int y1, int x2, int y2, char buf[50][50])
{
    for(int y=y1-1;y>=0;--y)
    {
        if (buf[y][x1] != '.')
            break;
        if (calc_pair_seg_two(x1,y,x2,y2,buf))
            return true;
    }
    
    for(int y=y1+1;y<50;++y)
    {
        if (buf[y][x1] != '.')
            break;
        if (calc_pair_seg_two(x1,y,x2,y2,buf))
            return true;
    }
    return false;
}

bool calc_pair_seg_three(int x1, int y1, int x2, int y2, char buf[50][50])
{
    //std::cout << "[seg_three] (" << x1 << "," << y1 << ") , (" << x2 << "," << y2 << ")" << std::endl;
    if (calc_pair_seg_three_x(x1,y1,x2,y2,buf))
    {
        //std::cout << "[seg_three] matched1" << std::endl;
        return true;
    }
    if (calc_pair_seg_three_y(x1,y1,x2,y2,buf))
    {
        //std::cout << "[seg_three] matched2" << std::endl;
        return true;
    }
    //std::cout << "[seg_three] not matched" << std::endl;
    return false;
}

int calc_pair(std::vector<Tile> &list, char buf[50][50])
{
    int sum = 0;
    for(auto it = list.begin();it != list.end(); ++it)
    {
        int x = (*it).x;
        int y = (*it).y;
        
        for(auto it2 = it+1;it2 != list.end();++it2)
        {
            if (calc_pair_seg_one(x, y, (*it2).x, (*it2).y, buf)) {
                std::cout << "found sy" << y << ",sx" << x << " -> ey" << (*it2).y << ", ex" <<  (*it2).x<<"\n";
                ++sum;
            }else if (calc_pair_seg_two(x, y, (*it2).x, (*it2).y, buf)){
                std::cout << "found sy" << y << ",sx" << x << " -> ey" << (*it2).y << ", ex" <<  (*it2).x<<"\n";
                ++sum;
            }else if (calc_pair_seg_three(x, y, (*it2).x, (*it2).y, buf)){
                std::cout << "found sy" << y << ",sx" << x << " -> ey" << (*it2).y << ", ex" <<  (*it2).x<<"\n";
                ++sum;
            }
        }
    }
    
    return sum;
}

int main()
{
    int numTest = 0;

    std::cin >> numTest;

    std::vector<testCase> testCases;
    for(int i = 0;i < numTest;++i)
    {
        testCase testcase;
        std::cin >> testcase.height >> testcase.width;
        
        std::string str;
        for(int j=0;j<testcase.height;++j)
        {
            std::cin >> str;
            testcase.lines.push_back(str);
        }

        testCases.push_back(testcase);
    }
    
    for(auto it = testCases.begin();it != testCases.end();++it)
    {
        Map map;
        generate_map((*it), map);
        
        int pair = 0;
        for(auto it2 = map.map.begin();it2 != map.map.end();++it2)
            pair += calc_pair( (*it2).second, map.buf );
            
        std::cout << pair << std::endl;
    }
    

    return 0;
}
