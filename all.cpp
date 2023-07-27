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
/////////////////////////////////////////////////////////////
int d1[N], d2[N], tmp[N];
void manacher1(string s, int* p)
{
    int n=s.length();
    s = "<"+s+">;
        int l=0, r=1;
    for(int i=1; i<=n; i++)
    {
        if(i>r) p[i]=0;
        else p[i]=min(r-i, p[l+r-i]);
        while(1<=i-p[i] && i+p[i]<=n && s[i-p[i]]==s[i+p[i]]) p[i]++; // mo rong p[i]
        p[i]--; // bo tam
        if(i+p[i]>r)
        {
            l=i-p[i];
            r=i+p[i];
        }
    }
}
void manacher2(string s, int* p)
{
    int n = s.length();
    string s1 = "";
    for(char v: s) s1 += '.', s1 += v;
    s1 += '.';
    manacher1(s1, tmp);
    for(int i=1; i<=n; i++) p[i] = tmp[i*2-1]/2;
}
/////////////////////////////////////////////////////////////
struct matrix
{
    vector<vector<int>> data;
    int row() const
    {
        return data.size();
    }
    int col() const
    {
        return data[0].size();
    }
    auto & operator [] (int i)
    {
        return data[i];
    }
    const auto & operator [] (int i) const
    {
        return data[i];
    }
    matrix() = default;
    matrix(int r, int c) :data(r, vector<int> (c)) { }
    matrix(const vector<vector<int>> &d) :data(d) { }
    static matrix iden(int n)
    {
        matrix ans = matrix(n, n);
        while(n--) ans[n][n]=1;
        return ans;
    }
    matrix operator * (const matrix &b)
    {
        matrix a=*this;
        matrix ans = matrix(a.row(), b.col());
        for(int i=0; i<a.row(); i++)
        {
            for(int j=0; j<b.col(); j++)
            {
                for(int k=0; k<a.col(); k++)
                {
                    ans[i][j]+=((a[i][k]%mod)*(b[k][j]%mod))%mod;
                    ans[i][j]%=mod;
                }
            }
        }
        return ans;
    }
    matrix power(ll exp)
    {
        matrix base=*this;
        matrix ans=iden(row());
        for(; exp>0; exp>>=1, base=base*base)
        {
            if(exp&1) ans=ans*base;
        }
        return ans;
    }
};
/////////////////////////////////////////////////////////////
struct node
{
    node* child[2];
    int sum, cnt, ex;
    node()
    {
        for(int i=0; i<2; i++) child[i]=NULL;
        sum=cnt=ex=0;
    }
};
struct Trie
{
    node* root;
    Trie()
    {
        root = new node();
    }
    void add(int x)
    {
        node* pos = root;
        for(int i=32; i>=0; i--)
        {
            int c = (x>>i)&1;
            if(pos->child[c] == NULL) pos->child[c] = new node();
            pos = pos->child[c];
            pos->sum+=x;
            pos->cnt++;
        }
        pos->ex++;
    }
    bool qfind(int x)
    {
        node* pos = root;
        for (int i=32; i>=0; i--)
        {
            int c = (x>>i)&1;
            if (pos->child[c] == NULL) return false;
            pos = pos->child[c];
        }
        return (pos->ex!=0);
    }
    void del(int x)
    {
        if(!qfind(x)) return;
        node* pos = root;
        for (int i=32; i>=0; i--)
        {
            int c = (x>>i)&1;
            node* tmp = pos->child[c];
            tmp->cnt--;
            tmp->sum-=x;
            if(tmp->cnt==0)
            {
                pos->child[c] = NULL;
                return;
            }
            pos = tmp;
        }
        pos->ex--;
    }
    int qsum(int x)
    {
        node* pos = root;
        int ans = 0;
        for (int i = 32; i >= 0; i--)
        {
            int c = (x>>i) & 1;
            if(c)
            {
                if (pos->child[0]) ans += pos->child[0]->sum;
            }
            if(pos->child[c]) pos = pos->child[c];
            else return ans;
            if(i==0) ans += pos->sum;
        }
        return ans;
    }
    int qxor(int x)
    {
        node* pos = root;
        int ans = 0;
        for (int i=32; i>=0; i--)
        {
            int c = (x>>i)&1;
            if (pos->child[c^1] != NULL)
            {
                ans += (1<<i);
                pos = pos->child[c^1];
            }
            else pos = pos->child[c];
        }
        return ans;
    }
    int qwalk(int x)
    {
        node* pos = root;
        int ans = 0;
        for (int i=32; i>=0; i--)
        {
            if(pos->child[0])
            {
                if (pos->child[0]->cnt >= x) pos = pos->child[0];
                else
                {
                    ans += (1 << i);
                    x-=pos->child[0]->cnt;
                    if (pos->child[1]) pos = pos->child[1];
                }
            }
            else
            {
                ans += (1<<i);
                pos = pos->child[1];
            }
        }
        return ans;
    }
};
/////////////////////////////////////////////////////////////
#include <bits/stdc++.h>
#define el '\n'
#define fi first
#define sc second
#define pii pair<int, int>
#define all(v) v.begin(), v.end()
#define int ll
using namespace std;
using ll=long long;
using ull=unsigned long long;
using ld=long double;
const int mod=1e9+7;
const int N=1e5+11;
int n, q, a[N], nod[4*N], add[4*N], mul[4*N], reset[4*N];
void glow(int id, int l, int r)
{
    if(l==r)
    {
        nod[id]=a[l]%mod;
        return;
    }
    int mid=(l+r)>>1;
    glow(id*2, l, mid);
    glow(id*2+1, mid+1, r);
    nod[id]=(nod[id*2]+nod[id*2+1])%mod;
}
void down(int id, int l, int r)
{
    int mid=(l+r)>>1;
    int llr=mid-l+1, rrr=r-mid;
    if(reset[id]!=0)
    {
        nod[id*2]=(reset[id]*llr)%mod;
        nod[id*2+1]=(reset[id]*rrr)%mod;
        reset[id*2]=reset[id*2+1]=reset[id];
        reset[id]=0;
        add[id*2]=add[id*2+1]=0;
        mul[id*2]=mul[id*2+1]=1;
    }
    nod[id*2]=(nod[id*2]*mul[id])%mod;
    nod[id*2+1]=(nod[id*2+1]*mul[id])%mod;
    mul[id*2]=(mul[id*2]*mul[id])%mod;
    mul[id*2+1]=(mul[id*2+1]*mul[id])%mod;
    add[id*2]=(add[id*2]*mul[id])%mod;
    add[id*2+1]=(add[id*2+1]*mul[id])%mod;
    mul[id]=1;
    nod[id*2]=(nod[id*2]+add[id]*llr)%mod;
    nod[id*2+1]=(nod[id*2+1]+add[id]*rrr)%mod;
    add[id*2]=(add[id*2]+add[id])%mod;
    add[id*2+1]=(add[id*2+1]+add[id])%mod;
    add[id]=0;
}
void up_sum(int id, int l, int r, int a, int b, int val)
{
    if(r<a || b<l) return;
    if(a<=l && r<=b)
    {
        add[id]=(add[id]+val)%mod;
        nod[id]=(nod[id]+val*(r-l+1))%mod;
        return;
    }
    int mid=(l+r)>>1;
    down(id, l, r);
    up_sum(id*2, l, mid, a, b, val);
    up_sum(id*2+1, mid+1, r, a, b, val);
    nod[id]=(nod[id*2]+nod[id*2+1])%mod;
}
void up_mul(int id, int l, int r, int a, int b, int val)
{
    if(r<a || b<l) return;
    if(a<=l && r<=b)
    {
        add[id]=(add[id]*val)%mod;
        nod[id]=(nod[id]*val)%mod;
        mul[id]=(mul[id]*val)%mod;
        return;
    }
    int mid=(l+r)>>1;
    down(id, l, r);
    up_mul(id*2, l, mid, a, b, val);
    up_mul(id*2+1, mid+1, r, a, b, val);
    nod[id]=(nod[id*2]+nod[id*2+1])%mod;
}
void up_reset(int id, int l, int r, int a, int b, int val)
{
    if(r<a || b<l) return;
    if(a<=l && r<=b)
    {
        reset[id]=val%mod;
        nod[id]=(val*(r-l+1))%mod;
        mul[id]=1;
        add[id]=0;
        return;
    }
    int mid=(l+r)>>1;
    down(id, l, r);
    up_reset(id*2, l, mid, a, b, val);
    up_reset(id*2+1, mid+1, r, a, b, val);
    nod[id]=(nod[id*2]+nod[id*2+1])%mod;
}
int get(int id, int l, int r, int a, int b)
{
    if(r<a || b<l) return 0;
    if(a<=l && r<=b)
    {
        return nod[id];
    }
    int mid=(l+r)>>1;
    down(id, l, r);
    return (get(id*2, l, mid, a, b) + get(id*2+1, mid+1, r, a, b))%mod;\
    nod[id]=(nod[id*2]+nod[id*2+1])%mod;
}
void sol()
{
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[i];
    fill(add, add+4*N+1, 0);
    fill(mul, mul+4*N+1, 1);
    fill(reset, reset+4*N+1, 0);
    glow(1, 1, n);
    while(q--)
    {
        int tt, x, l, r;
        cin >> tt >> l >> r;
        if(tt==1)
        {
            cin >> x;
            up_sum(1, 1, n, l, r, x);
        }
        if(tt==2)
        {
            cin >> x;
            up_mul(1, 1, n, l, r, x);
        }
        if(tt==3)
        {
            cin >> x;
            up_reset(1, 1, n, l, r, x);
        }
        if(tt==4)
        {
            cout << get(1, 1, n, l, r)%mod << el;
        }
    }
}
signed main()
{
//    freopen("task.INP", "r", stdin);
//    freopen("task.OUT", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t=1;
    //cin >> t;
    while(t--)
    {
        sol();
    }
}
/////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////
#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
#define el '\n'
#define fi first
#define sc second
using namespace std;
using ll=long long;
using ull=unsigned long long;
using ld=long double;
const int mod=1e9+7;
const int N=1e5+11;
mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
ll ran(ll left, ll right)
{
    return left+rd()%(right-left+1);
}
void maketest()
{
    ofstream inp("vcl"".inp");
    // code sinh test di thang l ran(l, r): rand tu l den r
    int x=ran(1, 20);
    inp << x << ' ' << x+ran(1, 100);
}
const int tests=1000;

int main()
{
    srand(time(0));
    for(int i=1; i<=tests; i++)
    {
        maketest();
        system("vcl""_trau.exe");
        system("vcl"".exe");
        if(system("fc ""vcl"".out ""vcl"".ans")!=0)
        {
            cout << "TEST" << i << ":WRONG!\n";
            return 0;
        }
        cout << "TEST" << i << ":CORRECT!\n";
    }
}
/////////////////////////////////////////////////////////////
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define el '\n'
#define fi first
#define sc second
#define int ll
#define pii pair<int, int>
#define all(v) v.begin(), v.end()
using namespace std;
#define ordered_set tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>
using namespace __gnu_pbds;
using ll=long long;
using ull=unsigned long long;
using ld=long double;
const int mod=1e9+7;
const int N=1e5+11;
void sol()
{
    
}
signed main()
{
//    freopen("divisor.INP", "r", stdin);
//    freopen("divisor.OUT", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t=1;
    //cin >> t;
    while(t--)
    {
        sol();
    }
}
