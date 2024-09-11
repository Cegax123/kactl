const int E = 26;
struct AC {
    int nodes;
    vector<vi> go;
    vi suf, term, super;
    AC(): nodes(0) {node();}
    int node() {
        // emplace back: go, suf, term, super (0)
        return nodes++;
    }
    void insert(const string& s) {
        int pos = 0;
        for(int i = 0; i < (int) s.size(); i++) {
            int nxt = s[i]-'a';
            if(go[pos][nxt] == 0) go[pos][nxt] = node();
            pos = go[pos][nxt];
        }
        term[pos]++;
    }
    void build(int src=0) {
        queue<int> Q;
        Q.emplace(src);
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            if(term[suf[u]]) super[u] = suf[u];
            else super[u] = super[suf[u]];
            for(int c = 0; c < E; c++) {
                if(go[u][c]) {
                    int v = go[u][c];
                    Q.emplace(v);
                    suf[v] = u == 0 ? 0 : go[suf[u]][c];
                }
                else {
                    go[u][c] = u == 0 ? 0 : go[suf[u]][c];
                }
            }
        }
    }
    void clear() {
        // clear: go, suf, term, super
        nodes = 0;
        node();
    }
};

