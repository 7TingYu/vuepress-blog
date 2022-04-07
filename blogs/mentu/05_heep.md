---
title: 门徒 5. 堆（Heap）与优先队列
date: 2022-04-6
tags:
 - 门徒
categories:
 - 门徒

---



### LeetCode 144.二叉树的前序遍历

```cpp
class Solution
{
public:
    void preorder(TreeNode *root, vector<int> &ans)
    {
        if (root == nullptr)
            return;
        // 根
        ans.push_back(root->val);
        // 左子树
        preorder(root->left, ans);
        // 右子树
        preorder(root->right, ans);
    }

    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> ans;
        preorder(root, ans);
        return ans;
    }
};
```
