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
