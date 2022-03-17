---
title: 门徒 2.线程池与任务队列
date: 2022-03-03
tags:
 - 门徒
categories:
 - 门徒

---



## leetCode 86 分隔链表

分分大小排队站


```cpp
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode r1, r2;
        ListNode *p1 = &r1, *p2 = &r2, *p = head, *q;

        while (p) {
            q = p->next;

            if (p->val < x) {
                p->next = p1->next;
                p1->next = p;
                p1 = p;
            } else {
                p->next = p2->next;
                p2->next = p;
                p2 = p;
            }
            p = q;
        }

        p1->next = r2.next;
        return r1.next;
    }
};
```



## leetCode 138 复制带随机指针的链表

分身之后插身后


```cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        Node *p = head;
        Node *new_head;

        // 克隆，将新节点插入到原节点的下面
        while(p) {
            Node *q = new Node(p->val);
            q->random = p->random;
            q->next = p->next;
            p->next = q;
            p = q->next;
        }

        // 回到头节点
        p = head->next;
        while (p) {
            if (p->random) p->random = p->random->next;
            (p = p->next) && (p = p->next);
        }

        // 拆链表
        new_head = head->next;
        p = head;
        while(p) {
            Node* q = p->next;
            p->next = q->next;
            if (p->next) q->next = p->next->next;
            p = p->next;
        }

        return new_head;
    }
};
```


## leetCode 622 设计循环队列


```cpp

class MyCircularQueue {
public:
    vector<int> arr;
    int head, tail, count;

    MyCircularQueue(int k) : arr(k), head(0), tail(0), count(0) {}
    
    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        arr[tail] = value;
        tail++;

        tail = tail % arr.size();
        count++;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) return false;
        head++;
        head = head % arr.size();
        count--;
        return true;
    }
    
    int Front() {
        if (isEmpty()) return -1;
        return arr[head];
    }
    
    int Rear() {
        if (isEmpty()) return -1;
        int real_tail = (tail-1 + arr.size()) % arr.size();
        return arr[real_tail];
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == arr.size();
    }
};
```

## leetcode 641 设计循环双端队列

```cpp
class MyCircularDeque {
public:
    vector<int> arr;
    int head, tail, count;

    MyCircularDeque(int k) : arr(k), head(0), tail(0), count(0) {}

    bool insertFront(int value) {
        if (isFull()) return false;
        head--;
        head = (head + arr.size()) % arr.size();
        arr[head] = value;
        count++;
        return true;
    }
    
    bool insertLast(int value) {
        if (isFull()) return false;
        arr[tail] = value;
        tail++;

        tail = tail % arr.size();
        count++;
        return true;
    }
    
    bool deleteFront() {
        if (isEmpty()) return false;
        head++;
        head = head % arr.size();
        count--;
        return true;
    }
    
    bool deleteLast() {
        if (isEmpty()) return false;
        tail--;
        tail = (tail + arr.size()) % arr.size();
        count--;
        return true;
    }
    
    int getFront() {
        if (isEmpty()) return -1;
        return arr[head];
    }
    
    int getRear() {
        if (isEmpty()) return -1;
        int real_tail = (tail-1 + arr.size()) % arr.size();
        return arr[real_tail];
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == arr.size();
    }
};
```



## leetcode 1670 设计循环双端队列

```cpp
class Node {
public:
    int val;
    Node *next;
    Node *pre;
    Node(int val = 0, Node *next = nullptr, Node *pre = nullptr) : val(val), next(next), pre(pre) {}

    void insert_pre (Node *p) {
        p->pre = this->pre;
        p->next = this;
        if (this->pre) {
            this->pre->next = p;
        }
        this->pre = p;
    }
    void insert_next(Node *p) {
        p->next = this->next;
        p->pre = this;
        if (this->next) {
            this->next->pre = p;
        }
        this->next = p;
    }
    void delete_pre() {
        if (this->pre == nullptr) return;
        this->pre = this->pre->pre;
        if (this->pre) {
            this->pre->next = this;
        }
    }
    void delete_next() {
        if (this->next == nullptr) return;
        this->next = this->next->next;
        if (this->next) {
            this->next->pre = this;
        }
    }
};

class Queue {
    Node head, tail;
    int count;
public:
    Queue() : count(0) {
        head.next = &tail;
        tail.pre = &head;
    }
    void push_frout(int val) {
        head.insert_pre(new Node(val));
        count++;
    }
    void push_back(int val) {
        tail.insert_next(new Node(val));
        count++;
    }
    int pop_frout() {
        if (isEmpty()) return -1;
        int ret;
        ret = head.next->val;
        head.delete_next();
        count--;
        return ret;
    }
    int pop_back() {
        if (isEmpty()) return -1;
        int ret;
        ret = tail.pre->val;
        tail.delete_pre();
        count--;
        return ret;
    }
    int front() {
        return head.next->val;
    }
    int back() {
        return tail.pre->val;
    }
    bool isEmpty() {
        return count == 0;
    }
    int size() {
        return count;
    }
};

class FrontMiddleBackQueue {
    Queue q1,q2;
public:
    FrontMiddleBackQueue() {}

    void pushFront(int val) {
        q1.push_frout(val);
        update();
    }
    
    void pushMiddle(int val) {
        if (q1.size() > q2.size()) { 
            q2.push_frout(q1.pop_back());
        }
        q1.push_back(val);
        update();
    }

    void pushBack(int val) {
        q2.push_frout(val);
        update();
    }

    int popFront() {
        if (isEmpty()) return -1;
        int ret = q1.pop_frout();
        update();
        return ret;
    }
    
    int popMiddle() {
        if (isEmpty()) return -1;
        int ret = q1.pop_back();
        update();
        return ret;
    }
    
    int popBack() {
        if (isEmpty()) return -1;
        int ret = -1;
        if (q2.isEmpty()) {
            ret = q1.pop_back();
        } else {
            ret = q2.pop_back();
        }
        
        update();
        return ret;
    }

    bool isEmpty() {
        return (q1.size() == 0) && (q2.size() == 0);
    }

    void update() {
        if (q1.size() < q2.size() ){
            q1.push_back(q2.pop_frout());
        }
        if (q1.size() == q2.size() + 2) {
            q2.push_frout(q1.pop_back());
        }
        return;
    }
};
```



