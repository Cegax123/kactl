namespace fft{
    const int mod=998244353;
    inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
    inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
    inline int mul(int x,int y){return ((ll)x*y)%mod;}
    inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
    inline int invv(int x){return step(x,mod-2);}
    const int fft_maxn=(1<<20);
    int proot=step(3,8*7*17);
    int prekw[fft_maxn];
    bool isprek=false;
    void prek(){
        if(isprek)return;
        isprek=true;
        prekw[0]=1;
        for(int i=1;i<fft_maxn;i++) prekw[i]=mul(prekw[i-1],proot);
    }
    void fft(vector<int>&a,bool invert){
        prek();
        int n=a.size();
        int j=0;
        for(int i=1;i<n;i++){
            int bit=n>>1;
            for(;bit&j;bit>>=1)j^=bit;
            j^=bit;
            if(i<j)swap(a[i],a[j]);
        }
        for(int len=2;len<=n;len<<=1){
            int hlen=(len>>1);
            for(int i=0;i<n;i+=len){
                int d=fft_maxn/len;
                int curr=0;
                if(invert)d=fft_maxn-d;
                for(int j=0;j<hlen;j++){
                    int pom1=a[i+j];
                    int pom2=mul(a[i+j+hlen],prekw[curr]);
                    a[i+j]=add(pom1,pom2);
                    a[i+j+hlen]=sub(pom1,pom2);
                    curr+=d;
                    if(curr>=fft_maxn)curr-=fft_maxn;
                }
            }
        }
        if(invert){
            int invn=invv(n);
            for(int i=0;i<n;i++)a[i]=mul(a[i],invn);
        }
    }
}
