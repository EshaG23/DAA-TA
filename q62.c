#include <stdio.h>
#define INF 999999
int main() {
    int n;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    int cost[20][20];
    printf("Enter adjacency matrix (use %d for no edge):\n", INF);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }
    int src, dest;
    printf("Enter source node and destination node: ");
    scanf("%d %d", &src, &dest);
    int direct = cost[src][dest];
    int best = direct;
    int steiner = -1;
    // check all possible intermediate nodes
    for (int k = 0; k < n; k++) {
        if (k != src && k != dest) {
            if (cost[src][k] != INF && cost[k][dest] != INF) {
                int via = cost[src][k] + cost[k][dest];
                if (via < best) {
                    best = via;
                    steiner = k;
                }
            }
        }
    }
    printf("Direct cost from %d -> %d = %d\n", src, dest, direct);

    if (steiner != -1) {
        printf("Better path found via node %d with cost = %d\n", steiner, best);
        printf("Node %d acts as a Steiner Point.\n", steiner);
    } else {
        printf("Direct path is the best. No Steiner Point needed.\n");
    }
    return 0;
}
