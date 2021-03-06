---
title: 门徒 1.链表
date: 2022-02-25
tags:
 - 门徒
categories:
 - 门徒

---



## leetCode 141 环形链表

判断一个数是否是环形链表的最快方式是通过快慢赛跑指针的形式


```cpp
class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        if (head == NULL)
            return false;

        ListNode *slow = head, *quick = head->next;

        while (slow && quick && quick->next && quick != slow)
        {
            slow = slow->next;
            quick = quick->next->next;
        }

        return quick == slow;
    }
};
```


## leetCode 142 环形链表-ii

需要计算环的节点

```
设节点为 x
已知快指针与慢指针相遇，另快指针走的距离为 q，慢指针为 s，c 为一圈
s = q - c
s = 2s - c
另 y 为 慢指针走过节点后的距离
x + y = 2(x + y) - c
x + y = c
x = c - y
```

c - y 为慢指针走完一圈需要再走多久

看出什么了么？

若我们再从初始点出发，慢指针在与快指针相遇处再向前走，我们会在环的节点处相遇


```cpp
class Solution
{
public:
    ListNode *detectCycle(ListNode *head)
    {
        if (head == nullptr)
            return nullptr;
        if (head->next == nullptr)
            return nullptr;

        ListNode *slow = head, *quick = head;

        do
        {
            slow = slow->next;
            quick = quick->next->next;
        } while (slow && quick && quick->next && quick != slow);

        if (quick == slow)
        {
            ListNode *start = head;
            while (slow != start)
            {
                slow = slow->next;
                start = start->next;
            }
            return slow;
        }
        return nullptr;
    }
};
```


## leetCode 202 快乐数


```cpp
class Solution {
public:
    int getNext(int x) {
        int ret = 0;
        while(x > 0) {
            int n = x % 10;
            ret += n * n;
            x = x / 10;
        }
        return ret;
    }
    bool isHappy(int n) {
        int slow = n, quick = n;

        do {
            slow = getNext(slow);
            quick = getNext(getNext(quick));
        } while (slow != quick && quick != 1);

        return quick == 1;
    }
};
```


## leetCode 206 反转链表


```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode *tail = head->next;
        ListNode *ret = reverseList(head->next);
        head->next = tail->next;
        tail->next = head;
        return ret;
    }
};
```



## leetCode 92 反转链表-ii


```cpp
class Solution {
public:
    ListNode* reverseNode(ListNode* node, int l) {
        if (l == 1) return node;
        ListNode *tail = node->next;
        ListNode *ret = reverseNode(node->next, l-1);
        node->next = tail->next;
        tail->next = node;
        return ret;
    }
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode ret(0, head);
        ListNode *p = &ret;
        int cnt = n - m + 1;
        while (--m) {
            p = p->next;
        }
        p->next = reverseNode(p->next, cnt);
        return ret.next;
    }
};
```




## leetCode 25 k-个一组反转链表


```cpp
class Solution
{
public:
    ListNode *_reserseN_(ListNode *head, int n)
    {
        if (n == 1)
            return head;
        ListNode *tail = head->next;
        ListNode *ret = _reserseN_(head->next, n - 1);
        head->next = tail->next;
        tail->next = head;
        return ret;
    }
    ListNode *reserseN(ListNode *head, int n)
    {
        ListNode *p = head;
        int cnt = n;
        while (--n && p)
        {
            p = p->next;
        }
        if (p == nullptr)
            return head;
        return _reserseN_(head, cnt);
    }
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode hair(0, head);
        ListNode *p = &hair;
        ListNode *q = p->next;

        while ((p->next = reserseN(q, k)) != q)
        {
            p = q;
            q = p->next;
        }
        return hair.next;
    }
};
```

## leetCode 61 旋转链表


```cpp
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr) return nullptr;
        int n = 1;
        ListNode *p = head;
        while (p->next) {
            p = p->next;
            n = n + 1;
        }
        p->next = head;
        k = k % n;
        k = n - k;
        while (k--) {
            p = p->next;
        }
        head = p->next;
        p->next = nullptr;
        return head;
    }
};
```


## leetCode 24 两两交换链表中的节点


```cpp
class Solution {
public:
    ListNode *_reserseN_(ListNode *head, int n)
    {
        if (n == 1)
            return head;
        ListNode *tail = head->next;
        ListNode *ret = _reserseN_(head->next, n - 1);
        head->next = tail->next;
        tail->next = head;
        return ret;
    }
    ListNode *reserseN(ListNode *head, int n)
    {
        ListNode *p = head;
        int cnt = n;
        while (--n && p)
        {
            p = p->next;
        }
        if (p == nullptr)
            return head;
        return _reserseN_(head, cnt);
    }
    ListNode* swapPairs(ListNode* head) {
        ListNode hair(0, head);
        ListNode *p = &hair;
        ListNode *q = p->next;

        while ((p->next = reserseN(q, 2)) != q)
        {
            p = q;
            q = p->next;
        }
        return hair.next;
    }
};
```


## leetCode 19 删除链表的倒数第-n-个节点


```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode hair(0, head);
        ListNode *p = &hair, *q = head;

        while(n--) {
            q = q->next;
        }

        while(q) {
            p = p->next;
            q = q->next;
        }

        p->next = p->next->next;
        return hair.next;
    }
};
```

## leetCode 83 删除排序链表中的重复元素


```cpp
class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode *slow = head, *fast = head->next;

        while (fast)
        {
            if (fast->val != slow->val)
            {
                slow->next = fast;
                slow = fast;
            }
            fast = fast->next;
        }

        slow->next = fast;

        return head;
    }
};
```

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode *fast = head;

        while (fast->next) {
            if (fast->val == fast->next->val) {
                fast->next = fast->next->next;
            } else {
                fast = fast->next;
            }
        }

        return head;
    }
};
```


## leetCode 82 删除排序链表中的重复元素-ii


```cpp
class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {

        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode hair(0, head);
        ListNode *slow = &hair, *fast;

        while (slow->next)
        {
            if (slow->next->next && slow->next->val == slow->next->next->val)
            {
                fast = slow->next->next;
                while (fast && fast->val == slow->next->val)
                {
                    fast = fast->next;
                }
                slow->next = fast;
            }
            else
            {
                slow = slow->next;
            }
        }

        return hair.next;
    }
};
```


