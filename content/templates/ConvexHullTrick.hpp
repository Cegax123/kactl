#define point complex<ll>
#define x real
#define y imag

ll dot(point a, point b) {
    return (conj(a) * b).x();
}
ll cross(point a, point b) {
    return (conj(a) * b).y();
}
vector<point> hull,vecs;
void add_line(ll k,ll b){
    point nw = {k,b};
    while(!vecs.empty() && dot(vecs.back(), nw - hull.back()) < 0) {
        hull.popb();
        vecs.popb();
    }
    if(!hull.empty()) vecs.pb(complex<ll>(0,1) * (nw - hull.back()));
    hull.pb(nw);
}
int get(ll x) {
    point query = {x, 1};
    auto it = lower_bound(all(vecs), query, [](point a, point b) {
        return cross(a, b) > 0;
    });
    return dot(query, hull[it - vecs.begin()]);
}
