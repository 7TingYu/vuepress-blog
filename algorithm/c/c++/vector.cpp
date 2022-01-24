#include <iostream>
#include <vector>

using namespace std;

struct node {
    int a, b;
};


int main() {
    vector<int> v;
    int cnt = 0;
    for (int i = 0; i < 10000000; i++) {
        v.push_back(i);
        if (cnt != v.capacity()) {
            cnt = v.capacity();
            cout << i << " " << cnt << endl;
        }
    }

    // vector<vector<int> > v;
    // v.push_back(vector<int>(5, 1));
    // v.push_back(vector<int>(3, 8));
    // v.push_back(vector<int>(10, 7));
    // v[1].push_back(99999);
    // for (int i = 0; i < v.size(); i++) {
    //     for (int j = 0; j < v[i].size(); j++) {
    //         cout << v[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    // vector<vector<int>> v2(5, vector<int>(6, -3));
    // for (int i = 0; i < v2.size(); i++) {
    //     for (int j = 0; j < v2[i].size(); j++) {
    //         cout << v2[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    // vector<int> v(10, 0xEFEFEF);
    // v[8] = 90;
    // v.resize(5, 10);
    // for (int i = 0; i < v.size(); i++) {
    //     cout << v[i] << ' ';
    // }
    // cout << endl;

    // vector<node> v;
    // node t;
    // t.a = 5;
    // t.b = 6;
    // v.push_back(t);
    // v.push_back((node){2, -5});
    // v.push_back((node){0, 9});
    // for (int i = 0; i < v.size(); i++) {
    //     cout << "[" << v[i].a << ", " << v[i].b << "]" << endl;
    // }

    // vector<string> v;
    // v.push_back("12345");
    // v.push_back("haha");
    // v.push_back("???");
    // cout << v.size() << endl;
    // for (int i = 0; i < v.size(); i++) {
    //     cout << v[i] << endl;
    // }

    // vector<int> v;
    // v.push_back(7);
    // v.push_back(3);
    // v.push_back(6);
    // v.push_back(999);

    // for (int i = 0; i < v.size(); i++) {
    //     cout << v[i] << ' ';
    // }
    // cout << endl;

    // v[3] = -5;
    // cout << v[3] << endl;

    // v[2] = 31;
    // v.pop_back();

    // for (int i = 0; i < v.size(); i++)
    // {
    //     cout << v[i] << ' ';
    // }
    // cout << endl;

    return 0;
}