/**
 * 1. 存图 => arr 矩阵 => 按行遍历
 * 2. ans 数组 => INI_MAX
 *    mark 数组
 * 3. 找边 => 遍历
 */

#include <stdio.h>
#include <string.h>

int n, m, s, arr[1005][1005], ans[1005], mark[1005];

int main() {
    memset(ans, 0x3F, sizeof(ans));
    scanf("%d%d%d", &n, &m, &s);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        
        if (arr[a][b] == 0 || arr[a][b] > c) {
            arr[a][b] = arr[b][a] = c;
        }
    }

    ans[s] = 0;
    for (int i = 0; i < n; i++) {
        int ind = 0;
        for (int j = 1; j <= n; j++) {
            if (mark[j] == 0 && ans[j] != 0x3F3F3F && (ind == 0 || ans[j] < ans[ind])) {
                ind = j;
            }
        }

        if (ind == 0) break;

        mark[ind] = 1;
        for (int j = 1; j <= n; j++) {
            if (arr[ind][j] && ans[j] > ans[ind] + arr[ind][j]) {
                ans[j] = ans[ind] + arr[ind][j];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d -> %d = %d\n", s, i, ans[i]);
    }

    return 0;
}