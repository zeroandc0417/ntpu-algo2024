#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <climits>

using namespace std;

void prim(vector<int>& dist, vector<int>& parent, vector<bool>& visited, vector<vector<int>>& g, int s, int n){
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

    vector<vector<int>> g(n, vector<int>(n, -1));
    for(int i = 0; i < m; i++){
        int r, c;
        int w;
        cin >> r >> c >> w;
        g[r-1][c-1] = w;
        g[c-1][r-1] = w;
    }
    int s;
    cin >> s;

    vector<int> dist(n, INT_MAX);
    dist[s-1] = 0;
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);
  
    prim(dist, parent, visited, g, s, n);

    for(int i = 0; i < n; i++) {
      	if(i == n-1){
        	cout << parent[i] + 1 << endl;
        } else {
        	cout << (parent[i]+1) << ' ';
        }
    }
    
    int sum = 0;
    for(int i = 0; i < n; i++) {
        if(dist[i] == INT_MAX) {
            cout << 0 << endl;
            return 0;
        }
	    sum += dist[i];
    }
    cout << sum << endl;
    return 0;
}