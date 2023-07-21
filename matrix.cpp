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
