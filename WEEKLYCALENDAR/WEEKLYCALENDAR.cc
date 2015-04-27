#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>

using namespace std;
//for debugging
//#define D(...) do{ printf(__VA_ARGS__ ); } while( false )
#define D(...) do{  } while( false )

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

string solve(string l)
{
    D("start\n");
    vector<string> s = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    vector<int> lastDay = {31,28,31,30,31,30,31,31,30,31,30,31};
    vector<string> v = split(l,' ');
    int mIdx = atoi(v[0].c_str()) - 1;
    int lDayPrev = lastDay[mIdx ? mIdx : 11];
    int lDayNext = lastDay[(mIdx + 1)  % 12];
    int dIdx = find(s.begin(), s.end(), v[2]) - s.begin();
    
    D("%d %d %d %d\n", mIdx, lDayPrev,lDayNext, dIdx);
    list<int> res;
    int cur = atoi(v[1].c_str());
    res.push_back(cur);
    int d = cur - 1;
    for(int i = dIdx-1; i >= 0; --i)
    {
        if(0 == d)
            d = lDayPrev;
        res.push_front(d);
        d--;
    }
    
    d = cur + 1;
    for(int i = dIdx+1; i <= 6; ++i)
    {
        if(lastDay[mIdx] < d)
            d = 1;
        res.push_back(d);
        d++;
    }
    stringstream res_str;
    for(auto it = res.begin(); it != res.end(); ) {
        res_str << *it;
        ++it;
        if(it != res.end())
            res_str << " ";
    }
    D("\nend\n");
    return res_str.str();
}

int main() {
  int N;
  string l;
  getline(cin, l);
  N = atoi(l.c_str());
  while(N--) {
    getline(cin, l);
    D("%s\n", l.c_str());
    cout << solve(l) << std::endl;   
  }
}
