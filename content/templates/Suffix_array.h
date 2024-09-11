const int maxn = 1e5+5;
const int LOGN = 20;

int LCP_ST[maxn][LOGN];
void LCP_build(const vector<int>& lcp) {
    for(int i = 1; i <= (int) lcp.size(); i++) 
        LCP_ST[i][0] = lcp[i-1];
    for(int k = 1; (1 << k) <= (int) lcp.size(); k++) {
        int dis = 1 << (k-1);
        for(int i = 1; i + 2*dis -1 <= (int) lcp.size(); i++)
            LCP_ST[i][k] = min(LCP_ST[i][k-1], LCP_ST[i+dis][k-1]);
    }
}
int LCP(int L, int R) {
	if(L > R) swap(L, R);
    L++;
    int d = R-L+1;
    int k = 31- __builtin_clz(d);
    int dis = 1 << k;
    return min(LCP_ST[L][k], LCP_ST[R-dis+1][k]);
}
vector<int> lcp_array(vector<int> &s, vector<int> &a){
	int n = s.size();
	vector<int> rank(n);
	for(int i = 0; i < n; i++) rank[a[i]] = i;
	int k = 0;
	vector<int> lcp(n);
	for(int i = 0; i < n; i++){
		if(rank[i] + 1 == n){
			k = 0;
			continue;
		}
		int j = a[rank[i] + 1];
		while(i + k < n and j + k < n and s[i + k] == s[j + k]) k++;
		lcp[rank[i]] = k;
		if(k) k--;
	}
	return lcp;
}

vector<int> suffix_array(vector<int> &s){
	int n = s.size();
	vector<int> a(n);
	vector<int> mp(n);
	iota(a.begin(), a.end(), 0);
	sort(a.begin(), a.end(), [&] (int i, int j){
		return s[i] < s[j];
	});
	mp[a[0]] = 0;
	for(int i = 1; i < n; i++){
		mp[a[i]] = mp[a[i - 1]] + (s[a[i - 1]] != s[a[i]]);
	}
	int len = 1;
	vector<int> head(n);
	vector<int> nmp(n);
	vector<int> sbs(n);
	while(len < n){
		for(int i = 0; i < n; i++) sbs[i] = (a[i] - len + n) % n;
		for(int i = n - 1; i >= 0; i--) head[mp[a[i]]] = i;
		for(int i = 0; i < n; i++){
			int x = sbs[i];
			a[head[mp[x]]++] = x;
		}
		nmp[a[0]] = 0;
		for(int i = 1; i < n; i++){
			if(mp[a[i - 1]] != mp[a[i]]){
				nmp[a[i]] = nmp[a[i - 1]] + 1;
			}
			else{
				int pre = mp[(a[i - 1] + len) % n];
				int cur = mp[(a[i] + len) % n];
				nmp[a[i]] = nmp[a[i - 1]] + (pre != cur);
			}
		}
		swap(mp, nmp);
		len <<= 1;
	}
	return a;
}

