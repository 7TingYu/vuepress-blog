#include <iostream>
#include <queue>

using namespace std;

struct node
{
    int a, b;

    bool operator<(const node &b) const {
        if (this->a == b.a) {
            return this->b > b.b;
        }
        return this->a > b.a;
    }
};

struct cmp {
    bool operator() (const node &a, const node &b) {
        if (a.a == b.a) {
            return a.b > b.b;
        }
        return a.a > b.a;
    }
};

int main()
{
    // priority_queue<node> que;
    priority_queue<node, vector<node>, cmp >que;
    que.push((node){2, 12});
    que.push((node){2, 1});
    que.push((node){99, 7});
    que.push((node){12, 7});
    que.push((node){-1, 0});

    while (!que.empty())
    {
        cout << que.top().a << " " << que.top().b << endl;
        que.pop();
    }

    // priority_queue<int> que;
    // 大顶堆
    // priority_queue<int, vector<int>, greater<int> > que;
    // 小顶堆
    // priority_queue<int, vector<int>, less<int> > que;
    // que.push(9);
    // que.push(5);
    // que.push(-3);
    // que.push(99);
    // que.push(999);

    // cout << que.size() << endl;
    // while (!que.empty())
    // {
    //     cout << que.top() << endl;
    //     que.pop();
    // }

    return 0;
}