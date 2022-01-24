#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class my_string
{
private:
    int len;
    char *str;

public:
    my_string() : len(0), str(NULL) {}
    my_string(const char *str){
        my_string(strlen(str), str);
    } 
    my_string(int len, const char s[])
    {
        if (this->len)
        {
            free(this->str);
        }
        this->len = len;
        this->str = (char *)calloc(strlen(s) + 1, 1);
        memcpy(this->str, s, strlen(s));

        cout << this->str << endl;
    }
    my_string(const my_string &b)
    {
        my_string(b.len, b.str);
    }
    ~my_string() {}

    friend istream &operator>>(istream &in, my_string &a);
    friend istream &operator<<(istream &in, my_string &a);
    friend ostream &operator<<(ostream &out, my_string &a);
    friend ostream &operator>>(ostream &out, my_string &a);
};

istream &operator>>(istream &in, my_string &a)
{
    if (a.len != 0)
    {
        free(a.str);
    }
    a.str = (char *)calloc(1005, 1);
    in >> a.str;
    a.len = strlen(a.str);
    return in;
};

istream &operator<<(istream &in, my_string &a){
    return operator>>(in, a);
};

ostream &operator<<(ostream &out, my_string &a)
{
    if (a.len != 0)
    {
        out << a.str;
    }
    return out;
}

ostream &operator>>(ostream &out, my_string &a)
{
    return operator<<(out, a);
}

int main()
{
    my_string s;
    cin << s;
    cout << s << endl;

    // my_string s = "abc";

    // cout << s << endl;

    my_string b = s;
    cout << b << endl;

    return 0;
}