#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

using namespace std;

void prim(vector<float>& dist, vector<int>& parent, vector<bool>& visited, vector<vector<float>>& g, int s, int n){
    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> pq;
    pq.push({0, s-1});

    while(!pq.empty()) {
        pair<float, int> vertex = pq.top();
        pq.pop();
        int curr = vertex.second;
        
        if(visited[curr]) continue;
        visited[curr] = true;

        for(int i = 0; i < n; i++) {
            float weight = g[curr][i];
            if(weight != -1 && !visited[i]) {
                if(weight < dist[i]) {
                    dist[i] = weight;
                    parent[i] = curr;
                    pq.push({dist[i], i});
                }
            }
        }
    }
}

int main(){
    int n, m;
    cin >> n >> m;

    vector<vector<float>> g(n, vector<float>(n, -1));
    for(int i = 0; i < m; i++){
        int r, c;
        float w;
        cin >> r >> c >> w;
        g[r-1][c-1] = w;
        g[c-1][r-1] = w;
    }
    int s;
    cin >> s;

    vector<float> dist(n, INT_MAX);
    dist[s-1] = 0;
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> pq;
    pq.push({0, s-1});

    prim(dist, parent, visited, g, s, n);

    for(int i = 0; i < n; i++) {
        cout << (parent[i] == -1 ? 0 : parent[i] + 1) << ' ';
    }
    cout << endl;
    int sum = 0;
    for(auto i : dist){
        sum += i;
    }
    cout << sum << endl;
    return 0;
}