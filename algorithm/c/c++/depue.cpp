#include <iostream>
#include <deque>

using namespace std;


int main()
{
    deque<int> que;
    que.push_front(99);
    que.push_front(0);
    que.push_front(9);
    que.push_back(22);
    que.push_back(-7);

    while (!que.empty())
    {
        cout << que.front() << " " << que.back() << endl;
        que.pop_front();
        if(!que.empty()) {
            que.pop_back();
        }
    }

    return 0;
}