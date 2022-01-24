#include <stdio.h>

int n, m, arr[105][105], in_degree[105], mark[105], ans[105];

int main() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        arr[a][b]++;
        in_degree[b]++;
    }

    for (int i = 0; i < n; i++) {
        int ind = 0;
        for (int j = 1; j <= n; j++) {
            if (in_degree[j] == 0 && mark[j] == 0) {
                ind = j;
                break;
            }
        }

        if (ind == 0) {
            break;
        }

        ans[i] = ind;
        mark[ind] = 1;
        for (int j = 1; j <= n; j++) {
            in_degree[j] -= arr[ind][j];
        }
    }

    if (ans[n - 1] == 0) {
        printf("-1\n");
    } else {
        for (int i = 0; i < n; i++) {
            if (i) printf("-");
            printf("%d", ans[i]);
        }
        printf("\n");
    }

    return 0;
}