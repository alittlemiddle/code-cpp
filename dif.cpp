const int N=1e6+11;
int pri[N];
void sang()
{
    for(int i=1; i<=N; i++)
    {
        pri[i]=i;
    }
    for(int i=2; i<=sqrt(N); i++)
    {
        if(pri[i]==i)
        {
            for(int j=i*i; j<=N; j+=i)
            {
                if(pri[j]==j) pri[j]=i;
            }
        }
    }
}




const int N = 1e6 + 6;
int prime[N + 1];
vector<int> pr;
void sieve()
{
    for (int i = 2; i <= N; ++i)
    {
        if (prime[i] == 0)
        {
            prime[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] <= N; ++j)
        {
            prime[i * pr[j]] = pr[j];
            if (pr[j] == prime[i])
            {
                break;
            }
        }
    }
}



const int N=1e5+11;
int pa[N];                              
int lead(int v) {
    return v == pa[v] ? v : pa[v] = lead(pa[v]);
}
void join(int a, int b) {
    a = lead(a);
    b = lead(b);
    if (a != b) {
        //if (sz[a] < sz[b]) swap(a, b);
        pa[b] = a;
    }
}


int n, u, v, up[N][19], h[N], q, x;
vector<int> adj[N];
void dfs(int u, int pa)
{
    up[u][0]=pa;
    for(int i=1; i<=18; i++)  up[u][i]=up[up[u][i-1]][i-1];
    for(auto v:adj[u])
    {
        if(v!=pa)
        {
            h[v]=h[u]+1;
            dfs(v, u);
        }
    }
}
int jump(int u, int k)
{
    for(int i=18; i>=0; i--)
        if(k >> i & 1)
        {
            u = up[u][i];
        }
    return u;
}
int lca(int u, int v)
{
    if(h[u]>h[v]) swap(u, v);
    v = jump(v, h[v]-h[u]);
    if(u==v) return u;
    for (int i = 18; i >= 0; i--)
        if (up[u][i] != up[v][i])
        {
            u = up[u][i];
            v = up[v][i];
        }

    return up[u][0];
}




int po(int a,int b)
{
    int r=1;
    while (b>0)
    {
        if(b%2==1) r=r*a%mod;
        b/=2;
        a=a*a%mod;
    }
    return r;
}
