#include <iostream>
#include <string>
#include <map>

using namespace std;

string convertURI(string l)
{
  map <string, string> x  { 
    { "%20", " " },
    { "%21", "!" },
    { "%24", "$" },
    { "%25", "%" },
    { "%28", "(" },
    { "%29", ")" },
    { "%2a", "*" }
  };
  
  for(int i = 0; i< l.length(); ++i) {
    for(auto it = x.begin(); it != x.end(); ++it) {
      if(l.compare(i, 3, it->first) == 0) {
        l.replace(i, 3, it->second);
        break;
      }
    }
  }
  
  return l;
}

int main() {
  int N;
  string l;
  getline(cin, l);
  N = atoi(l.c_str());
  while(N--) {
    getline(cin, l);
    cout << convertURI(l) << std::endl;   
  }
}
