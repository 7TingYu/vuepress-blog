#include <iostream>
#include <stack>

using namespace std;

struct node {
    int a,b;
};

int main() {
    stack<node> sta;
    sta.push((node){2, 1});
    sta.push((node){99, 7});
    sta.push((node){12, 7});
    sta.push((node){-1, 0});

    while(!sta.empty()) {
        cout << sta.top().a << " " << sta.top().b << endl;
        sta.pop();
    }

    // stack<double> sta;
    // sta.push(2.7);
    // sta.push(5.9);
    // sta.push(12.5);
    // sta.push(-8.9);

    // cout << sta.size() << endl;

    // while(!sta.empty()) {
    //     cout << sta.top() << endl;
    //     sta.pop();
    // }

    // cout << sta.size() << endl;

    return 0;
}