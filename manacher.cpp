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
