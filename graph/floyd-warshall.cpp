#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

const double INF = numeric_limits<double>::max();

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<double>> dist(n, vector<double>(n, INF));
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int from, to;
        double weight;
        cin >> from >> to >> weight;
        from--; to--;
        dist[from][to] = weight;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && 
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
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
