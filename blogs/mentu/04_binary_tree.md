---
title: 门徒 4. 二叉树
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





### LeetCode 589.N 叉树的前序遍历

```cpp
class Solution
{
public:
    void _preorder(Node *root, vector<int> &ans)
    {
        if (root == nullptr)
            return;
        // 根
        ans.push_back(root->val);

        // 遍历所有children
        for (int i = 0; i < root->children.size(); i++)
        {
            _preorder(root->children[i], ans);
        }
    }

    vector<int> preorder(Node *root)
    {
        vector<int> ans;
        _preorder(root, ans);
        return ans;
    }
};
```


### LeetCode 226.翻转二叉树

```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;

        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};
```





### LeetCode 102.二叉树的层序遍历

```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == nullptr) return  ans;
        queue<TreeNode*> q;
        q.push(root);
        // int depth = 1;
        while (!q.empty()) {
            int qSize = q.size();
            ans.push_back(vector<int> ());
            for (int i = 0; i < qSize; i++) {
                TreeNode *node = q.front();
                q.pop();
                ans.back().push_back(node-> val);
                // cout << node->val << " " << depth << endl;
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
            // depth++;
        }
        return ans;
    }
};
```


```cpp
class Solution {
public:
    void _levelOrder(TreeNode *root, int depth, vector<vector<int>> &ans)
    {
        if (!root)
            return;

        if (depth == ans.size())
            ans.push_back(vector<int>());

        ans[depth].push_back(root->val);
        _levelOrder(root->left, depth + 1, ans);
        _levelOrder(root->right, depth + 1, ans);
    }

    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> ans;
        if (root == nullptr)
            return ans;

        _levelOrder(root, 0, ans);

        return ans;
    }
};
```



### LeetCode 107.二叉树的层序遍历 II


```cpp
class Solution {
public:
    void _levelOrder(TreeNode *root, int depth, vector<vector<int>> &ans)
    {
        if (!root)
            return;

        if (depth == ans.size())
            ans.push_back(vector<int>());

        ans[depth].push_back(root->val);
        _levelOrder(root->left, depth + 1, ans);
        _levelOrder(root->right, depth + 1, ans);
    }

    vector<vector<int>> levelOrderBottom(TreeNode *root)
    {
        vector<vector<int>> ans;
        if (root == nullptr)
            return ans;

        _levelOrder(root, 0, ans);

        for (int i = 0; i < ans.size() / 2; i++)
        {
            swap(ans[i], ans[ans.size() - i - 1]);
        }

        return ans;
    }
};
```




### LeetCode 103.二叉树的锯齿形层序遍历


```cpp
class Solution
{
public:
    void _levelOrder(TreeNode *root, int depth, vector<vector<int>> &ans)
    {
        if (!root)
            return;

        if (depth == ans.size())
            ans.push_back(vector<int>());

        ans[depth].push_back(root->val);
        _levelOrder(root->left, depth + 1, ans);
        _levelOrder(root->right, depth + 1, ans);
    }

    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int>> ans;
        if (root == nullptr)
            return ans;

        _levelOrder(root, 0, ans);

        for (int i = 1; i < ans.size(); i += 2)
        {
            for (int j = 0; j < ans[i].size() / 2; j++)
            {
                swap(ans[i][j], ans[i][ans[i].size() - j - 1]);
            }
        }

        return ans;
    }
};
```




### LeetCode 110.平衡二叉树


```cpp
class Solution {
public:
    int getHight(TreeNode* root) {
        if (root == nullptr) return 0;
        int l = getHight(root->left);
        int r = getHight(root->right);
        // cout << root->val << " " << max(l, r) + 1 << endl;
        if (l == -100 || r == -100) return -100;
        if (abs(l - r) > 1) return -100;
        return max(l, r) + 1;
    }

    bool isBalanced(TreeNode* root) {
        return getHight(root) != -100;
    }
};
```






### LeetCode 112.路径总和


```cpp
class Solution
{
public:
    bool hasPathSum(TreeNode *root, int targetSum)
    {
        if (!root)
            return false;

        // 叶子节点
        if (!root->left && !root->right)
            return root->val == targetSum;

        bool l = hasPathSum(root->left, targetSum - root->val);
        bool r = hasPathSum(root->right, targetSum - root->val);

        return l || r;
    }
};
```



### LeetCode 105.从前序与中序遍历序列构造二叉树

> 困难点如何算左右子树大小

```cpp
class Solution {
public:
    TreeNode* build(vector<int>& preorder, int preL, int preR, vector<int>& inorder, int inL, int inR) {
        if (preL > preR || inL > inR) return nullptr;
        TreeNode *root = new TreeNode(preorder[preL]);
        
        int idx = inL;
        for (; idx <= inR; idx++) {
            if (inorder[idx] == root->val) break;
        }
        root->left = build(preorder, preL + 1, preL + (idx - inL), inorder, inL, idx - 1);
        root->right = build(preorder, preL + (idx - inL) + 1, preR, inorder, idx + 1, inR);
        
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return build(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }
};
```




### LeetCode 222.完全二叉树的节点个数


```cpp
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};
```

```cpp
class Solution {
public:
    int getHeight(TreeNode* root) {
        TreeNode *p = root;
        int height = 0;
        while (p) {
            p = p->left;
            height++;
        }
        return height;
    }

    int countNodes(TreeNode* root) {
        if (!root) return 0;
        
        int l = getHeight(root->left);
        int r = getHeight(root->right);
        if (l > r) return countNodes(root->left) + (1 << r);
        else return countNodes(root->right) + (1 << l);
    }
};
```


