#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second < b.second;
}

void greedy(vector<int>& select, vector<pair<int, int>>& activities, int n){
    for(int i = 1,  j = 0; i < n; i++){
        if(activities[i].first >= activities[j].second){
            select.push_back(i);
            j = i;
        }
    }
}

string get_solution(vector<int>& select){
    string s = "(";
    for(auto i : select){
        s += to_string(i+1);
        s += ',';
    }
    s.pop_back();
    s += ')';
    return s;
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> activities(n);
    for(int i = 0; i < n; i++) cin >> activities[i].first;
    for(int i = 0; i < n; i++) cin >> activities[i].second;
    sort(activities.begin(), activities.end(), cmp);
    vector<int> select;
    select.push_back(0);
    greedy(select, activities, n);
    cout << select.size() << endl;
    cout << get_solution(select) << endl;
    return 0;
}