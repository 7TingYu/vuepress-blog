#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main() {
    string s = "0123456789";
    cout << s << " size = " << s.size() << endl;

    s[5] = '\0';
    cout << s << " size = " << s.size() << endl;

    char str[20] = "0123456789";
    cout << str << " size = " << strlen(str) << endl;

    str[5] = '\0';
    cout << str << " size = " << strlen(str) << endl;

    // string s;
    // s = "abcdefg";
    // string a;
    // a = s;
    // string b = a + s;

    // cout << s << endl << a << endl << b << endl;

    // b[5] = '?';
    // b[8] = '!';
    // cout << b << endl;

    // if (b.find("bcd", 3) != string::npos) {
    //     cout << "bcd in b at ind = " << b.find("cde") << endl;
    // } else {
    //     cout << "not find bcd in b" << endl;
    // }

    // string c = b.substr(3, 6);
    // cout << c << endl;

    // c = c.insert(1, "!!!!!");
    // cout << c << endl;

    // c.replace(2, 6, "()");
    // cout << c << endl;

    // string d(10, '?');
    // cout << d << endl;
    
    return 0;
}