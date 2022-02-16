#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

void PrintStrint(const string& s_)
{
    cout << s_ << endl;
}

int main()
{
    string input;
    map<string, size_t> strMap;
    queue<string> q;

    while (getline(cin, input) && "." != input)
    {
        if (0 == strMap[input])
        {
            q.push(input);
        }
        ++strMap[input];
    }
    
    while (!q.empty())
    {
        cout << strMap[q.front()] << ' ' << q.front() << endl;
        q.pop();
    }
    
    return  0;
}