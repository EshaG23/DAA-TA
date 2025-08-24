#include <stdio.h>
#define MAXN 200000

int parent_[MAXN], rank_[MAXN];

int find_set(int v) {
    if (parent_[v] == v) return v;
    parent_[v] = find_set(parent_[v]);
    return parent_[v];
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b) return;
    if (rank_[a] < rank_[b]) { int t = a; a = b; b = t; }
    parent_[b] = a;
    if (rank_[a] == rank_[b]) rank_[a]++;
}

int main(void) {
    int n, m;
    
    printf("Enter number of vertices (n) and edges (m): ");
    if (scanf("%d %d", &n, &m) != 2) return 0;

    if (n > MAXN) {
        fprintf(stderr, "Error: Increase MAXN.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        parent_[i] = i;
        rank_[i] = 0;
    }

    printf("Enter %d edges (u v) one per line:\n", m);
    int u, v;
    for (int i = 0; i < m; i++) {
        if (scanf("%d %d", &u, &v) != 2) return 0;
        if (u == v) continue;         
        if (u < 0 || u >= n || v < 0 || v >= n) {
            fprintf(stderr, "Error: Vertex out of range.\n");
            return 1;
        }
        union_sets(u, v);
    }

    if (m < n - 1) {
        printf("Output: -1 (Not enough edges to connect the graph)\n");
        return 0;
    }

    int components = 0;
    for (int i = 0; i < n; i++) {
        if (find_set(i) == i) components++;
    }

    printf("Minimum operations required = %d\n", components - 1);
    return 0;
}
