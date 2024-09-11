// dp[i,j] = min[0 <= k <= j] dp[i-1][k-1] + C[k, j]
// opt(i, j) <= opt(i, j + 1)
vector<ll> dp_bef, dp;
 
void solve(int l, int r, int optl, int optr) {
    if(l > r) return;
 
    int mi = (l + r) >> 1;
    ll best_ans = (ll) 1e15;
    int opt = -1;
 
    for(int k = optl; k <= min(mi, optr); k++) {
        slide(k, mi);
        ll curr_ans = (k == 0 ? 0 : dp_bef[k-1]) + ccost;
        if(curr_ans < best_ans) {
            best_ans = curr_ans;
            opt = k;
        }
    }
 
    dp[mi] = best_ans;
 
    solve(l, mi-1, optl, opt);
    solve(mi+1, r, opt, optr);
}
