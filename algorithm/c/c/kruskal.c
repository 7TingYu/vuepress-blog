#include <stdio.h>

typedef struct edge {
    // s 起点， e 终点，v 值
    int s, e, v;
} edge;

edge edg[105];
// 点数，边数，最小生成树的总权值，选出边的数量，并查集
int n, m, ans, cnt, my_union[105];

void init_union(){
    for (int i = 1; i <= n; i++) {
        my_union[i] = i;
    }
}

// 冒泡排序
void sort() {
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - i - 1; j++) {
            if (edg[j].v > edg[j + 1].v) {
                int a, b, c;
                a = edg[j].s;
                b = edg[j].e;
                c = edg[j].v;

                edg[j].s = edg[j + 1].s;
                edg[j].e = edg[j + 1].e;
                edg[j].v = edg[j + 1].v;

                edg[j + 1].s = a;
                edg[j + 1].e = b;
                edg[j + 1].v = c;
            }
        }
    }
}

int find_fa(int x) {
    if (my_union[x] == x) {
        return x;
    }
    return my_union[x] = find_fa(my_union[x]);
}

int main () {
    scanf("%d%d", &n, &m);
    init_union();

    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        edg[i].s = a, edg[i].e = b, edg[i].v = c;
    }

    sort();

    cnt = 1;
    for (int i = 0; i < m; i++) {
        int s = edg[i].s, e = edg[i].e;
        int fs = find_fa(s), fe = find_fa(e);
        if (fs != fe) {
            ans += edg[i].v;
            cnt++;
            my_union[fs] = fe;

            if (cnt == n) {
                break;
            }
        }
    }

    if (cnt == n) {
        printf("%d\n", ans);
    } else {
        printf("-1\n");
    }

    return 0;
}