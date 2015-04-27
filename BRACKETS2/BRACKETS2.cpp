#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

//for debugging
#define D(...) do{ printf(__VA_ARGS__ ); } while( false )
//#define D(...) do{  } while( false )

char get_counter(char c)
{
    if('(' == c)    return ')';
    if('{' == c)    return '}';
    if('[' == c)    return ']';
    
    return 'x';
}
string solve(const string& l)
{
    stack<char> s;
    for(size_t i = 0; i < l.size(); ++i )
    {
        if(l[i] == '(' || l[i] == '{' || l[i] == '[')
            s.push(l[i]);
        else {
            if(s.empty())
                return "NO";
            if(get_counter(s.top()) != l[i])
                return "NO";
            s.pop();
        }
    }
    
    if(!s.empty())
        return "NO";
    
    return "YES";
}

int main() {
    
    //ifstream in_stream("input.txt");
    istream& in_stream = cin;
    int N;
    string l;
    getline(in_stream, l);
    N = atoi(l.c_str());
    while(N--) {
        getline(in_stream, l);

        cout << solve(l) << std::endl;   
    }
}
