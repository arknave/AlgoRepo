/**
 * Graph is expected to be vector<pair<int, ll> >[MAXN];
 * dist is a ll array that contains the distances
 * ll dist[MAXN];
 */
void dijkstra(const int& s) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    memset(dist, -1, sizeof(dist));
    pq.push(make_pair(0LL, s));
    dist[s] = 0LL;

    while (!pq.empty()) {
        pair<ll, int> cur = pq.top();
        pq.pop();

        int node = cur.second;

        if (cur.first != dist[node])
            continue;

        for (auto& e : graph[node]) {
            int next_node = e.first;
            ll new_dist = cur.first + e.second;

            if (dist[next_node] == -1 or new_dist < dist[next_node]) {
                dist[next_node] = new_dist;
                pq.push(make_pair(new_dist, next_node));
            }
        }
    }
}

// as a struct for whatever reason
struct dijkstra {
    using edge = pair<ll, int>;

    int n;
    vector<vector<edge>> graph;

    dijkstra(int n): n(n) {
        graph.assign(n, vector<edge>());
    }

    void add_edge(int u, int v, ll w) {
        graph[u].emplace_back(w, v);
        graph[v].emplace_back(w, u);
    }

    vector<ll> run(int src) {
        vector<ll> dist(n, INF);
        priority_queue<edge, vector<edge>, greater<edge>> pq;

        dist[src] = 0LL;
        pq.emplace(0LL, src);

        ll cur_dist;
        int u;
        while (!pq.empty()) {
            tie(cur_dist, u) = pq.top();
            pq.pop();
            if (dist[u] != cur_dist)
                continue;

            for (auto& e : graph[u]) {
                ll w = e.first;
                int v = e.second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }
        }

        return dist;
    }
};
