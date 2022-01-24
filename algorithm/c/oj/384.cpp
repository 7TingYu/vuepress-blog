/**
 * @file #378.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-18
 * 
 * @copyright Copyright (c) 2022
 * 
 * http://oj.haizeix.com/problem/384
 * 
 * ​ 384. 敲七
 *  辅助栈
 * 
 */

#include <iostream>
#include <queue>

using namespace std;

int func(int x) {
    if (x % 7 == 0) return 0;
    while (x != 0) {
        if (x % 10 == 7) return 0;
        x /= 10;
    }
    return 1;
}

int main()
{
    int n, x, t;
    cin >> n >> x >> t;

    queue<int> que;
    for (int i = x; i <= n; i++) {
        que.push(i);
    }
    for (int i = 1; i < x; i++) {
        que.push(i);
    }

    while(que.size() != 1) {
        if (func(t)) {
            que.push(que.front());
        }
        que.pop();
        t++;
    }
    cout << que.front() << endl;

    return 0;
}
