#include <iostream>
#include <queue>

using namespace std;

int main() {
    queue<long long> r;
    int n;
    long long sum = 0, nr = 1;
    cin >> n;

    for (int i = 0; i < n; i++) {
        sum += nr;
        r.push(nr);
        if (r.size() == 3) {
            nr += r.front();
            r.pop();
        }
    }

    cout << nr << endl;

    while (!r.empty()) {
        cout << r.front() << " ";
        r.pop();
    }
    cout << endl;

    cout << sum << endl;
}