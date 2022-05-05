class Solution
{
public:
    int lastStoneWeight(vector<int> &stones)
    {
        Heap<int> h{stones, greater<int>()};
        while (h.size() > 1)
        {
            int x = h.pop();
            int y = h.pop();
            if (x != y)
                h.push(x - y);
        }
        return h.size() == 1 ? h.top() : 0;
    }
};