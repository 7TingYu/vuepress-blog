#include <stdio.h>
#include <string.h>

int n, m, s, arr[105][105];

int main() {
    memset(arr, 0x3F, sizeof(arr));
    scanf("%d%d%d", &n, &m, &s);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);

        if (arr[a][b] == 0 || arr[a][b] > c)
        {
            arr[a][b] = arr[b][a] = c;
        }
    }

    for (int i = 1; i <= n; i++) {
        arr[i][i] = 0;
    }

    // 最外层中转
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                if (arr[j][k] > arr[j][i] + arr[i][k]) {
                    arr[j][k] = arr[j][i] + arr[i][k];
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d -> %d = %d\n", s, i, arr[s][i]);
    }

    for (int i = 1; i <= n; i++) {
        printf("[%d]: ", i);
        for (int j = 1; j <= n; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}