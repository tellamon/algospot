#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <numeric>

using namespace std;

vector<int> getDevisors(int n){
  vector<int> result;
  for(int i = 1; i < n; ++i){
    if(n%i == 0)
      result.push_back(i);
  }
  return result;
}

bool isAbundent(int n, vector<int> & d){
  int sum_of_elems = ::accumulate(d.begin(),d.end(),0);
  if(sum_of_elems < n)
    return true;
    
  return false;
}

bool isSemiperfect(int n, vector<int> & d){
  
  
  return false;
}


string solve(string l)
{
  int n = atoi(l.c_str());

  vector<int> devisors = getDevisors(n);
  if(!isAbundent(n, devisors))
    return "not weird";
  
  if(!isSemiperfect(n,devisors))
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
