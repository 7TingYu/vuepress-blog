struct Node
{
    int x, y;
    int idx;
};
bool cmp(Node a, Node b)
{
    return a.x + a.y < b.x + b.y;
}
class Solution
{
public:
    vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k)
    {
        Heap<Node> h{cmp};
        for (int i = 0; i < nums1.size(); i++)
        {
            h.push(Node{nums1[i], nums2[0], 0});
        }
        vector<vector<int>> ans;
        for (int i = 0; i < k; i++)
        {
            if (h.empty())
                break;
            Node node = h.pop();
            ans.push_back(vector<int>{node.x, node.y});
            node.idx++;
            if (node.idx == nums2.size())
                continue;
            node.y = nums2[node.idx];
            h.push(node);
        }
        return ans;
    }
};