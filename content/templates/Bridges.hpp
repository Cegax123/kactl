// Finding bridges in O(N+M)

int n; // number of nodes
vector<vii> adj; // adjacency list of graph
vector<bool> vis;
vector<int> tin, low;
int timer;
void dfs(int v, int p = -1) {
    vis[v] = true;
    tin[v] = low[v] = timer++;
    for (auto e : adj[v]) {
        int to = e.first, id = e.second;
        if (to == p) continue;
        if (vis[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
                IS_BRIDGE(v, to);
        }
    }
}
