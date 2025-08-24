#include <stdio.h>
#include <stdlib.h>
typedef struct { int *a; int sz, cap; } Vec;
typedef struct { int u, v; } Edge;
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
static int edge_cmp(const void *A, const void *B)
{
    const Edge *a = (const Edge*)A, *b = (const Edge*)B;
    if(a->u != b->u) return a->u - b->u;
    return a->v - b->v;
}
int n, m;
Vec *g;
int *tin, *low, *vis;
int timer = 0;
Edge *bridges;
int bc = 0, bcap = 0;
static void add_bridge(int u, int v)
{
    if(u > v){ int t=u; u=v; v=t; }
    if(bc == bcap)
    {
        bcap = bcap ? bcap*2 : 8;
        bridges = (Edge*)realloc(bridges, bcap*sizeof(Edge));
    }
    bridges[bc++] = (Edge){u,v};
}
void dfs(int u, int p)
{
    vis[u] = 1;
    tin[u] = low[u] = ++timer;
    for(int i=0;i<g[u].sz;i++)
    {
        int v = g[u].a[i];
        if(v == p) continue;
        if(vis[v])
        {
            if(low[u] > tin[v]) low[u] = tin[v];
        } 
        else 
        {
            dfs(v, u);
            if(low[u] > low[v]) low[u] = low[v];
            if(low[v] > tin[u])
            {
                add_bridge(u, v);
            }
        }
    }
}
int main(void)
{
    printf("Enter number of nodes n and number of edges m (nodes are 1..n):\n");
    if(scanf("%d %d", &n, &m) != 2)
    {
        printf("Invalid input. Expected two integers: n m\n");
        return 1;
    }
    g   = (Vec*)malloc((n+1)*sizeof(Vec));
    tin = (int*)calloc(n+1, sizeof(int));
    low = (int*)calloc(n+1, sizeof(int));
    vis = (int*)calloc(n+1, sizeof(int));
    for(int i=1;i<=n;i++) vec_init(&g[i]);
    printf("Enter %d edges (u v) one per line using 1-based node indices:\n", m);
    for(int i=0;i<m;i++)
    {
        int u,v;
        if(scanf("%d %d", &u, &v) != 2)
        {
            printf("Invalid edge on line %d. Expected: u v\n", i+1);
            return 1;
        }
        if(u<1 || u>n || v<1 || v>n)
        {
            printf("Edge (%d, %d) out of range. Nodes must be in [1, %d]\n", u, v, n);
            return 1;
        }
        vec_push(&g[u], v);
        vec_push(&g[v], u);
    }
    for(int i=1;i<=n;i++)
    {
        if(!vis[i] && g[i].sz>0)
        {
            dfs(i, -1);
        }
    }
    Edge *core = NULL;
    int cc = 0, ccap = 0;
    for(int i=0;i<bc;i++)
    {
        int u = bridges[i].u, v = bridges[i].v;
        if(g[u].sz > 1 && g[v].sz > 1)
        {
            if(cc == ccap)
            {
                ccap = ccap ? ccap*2 : 8;
                core = (Edge*)realloc(core, ccap*sizeof(Edge));
            }
            core[cc++] = bridges[i];
        }
    }
    if(cc)
    {
        qsort(core, cc, sizeof(Edge), edge_cmp);
        printf("\nBridges found (excluding leaf-edges): %d\n", cc);
        for(int i=0;i<cc;i++)
        {
            printf("%d %d\n", core[i].u, core[i].v);
        }
    } 
    else 
    {
        printf("\nNo bridges (after excluding leaf-edges)\n");
    }
    for(int i=1;i<=n;i++) free(g[i].a);
    free(g); free(tin); free(low); free(vis); free(bridges); free(core);
    return 0;
}