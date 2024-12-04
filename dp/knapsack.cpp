#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool is_item_used(const vector<vector<int>>& chosen, int w, int v, int item,
                  const vector<int>& weight, const vector<int>& volume) {
    while(w > 0 && v > 0) {
        int prev_item = chosen[w][v];
        if(prev_item == item) return true;
        if(prev_item == -1) break;
        w -= weight[prev_item];
        v -= volume[prev_item];
    }
    return false;
}

void knapsack(vector<vector<int>>& dp, vector<vector<int>>& chosen, int n, int W, int V, 
              vector<int> cost, vector<int> weight, vector<int> volume) {
    for(int w = 1; w <= W; w++) {
        for(int v = 1; v <= V; v++) {
            int price = dp[w][v];
            for(int i = 0; i < n; i++) {
                if(weight[i] <= w && volume[i] <= v) {
                    // Check if this item wasn't used in the path
                    if(!is_item_used(chosen, w - weight[i], v - volume[i], i, weight, volume)) {
                        int new_price = cost[i] + dp[w - weight[i]][v - volume[i]];
                        if(new_price > price) {
                            price = new_price;
                            chosen[w][v] = i;
                        }
                    }
                }
            }
            dp[w][v] = price;
        }
    }
}

pair<int, string> get_solution(vector<vector<int>>& chosen, int W, int V,
                        vector<int> weight, vector<int> volume) {
    vector<int> items;
    int w = W, v = V;
    
    while(w > 0 && v > 0) {
        int item = chosen[w][v];
        if(item == -1) break;
        items.push_back(item);
        w -= weight[item];
        v -= volume[item];
    }
    int count = items.size();
    sort(items.begin(), items.end());

    string s = "(";
    for(auto i : items){
        s += to_string(i+1);
        s += ',';
    }
    s.pop_back();
    s += ')';
    return {count, s};
}

int main() {
    int n, W, V;
    cin >> n >> W >> V;
    vector<int> cost(n), weight(n), volume(n);
    
    for(int i = 0; i < n; i++) cin >> cost[i];
    for(int i = 0; i < n; i++) cin >> weight[i];
    for(int i = 0; i < n; i++) cin >> volume[i];
    
    vector<vector<int>> dp(W+1, vector<int>(V+1, 0));
    vector<vector<int>> chosen(W+1, vector<int>(V+1, -1));  // Initialize with -1
    
    knapsack(dp, chosen, n, W, V, cost, weight, volume);
    pair<int, string> solution = get_solution(chosen, W, V, weight, volume);
    
    cout << dp[W][V] << endl;
    cout << solution.first << endl;
    cout << solution.second << endl;
    
    return 0;
}