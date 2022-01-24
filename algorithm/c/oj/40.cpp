#include <iostream>
#include <vector>

using namespace std;

long arr[105];

long func(int n)
{
    if (arr[n])
        return arr[n];

    long sum = func(n - 2) + func(n - 3);
    arr[n] = sum;

    return sum;
};

int main()
{
    int n;

    scanf("%d", &n);

    arr[1] = 0;
    arr[2] = 1;
    arr[3] = 1;
    arr[4] = 1;

    printf("%ld\n", func(n));

    return 0;
}