## leetcode 933 最近的请求次数

```cpp
class RecentCounter {
public:
    queue<int> q;
    RecentCounter() {}
    
    int ping(int t) {
        q.push(t);
        while(t-q.front() > 3000) {
            q.pop();
        }
        return q.size();
    }
};
```


## leetcode 面试题 17.09. 第 k 个数

```cpp
class Solution {
public:
    vector <int> q;
    int min(int a, int b) {
        return a > b ? b : a;
    }
    int getKthMagicNumber(int k) {
        q.push_back(1);
        int head3 = 0, head5 = 0, head7 = 0;
        while(q.size() < k) {
            int min_ans = q[head3] * 3;
            min_ans = min(min_ans, q[head5] * 5);
            min_ans = min(min_ans, q[head7] * 7);

            if (min_ans == q[head3] * 3) head3++;
            if (min_ans == q[head5] * 5) head5++;
            if (min_ans == q[head7] * 7) head7++;
            q.push_back(min_ans);
        }

        return q[k-1];
    }
};
```



## leetcode 859 亲密字符串

```cpp
class Solution {
public:
    bool has_repeat(string a, string b) {
        int count[26] = {0};
        for (int i = 0; a[i]; i++) {
            count[a[i] - 'a']++;
            if (count[a[i]-'a'] == 2) return true;
        }
        return false;
    }
    bool buddyStrings(string a, string b) {
        if (a.size() != b.size()) return false;

        if (a == b) return has_repeat(a, b);

        // 找两处不同的地方，然后看是否只有两处，切这两处是字母交换位置
        int i = 0, j;
        while (a[i] == b[i]) {
            i++;
        }
        j = i + 1;
        if (j > a.size()) return false;
        while (j < a.size() && a[j] == b[j]){
            j++;
        }
        // 只有一处差异
        if (j == a.size()) return false;
        // 发现两处不相等
        if (a[i] !=b[j] || a[j]!=b[i]) {
            return false;
        }
        j++;
        // 有三个以上的差异
        while(j < a.size()) {
            if (a[j] != b[j]) return false;
            j++;
        }
        return true;
    }
};
```


## leetcode 860 柠檬水找零

```cpp
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int count5 = 0, count10 = 0;
        for (int i = 0; i < bills.size(); i++) {
            switch (bills[i]) {
                case 5:
                    count5++;
                    break;
                case 10:
                    if (count5 > 0) {
                        count5--;
                        count10++;
                    }
                    else {
                        return false;
                    }
                    break;
                case 20:
                    if (count10 > 0 & count5 > 0) {
                        count5--;
                        count10--;
                    }
                    else if (count5 >= 3) {
                        count5 -= 3;
                    }
                    else {
                        return false;
                    }

                    break;

                default: 
                    break;
            }
        }
        return true;
    }
};
```


## leetcode 969 煎饼排序

```cpp
class Solution {
public:
    void reverse(vector<int> &arr, int n, vector <int> &ind) {
        for (int i = 0, j = n - 1; i < j; i++, j--) {
            swap(arr[i], arr[j]);
            ind[arr[i]] = i;
            ind[arr[j]] = j;
        }
    }
    vector<int> pancakeSort(vector<int>& arr) {
        vector <int> ind(arr.size() + 1);
        vector <int> ret;
        for (int i = 0; i < arr.size(); i++) {
            // 记录当前值的位置
            ind[arr[i]] = i;
        }
        for (int i = arr.size(); i >= 1; i--) {
            // 当前位置为正确位置则不翻转
            if (ind[i] != i) {
                // 翻转最大数字所在位置
                if (ind[i] != 0) {
                    ret.push_back(ind[i] + 1);
                    reverse(arr, ind[i] + 1, ind);
                }
                // 翻转当前数字长度
                if (i != 1) {
                    ret.push_back(i);
                    reverse(arr, i, ind);
                }
            }
        }
        return ret;
    }
};
```




