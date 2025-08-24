#include <stdio.h>
#include <stdlib.h>
typedef struct { int *a; int sz, cap; } Vec;
static void vec_init(Vec *v){ v->a=NULL; v->sz=0; v->cap=0; }
static void vec_push(Vec *v, int x)
{
    if(v->sz==v->cap)
    {
        v->cap = v->cap ? v->cap*2 : 4;
        v->a = (int*)realloc(v->a, v->cap*sizeof(int));
    }
    v->a[v->sz++] = x;
}
int n;
int *X, *Y;
Vec *adj;
int *vis;
void dfs(int u)
{
    vis[u] = 1;
    for(int i=0;i<adj[u].sz;i++)
    {
        int v = adj[u].a[i];
        if(!vis[v]) dfs(v);
    }
}
int main(void)
{
    printf("Enter number of stones N:\n");
    if(scanf("%d", &n) != 1)
    {
        printf("Invalid input for N\n");
        return 1;
    }
    X = (int*)malloc(n*sizeof(int));
    Y = (int*)malloc(n*sizeof(int));
    adj = (Vec*)malloc(n*sizeof(Vec));
    vis = (int*)calloc(n, sizeof(int));
    for(int i=0;i<n;i++) vec_init(&adj[i]);

    printf("Enter %d coordinates (xi yi) one per line:\n", n);
    for(int i=0;i<n;i++)
    {
        if(scanf("%d %d", &X[i], &Y[i]) != 2)
        {
            printf("Invalid coordinate on line %d\n", i+1);
            return 1;
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(X[i]==X[j] || Y[i]==Y[j])
            {
                vec_push(&adj[i], j);
                vec_push(&adj[j], i);
            }
        }
    }
    int components = 0;
    for(int i=0;i<n;i++)
    {
        if(!vis[i])
        {
            components++;
            dfs(i);
        }
    }
    int result = n - components;
    printf("Maximum stones that can be removed: %d\n", result);
    for(int i=0;i<n;i++) free(adj[i].a);
    free(adj); free(vis); free(X); free(Y);
    return 0;
}