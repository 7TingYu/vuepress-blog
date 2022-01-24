/**
 * @file #378.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-18
 * 
 * @copyright Copyright (c) 2022
 * 
 * http://oj.haizeix.com/problem/378
 * 
 * ​ 给出一个字符串，判断其中的左右括号是否匹配。
 * ​ 注：需同时判断左右圆括号 ′(′  和  ′)′，左右中括号 ′[′  和  ′]′，左右大括号 ′{′ 和 ′}′。
 * ​ 不需要考虑括号之间的优先级的问题，也就是说，小括号包含大括号，也是被允许的。
 * 
 */

#include <iostream>
#include <stack>

using namespace std;

int main() {
    stack<char> sta;
    char s[305];
    cin >> s;

    for (int i = 0; s[i] != '@'; i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            sta.push(s[i]);
        } else if (s[i] == ')') {
            if (!sta.empty() && sta.top() == '(') {
                sta.pop();
            } else {
                cout << "NO" << endl;
                return 0;
            }
        } else if (s[i] == ']') {
            if (!sta.empty() && sta.top() == '[') {
                sta.pop();
            } else {
                cout << "NO" << endl;
                return 0;
            }
        } else if (s[i] == '}') {
            if (!sta.empty() && sta.top() == '{') {
                sta.pop();
            } else {
                cout << "NO" << endl;
                return 0;
            }
        }
    }

    if (sta.empty()) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}

