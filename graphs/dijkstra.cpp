/**
 * Graph is expected to be vector<pair<int, long long> >[MAXN];
 * dist is a long long array that contains the distances
 * long long dist[MAXN];
 */

void dijkstra(const int& s) {
    priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;

    memset(dist, -1, sizeof(dist));
    pq.push(make_pair(0LL, s));
    dist[s] = 0LL;

    while (!pq.empty()) {
        pair<long long, int> cur = pq.top();
        pq.pop();

        int node = cur.second;

        if (cur.first > dist[node])
            continue;

        for (auto it = graph[node].begin(); it != graph[node].end(); ++it) {
            int next_node = it->first;
            long long new_dist = cur.first + it->second;

            if (dist[next_node] == -1 || new_dist < dist[next_node]) {
                dist[next_node] = new_dist;
                pq.push(make_pair(new_dist, next_node));
            }
        }
    }
}


