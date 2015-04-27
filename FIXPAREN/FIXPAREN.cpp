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

struct p_pair {
    p_pair(int i, char c) {
        this->i = i;
        this->c = c;
    }
    int i;
    char c;
};


char get_counter(char c)
{
    if('(' == c)    return ')';
    if('{' == c)    return '}';
    if('[' == c)    return ']';
    if('<' == c)    return '>';
    if(')' == c)    return '(';
    if('}' == c)    return '{';
    if(']' == c)    return '[';
    if('>' == c)    return '<';
    
    return 'x';
}

string solve(const string& ll)
{
    vector<string> split_str = split(ll, ' ');
    string l = split_str[0];
    string order = split_str[1];
    stack<p_pair> s;
    for(size_t i = 0; i < l.size(); ++i )
    {
        if(l[i] == '(' || l[i] == '{' || l[i] == '[' ||  l[i] == '<')
            s.push(p_pair(i,l[i]));
        else {
            char counterOfClosed = get_counter(l[i]);
            
            if(s.top().c != counterOfClosed)
            {
                for(size_t j = 0; j < order.size(); ++j)
                {
                    if(order[j] == s.top().c) {
                        l[i] = get_counter(s.top().c);
                        break;
                    }else if(order[j] == counterOfClosed) {
                        l[s.top().i] = counterOfClosed;
                        break;
                    }
                }
            }
            s.pop();
        }
    }
    
    return l;
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
