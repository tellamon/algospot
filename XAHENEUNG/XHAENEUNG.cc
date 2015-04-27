#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

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
  vector <string> x  { 
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
    "ten"
  };
  
  
  std::vector<std::string> tokens = split(l, ' ');
  
  
  int v1 = distance(x.begin(), find(x.begin(), x.end(), tokens[0]));
  int v2 = distance(x.begin(), find(x.begin(), x.end(), tokens[2]));
  
  int ans  = -1;
  
  if(tokens[1] == "+")
    ans = v1 + v2;
  else if(tokens[1] == "-")
    ans = v1 - v2;
  else if(tokens[1] == "*")
    ans = v1 * v2;
  else if(tokens[1] == "/")
    ans = v1 / v2;
  
  // << "Expected : " << ans << endl;
  
  if(ans < 0 || 10 < ans)
    return "No";
  
  auto ansPos = find_if(x.begin(), x.end(),
                      [&] (const string& v) {
                        return is_permutation(tokens[4].begin(),tokens[4].end(), v.begin());
                      }
                      );
  if(x.end() == ansPos) {
    return "No";
  }else {
    int ansInput = distance(x.begin(), ansPos);
    //cout << "ansInput : " << ansInput << endl;
    if(ansInput == ans)
      return "Yes";
    else
      return "No";
  }
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
