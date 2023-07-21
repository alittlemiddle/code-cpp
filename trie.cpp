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
