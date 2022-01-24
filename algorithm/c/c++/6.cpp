#include <iostream>
using namespace std;

class node
{
private:
    int x, y;

public:
    void change_x(int val)
    {
        this->x = val;
    }
    void change_y(int val)
    {
        this->y = val;
    }
    void show_x()
    {
        cout << this->x << endl;
    }
    void show_y()
    {
        cout << this->y << endl;
    }
    void hello();

    friend void my_friend(node &t);
};

void node::hello()
{
    cout << "hello" << endl;
}

void my_friend(node &t)
{
    cout << "friend" << endl;
    cout << t.x << " " << t.y << endl;
}

int main()
{
    node n;
    n.change_x(2);
    n.change_y(102);

    n.show_x();
    n.show_y();

    n.hello();
    my_friend(n);

    return 0;
}
