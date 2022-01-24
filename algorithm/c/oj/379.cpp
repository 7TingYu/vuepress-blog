/**
 * @file #378.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-18
 * 
 * @copyright Copyright (c) 2022
 * 
 * http://oj.haizeix.com/problem/379
 * 
 * ​ 379. 仓库日志
 *  辅助栈
 * 
 */

#include <iostream>
#include <stack>

using namespace std;

int main() {
    stack<int> sta, mmax;
    mmax.push(0);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int t;
        scanf("%d", &t);

        if (t == 0) {
            scanf("%d", &t);
            sta.push(t);
            mmax.push(max(mmax.top(), t));
        } else if (t == 1) {
            if (!sta.empty()) {
                sta.pop();
                mmax.pop();
            }
        } else if (t == 2) {
            printf("%d\n", mmax.top());
        }
    }

    return 0;
}
