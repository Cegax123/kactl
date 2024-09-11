const int Maxn = 100010 *3;
int Mo = 998244353; //系数的模
// P: módulo de la FFT, G: raíz primitiva de P. Nota: P debe ser mayor que el valor máximo que pueden tener los coeficientes.
// P = C * 2^k + 1. Nota: elegir un P adecuado. Aquí es 119 * 2^23 + 1, que es 1004535809.
int P  = 998244353 , G = 3;
struct fft{    
    ll FA[Maxn],FB[Maxn],tmp[Maxn];
    ll pw (ll a, int b,int Mo){
        ll ans = 1;
        for (;b;b/=2,a=a*a%Mo)
            if (b&1) ans =  a * ans  % Mo; 
        return ans;
    }
    int Getlen(int x){ while(x&(x-1)) x+=x&-x; return x;}
    //n:长度(2的幂),A:系数数组,ck 0是FFT,1是DFT
    void FFT(int N,ll* A,int ck){
        ll w1 = pw(G,(P-1)/N,P) , Rev = pw(N,P-2,P) ,Wx[Maxn];
        Wx[0] = 1;
        for (int i=1;i<=N;i++) Wx[i] = w1 * Wx[i-1] % P;
        for (int d=N/2; d ;d/=2){
            ll wn = 1 , w = ck?Wx[N-d]:Wx[d];
            for (int i=0; i<N; i+=d,wn=wn*w%P)
                for (int j=0, p=2*i%N; j<d ;j++)
                    tmp[i+j]= ( wn * A[p+d+j] + A[p+j])%P;
            for (int i=0;i<N;i++) A[i]=tmp[i];
        }
        if (ck) for (int i=0;i<N;i++) A[i]= Rev * A[i] %P;
    } 
    void Poly_Div(ll* A,ll* B,ll *D,ll *R,int nA,int nB){
    //多项式A=B*D+R 求得D,R      
        ll FA[Maxn],FB[Maxn];
        for (int i=0;i<nA;i++) FA[i] = A[nA-i];
        for (int i=0;i<nB;i++) FB[i] = B[nB-i];
        int nD = nA - nB + 1, nR;
        Poly_Inv(nD,FB,D);
        Poly_Multi(FA,D,D,nD,nD);
        nR = Poly_Multi(FB,D,R,nB,nD) - nD;
        for (int i=0;i<nR;i++) R[i]=(FA[i+nD]-R[i+nD])%Mo;
        for (int i=0;i<nD/2;i++) swap(D[i],D[nD-i]);
        for (int i=0;i<nR/2;i++) swap(R[i],R[nR-i]);            
    }
    int Poly_Multi(ll * A,ll* B,ll* C,int nA,int nB){        
        int nC = nA+nB-1 , m = Getlen(nC);
        for (int i=0;i<m;i++)  FA[i]=FB[i]=0;
        for (int i=0;i<nA;i++) FA[i]=A[i];
        for (int i=0;i<nB;i++) FB[i]=B[i];            
        FFT(m,FA,0); FFT(m,FB,0);
        for (int i=0;i<m;i++) C[i] = FA[i] * FB[i] % P;
        FFT(m,C,1);
        return nC;
    }
    void Poly_Inv(int t,ll *A,ll *B){
    //El inverso de un polinomio A bajo el modulo x^t es B
        ll FA[Maxn]; 
        B[0] = pw(A[0],Mo-2,Mo); t*=2;
        for (int m=2;m<t;m<<=1){          
            for(int i=m/2;i<m*2;i++) B[i] = FA[i] = 0;
            for(int i=0;i<m;i++) FA[i] = A[i];
            FFT(m*2,FA,0);FFT(m*2,B,0);
            for(int i=0;i<m*2;i++) B[i]=(2 - FA[i]*B[i]) %P * B[i] % P;
            FFT(m*2,B,1);
        }
    }
    
    void Poly_Sqrt(int t,ll *A,ll *B){
    //B^2=A % x ^ t. Nota: la longitud de B, nB, es t.
    // Solo se maneja el caso en que A[0] = 1; de lo contrario, usa BGstep para encontrar el residuo cuadrático de A[0] módulo Mo.
        ll FB[Maxn];    
        int Rev2 = pw(2,Mo-2,Mo);
        B[0] = 1; t<<=1;
        for (int m=2;m<t;m<<=1){
            // for(int i=m/2;i<m;i++) B[i] =0;
            Poly_Inv(m,B,FB);
            Poly_Multi(A,FB,FB,m,m);
            for (int i=0;i<m;i++) B[i] = (B[i]+FB[i])%P * Rev2 % Mo;
        }
    }
}FFT;

int a,deg,N,M;
ll  A[Maxn],B[Maxn],C[Maxn];
int main(){
    scanf("%d%d",&N,&M);
    deg = FFT.Getlen(M+1);
    for (int i=1;i<=N;i++){
        scanf("%d",&a);
        if (a>deg) continue;
        A[a]-=4;
    }
    A[0] = 1;
    FFT.Poly_Sqrt(deg,A,B);
    B[0]++;
    FFT.Poly_Inv(deg,B,A);
    for (int i=1;i<=M;i++) cout<<(Mo+A[i]*2%Mo) %Mo <<endl;
}

