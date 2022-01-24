#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

bool cmp(const int &a, const int &b) {
    return a > b;
}

int main() {
    int n, num[105];

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }

    sort(num, num + n, cmp);
    for (int i = 0; i < n; i++) {
        cout << num[i] << " ";
    }
    cout << endl;

    // char str[105];
    // cin >> str;
    // sort(str, str + strlen(str));
    // cout << str << endl;

    return 0;
}