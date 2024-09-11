using cd = complex<double>;
const double PI = acos(-1);
void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    vector<cd> root(2*n);
    root[1]=cd(1,0);
    for(int k = 2; k < n; k <<= 1){
        double alpha = 2 * PI / (k<<1) * (invert ? -1 : 1);
        cd w(cos(alpha), sin(alpha));
        for(int i=(k>>1); i<k; i++){
            root[2*i] = root[i];
            root[2*i+1] = root[i]*w;
        }
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        for (int i = 0; i < n; i += len) 
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * root[j+len/2];
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
            }
    }
    if (invert) {
        for (cd & x : a) x /= n;
    }
}
void multiply(vector<ll> const& a, vector<ll> const& b,vector<ll> &result) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    result.resize(n);
    for (int i = 0; i < n; i++) result[i] = round(fa[i].real());
}
void convolute(vector<ll> &a,vector<ll> &b,vector<ll> &mul){
    int n=a.size();
    multiply(a,b,mul);
    mul.resize(n);
}
