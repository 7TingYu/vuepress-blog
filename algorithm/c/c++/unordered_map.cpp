#include <iostream>
#include <map>
#include <string>

using namespace std;

// struct node {
//     int a, b;
//     bool operator< (const node &b) {
//         return this->a < b.a;
//     }
// };

int main() {
    map<int, string> m;
    m.insert({86, "+-+"});
    m[12] = ">-<";
    m[77] = "-_-";
    m[49] = "^_^";
    m[2] = "@_@";

    if (m.count(49)) {
        cout << "49 yes value = " << m[49] << endl;
    }
    cout << m.size() << endl;

    m[49] = '>';
    cout << "key = 49 value = " << m[49] << endl;

    m.erase(12);
    if (!m.count(12)) {
        cout << "12 no " << endl;
    }

    for (auto &x : m) {
        cout << x.first << " " << x.second << endl;
    }

    return 0;
}