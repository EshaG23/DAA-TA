#include <stdio.h>
int main() {
    int n, m;
    printf("Enter rows and columns: ");
    scanf("%d %d", &n, &m);
    int a[50][50];
    printf("Enter matrix elements:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    int found = 0;
    for (int i = 0; i < n; i++) {
        // find min in row i
        int minVal = a[i][0], col = 0;
        for (int j = 1; j < m; j++) {
            if (a[i][j] < minVal) {
                minVal = a[i][j];
                col = j;
            }
        }
        // check if this min is also max in its column
        int isMax = 1;
        for (int r = 0; r < n; r++) {
            if (a[r][col] > minVal) {
                isMax = 0;
                break;
            }
        }
        if (isMax) {
            printf("Saddle Point = %d at position (%d,%d)\n", minVal, i, col);
            found = 1;
        }
    }
    if (!found) printf("No Saddle Point in the matrix.\n");
    return 0;
}