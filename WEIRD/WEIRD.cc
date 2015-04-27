#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <stdio.h>

using namespace std;

//TODO : 다른 방식(DP?) 풀이 분석 : http://huck.tistory.com/102, http://trynerr.tistory.com/5

//for debugging
#define D(...) do{ printf(__VA_ARGS__ ); } while( false )
//#define D(...) do{  } while( false )

// 12 - 1 2 3 4 6 
// 70 - 1 2 5 7 10 14 35
vector<int> getDivisors(int n){
  D("divisors:");
  vector<int> result;
  for(int i = 2; i <= n/2; ++i){
    if(n%i == 0){
      result.push_back(i);
      D("%d ", i);
    }
  }
  D("\n");
  return result;
}

bool isAbundent(int n, vector<int> & d){
  int sum_of_elems = ::accumulate(d.begin(),d.end(),0);
  if(sum_of_elems > n)
    return true;
    
  return false;
}

bool isSemiperfect(int n, vector<int> & d){
  if( 0 == n)
    return true;
    
  for(int i = d.size(); 0 < i ; --i)
  {
    int temp = d.back();
    d.pop_back();
    if(isSemiperfect(n - temp, d))
      return true;
    d.push_back(temp);
  }
  return false;
}


string solve(string l)
{
  int n = atoi(l.c_str());

  vector<int> divisors = getDivisors(n);
  if(!isAbundent(n, divisors))
    return "not weird";
  
  if(!isSemiperfect(n, divisors))
    return "weird";
  else
    return "not weird";
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
