#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct node
{
    string s;
    double b;
};

int main()
{
    queue<char> que;
    que.push('>');
    que.push('=');
    que.push('a');
    que.push('N');
    que.push('5');

    while(!que.empty()) {
        cout << que.front() << " " << que.back() << endl;
        que.pop();
    }

    return 0;
}