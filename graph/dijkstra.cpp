#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

const double INF = numeric_limits<double>::max();

// Structure to represent edges
struct Edge {
    int to;
    double weight;
    Edge(int t, double w) : to(t), weight(w) {}
};

void dijkstra(const vector<vector<Edge>>& graph, int start, vector<double>& dist, vector<int>& parent) {
    int n = graph.size();
    dist.assign(n, INF);
    parent.assign(n, -1);
    dist[start] = 0;

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        //C++17
        //auto [d, u] = pq.top();

        pair<double, int> top = pq.top();
        double d = top.first;
        int u = top.second;
        pq.pop();

        if (d > dist[u]) continue;

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            double weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> graph(n);
    
    for (int i = 0; i < m; i++) {
        int from, to;
        double weight;
        cin >> from >> to >> weight;
        from--; to--;
        graph[from].emplace_back(to, weight);
    }

    int start;
    cin >> start;
    start--;

    vector<double> dist;
    vector<int> parent;
    dijkstra(graph, start, dist, parent);

    for (int i = 0; i < n; i++) {
      if(i == n-1){
        if(dist[i] == INF){
          cout << -1 << endl;
        } else {
          cout << dist[i] << endl;
        }
        break;
      }
        if (dist[i] == INF) {
            cout << -1 << " ";
        } else {
            cout << dist[i] << " ";
        }
    }
    for (int i = 0; i < n; i++) {
      if(i == n-1) cout << parent[i] + 1 << endl;
      else cout << parent[i] + 1 << " ";
    }

    return 0;
}
