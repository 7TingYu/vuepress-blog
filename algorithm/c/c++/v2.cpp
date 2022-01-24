#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v;
    v.push_back(9);
    v.push_back(99);
    v.push_back(103);
    v.push_back(133);
    v.push_back(12);
    v.push_back(77);

    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;

    for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    for (auto x: v) {
        cout << x << " ";
    }
    cout << endl;

    vector<int> v2 = {99, 72, 36, 10, 55};
    for (int i = 0; i < v2.size(); i++) {
        cout << v2[i] << " ";
    }
    cout << endl;

    return 0;
}