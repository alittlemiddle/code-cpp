int n, k, sz[N], vit[N], dp[N], mx;
ll ans;
vector<int> adj[N];
int subtree(int u, int pa)
{
    sz[u] = 1;
    for (auto v: adj[u])
    {
        if (v != pa && !vit[v])
        {
            sz[u] += subtree(v, u);
        }
    }
    return sz[u];
}
int cen(int u, int pa, int n)
{
    for (auto i: adj[u])
    {
        if (i != pa && !vit[i] && sz[i] > n/2)
        {
            return cen(i, u, n);
        }
    }
    return u;
}
void dfs(int u, int pa, int d, int ch)
{
    if(d > k) return;
    if(ch)
    {
        // update
    }
    else
    {
        // calc
    }
    for(auto v: adj[u])
    {
        if(v != pa && !vit[v]) dfs(v, u, d+1, ch);
    }
}
void calc(int u)
{
    subtree(u, 0);
    int c = cen(u, 0, sz[u]);
    vit[c] = 1;
    for(auto u: adj[c])
    {
        if (!vit[u])
        {
            dfs(u, c, 1, 0);
            dfs(u, c, 1, 1);
        }
    }
    //reset
    for (auto v: adj[c])
    {
        if (!vit[v])
        {
            calc(v);
        }
    }
}
