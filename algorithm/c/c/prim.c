/**
 * 1. 存图 => arr 矩阵 => 按行遍历
 * 2. 外部，内部 => mark 数组
 * 3. 找边 => 遍历
 */

#include <stdio.h>

// 点数，边数，邻接矩阵，选出边的数量，最小生成树的总权值，标记数组[标记内部点]
int n, m, arr[105][105], cnt, ans, mark[105];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if (arr[a][b] == 0 || arr[a][b] > c) {
            arr[a][b] = arr[b][a] = c;
        }
    }

    cnt = 1;
    mark[1] = 1;
    while(1) {
        // 当前最小边的权值，这条边连接的点
        int mmin = 999999999, mind;
        // j 内部点， k 外部点
        for (int j = 1; j <= n; j++) {
            if (mark[j] == 1) {
                for (int k = 1; k <= n; k++) {
                    // 边需要存在
                    if (mark[k] == 0 && mmin > arr[j][k] && arr[j][k]) {
                        mmin = arr[j][k];
                        mind = k;
                    }
                }
            }
        }
        if (mind == 0) break;
        ans += mmin;
        mark[mind] = 1;
        cnt ++;

        if (cnt == n) break;
    }

    if (cnt = n) {
        printf("%d\n", ans);
    } else {
        printf("-1\n");
    }


    return 0;
}
