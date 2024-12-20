#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <iomanip>

using namespace std;

const double INF = numeric_limits<double>::max();

struct Edge {
    int from, to;
    double weight;
    Edge(int f, int t, double w) : from(f), to(t), weight(w) {}
};

bool bellmanFord(const vector<Edge>& edges, int n, vector<double>& h) {
    h.assign(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        for (const Edge& edge : edges) {
            if (h[edge.from] != INF && h[edge.from] + edge.weight < h[edge.to]) {
                h[edge.to] = h[edge.from] + edge.weight;
            }
        }
    }

    for (const Edge& edge : edges) {
        if (h[edge.from] != INF && h[edge.from] + edge.weight < h[edge.to]) {
            return false;
        }
    }
    return true;
}

void dijkstra(const vector<vector<pair<int, double>>>& graph, int start, vector<double>& dist) {
    dist.assign(graph.size(), INF);
    dist[start] = 0;
    
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto [v, weight] : graph[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges;
    
    for (int i = 0; i < m; i++) {
        int from, to;
        double weight;
        cin >> from >> to >> weight;
        from--; to--;
        edges.emplace_back(from, to, weight);
    }

    for (int i = 0; i < n; i++) {
        edges.emplace_back(n, i, 0);
    }

    vector<double> h;
    if (!bellmanFord(edges, n + 1, h)) {
        cout << "Negative cycle detected\n";
        return 0;
    }

    for (int i = 0; i < n; i++) {
      	if(i == n-1){
          if(h[i] == INF){
            cout << "N" << endl;
          } else {
            cout << h[i] << endl;
          }
          continue;
        }
        if (h[i] == INF) {
            cout << "N ";
        } else {
            cout << h[i] << " ";
        }
    }
    cout << "\n";

    vector<vector<pair<int, double>>> graph(n);
    for (const Edge& edge : edges) {
        if (edge.from == n) continue;
        double new_weight = edge.weight + h[edge.from] - h[edge.to];
        graph[edge.from].emplace_back(edge.to, new_weight);
    }

    vector<vector<double>> dist(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        vector<double> d;
        dijkstra(graph, i, d);
        for (int j = 0; j < n; j++) {
            if (d[j] == INF) {
                dist[i][j] = INF;
            } else {
                dist[i][j] = d[j] - h[i] + h[j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if(j == n-1){
            if(dist[i][j] == INF){
              cout << "N" << endl;
            } else {
              cout << dist[i][j] << endl;
            }
            continue;
          }
            if (dist[i][j] == INF) {
                cout << "N ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
    }

    return 0;
}
