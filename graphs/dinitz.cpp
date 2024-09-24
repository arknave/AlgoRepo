// Computes the max flow on a graph with Dinic's algorithm
// Just from kactl with expanded macros
struct Dinitz {
    using Flow_t = int64_t;
    static constexpr Flow_t INF = std::numeric_limits<Flow_t>::max();
	struct Edge {
		int32_t to, rev;
		Flow_t cap, origCap;
		Flow_t flow() const { return std::max(origCap - cap, Flow_t{}); }
	};

    std::vector<int32_t> level, head, q;
    std::vector<std::vector<Edge>> adj;

    Dinitz(int32_t n): q(n), adj(n) {}

    void addEdge(int32_t a, int32_t b, Flow_t c, Flow_t revC = Flow_t{}) {
        adj[a].push_back({b, static_cast<int32_t>(adj[b].size()), c, c});
        adj[b].push_back({a, static_cast<int32_t>(adj[a].size()) - 1, revC, revC});
    }

    void bfs(Flow_t bit, int32_t src, int32_t sink) {
        level.assign(q.size(), 0);

        int32_t qi = 0;
        int32_t qe = 1;
        q[0] = src;
        level[src] = 1;
        while (qi < qe && level[sink] == 0) {
            int32_t u = q[qi++];
            for (auto e : adj[u]) {
                if (!level[e.to] && (e.cap >> (30 - bit)) > 0) {
                    q[qe++] = e.to;
                    level[e.to] = level[u] + 1;
                }
            }
        }
    }

    Flow_t dfs(int32_t u, int32_t sink, Flow_t curFlow) {
        if (u == sink || !curFlow) return curFlow;
        for (int32_t& i = head[u]; i < adj[u].size(); ++i) {
            Edge& e = adj[u][i];
            if (level[e.to] == level[u] + 1) {
                if (Flow_t p = dfs(e.to, sink, std::min(curFlow, e.cap)); p > 0) {
                    e.cap -= p;
                    adj[e.to][e.rev].cap += p;
                    return p;
                }
            }
        }

        return {};
    }

    Flow_t calc(int32_t src, int32_t sink) {

        Flow_t flow{};
        for (Flow_t bit = 0; bit < 31; ++bit) {
            do {
                bfs(bit, src, sink);

                head.assign(q.size(), 0);
                while (Flow_t p = dfs(src, sink, INF))
                    flow += p;
            } while (level[sink] > 0);
        }

        return flow;
    }

	bool leftOfMinCut(int32_t a) { return level[a] != 0; }
};


