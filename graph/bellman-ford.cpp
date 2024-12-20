#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

const double INF = numeric_limits<double>::max();

struct Edge {
    int from, to;
    double weight;
    Edge(int f, int t, double w) : from(f), to(t), weight(w) {}
};

bool bellmanFord(const vector<Edge>& edges, int n, int start, vector<double>& dist, vector<int>& parent) {
    dist.assign(n, INF);
    parent.assign(n, -1);
    dist[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (const Edge& edge : edges) {
            if (dist[edge.from] != INF && dist[edge.from] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[edge.from] + edge.weight;
                parent[edge.to] = edge.from;
            }
        }
    }

    for (const Edge& edge : edges) {
        if (dist[edge.from] != INF && dist[edge.from] + edge.weight < dist[edge.to]) {
            return false;
        }
    }

    return true;
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

    int start;
    cin >> start;
    start--;

    vector<double> dist;
    vector<int> parent;
    
    bool no_negative_cycle = bellmanFord(edges, n, start, dist, parent);

    if (!no_negative_cycle) {
        cout << "There is a negative weight cycle in the graph" << endl;
        return 0;
    }

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
