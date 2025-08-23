#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ACCOUNTS 100
#define MAX_EMAILS 100
#define MAX_LEN 100
// adjacency matrix for email connections
int adj[MAX_ACCOUNTS * MAX_EMAILS][MAX_ACCOUNTS * MAX_EMAILS];
int visited[MAX_ACCOUNTS * MAX_EMAILS];
char emails[MAX_ACCOUNTS * MAX_EMAILS][MAX_LEN];
char names[MAX_ACCOUNTS][MAX_LEN];
int emailCount = 0;
// find index of email or add if not exists
int getEmailIndex(char *email) {
    for (int i = 0; i < emailCount; i++) {
        if (strcmp(emails[i], email) == 0) return i;
    }
    strcpy(emails[emailCount], email);
    return emailCount++;
}
// DFS to collect connected emails
void dfs(int node, int comp[], int *size) {
    visited[node] = 1;
    comp[(*size)++] = node;
    for (int i = 0; i < emailCount; i++) {
        if (adj[node][i] && !visited[i]) {
            dfs(i, comp, size);
        }
    }
}
int main() {
    int N = 6;  // number of accounts
    char accounts[6][3][MAX_LEN] = {
        {"Esha", "esha123@mail.com", "esha@mail.com"},
        {"Disha", "disha@mail.com", "disha123@mail.com"},
        {"Esha", "esha@mail.com", "eshaNY@mail.com"},
        {"Dilip", "dilip@mail.com", ""},
        {"Sabari", "sabari@mail.com", ""},
        {"Esha", "esha99@mail.com", ""}
    };
    // Step 1: build graph
    for (int i = 0; i < N; i++) {
        strcpy(names[i], accounts[i][0]);
        int first = -1;
        for (int j = 1; j < 3 && accounts[i][j][0] != '\0'; j++) {
            int idx = getEmailIndex(accounts[i][j]);
            if (first == -1) first = idx;
            adj[first][idx] = adj[idx][first] = 1; // connect
        }
    }
    // Step 2: DFS to find connected components
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < emailCount; i++) {
        if (!visited[i]) {
            int comp[100], size = 0;
            dfs(i, comp, &size);
            // Step 3: print result (name + emails)
            printf("[%s", names[0]);  // name (just take first one, same per problem)
            for (int k = 0; k < size; k++) {
                printf(", %s", emails[comp[k]]);
            }
            printf("]\n");
        }
    }
    return 0;
}