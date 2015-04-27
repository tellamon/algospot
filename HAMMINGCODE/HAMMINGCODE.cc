#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

//for debugging
#define D(...) do{ printf(__VA_ARGS__ ); } while( false )
//#define D(...) do{  } while( false )

int n(char c) {
  return c - '0';
}

char flip(char c) {
  if('0' == c)
    return '1';
  else
    return '0';
}


string solve(string l)
{
  l.insert(0,"-");//for easy indexing
  int p1 = (n(l[1]) ^ n(l[3]) ^ n(l[5]) ^ n(l[7])) & 1;
  int p2 = (n(l[2]) ^ n(l[3]) ^ n(l[6]) ^ n(l[7])) & 1;
  int p4 = (n(l[4]) ^ n(l[5]) ^ n(l[6]) ^ n(l[7])) & 1;
  
  int p = p1 + (2 * p2) + (4 * p4);
  //D("p : %d\n", p);
  if(p)
    l[p] = flip(l[p]);
    
  stringstream org;
  org << l[3] << l[5] << l[6] << l[7];
  
  return org.str();
}

int main() {
  int N;
  string l;
  getline(cin, l);
  N = atoi(l.c_str());
  while(N--) {
    getline(cin, l);
    cout << solve(l) << std::endl;   
  }
}
