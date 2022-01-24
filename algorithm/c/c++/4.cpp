#include <iostream>
#include <algorithm>
using namespace std;

class node {
    public:
        int x, y;

        bool operator<(const node &b) const{
            node a(*this);
            if (a.x == b.x) {
                return a.y < b.y;
            }
            return a.x < b.x;
        }
};


int main() {
    int n;
    node num[105];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> num[i].x >> num[i].y;
    }

    sort(num, num + n);
    for (int i = 0; i < n; i++) {
        cout << "[" << num[i].x << ", " << num[i].y << "]" << endl;
    }

    return 0;
}
