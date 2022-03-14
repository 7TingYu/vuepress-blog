---
title: 门徒 3.递归与栈
date: 2022-03-11
tags:
 - 门徒
categories:
 - 门徒

---

## 栈的基本性质

先进后出


### leetCode 20 有效的括号

```cpp
class Stack{
private:
    int top, *data;
public:
    Stack(int n = 100)
    {
        top = 0;
        data = new int[n];
    }
    void push(int val) { data[top++] = val; }
    void pop() { top--; }
    int getTop() { return data[top - 1]; }
    bool empty() { return top == 0; }
    int size() { return top; }
};
class Solution{
public:
    bool matched(char x, char y)
    {
        if (x == '(' && y == ')')
            return true;
        if (x == '[' && y == ']')
            return true;
        if (x == '{' && y == '}')
            return true;
        return false;
    }
    bool isValid(string s)
    {
        Stack sta(10005);
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{')
            {
                sta.push(s[i]);
            }
            else
            {
                if (sta.empty() || !matched(sta.getTop(), s[i]))
                {
                    return false;
                }
                sta.pop();
            }
        }
        return sta.empty();
    }
};
```





































