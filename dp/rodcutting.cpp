#include <iostream>
#include <vector>
#include <string>
using namespace std;

pair<string, int> cutting(int length, vector<int>& cut){
    int count = 0;
    string s = to_string(length) + '=';
    while(length > 0){
        s += to_string(cut[length]);
        s.push_back('+');
        length -= cut[length];
        count++;
    }
    s.pop_back();
    return {s, count};
}

void rodcutting(vector<int>& price, vector<int>& sell, vector<int>& cut, int n){
    for(int i = 1; i <= n; i++){
        int q = INT_MIN;
        for(int j = 1; j <= i; j++){
            if(q < price[j] + sell[i-j]){
                q = price[j] + sell[i-j];
                cut[i] = j;
            }
        }
        sell[i] = q;
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> price(n+1, 0), sell(n+1, 0), cut(n+1, 0);
    for(int i = 1; i <= n; i++){
        cin >> price[i];
    }

    rodcutting(price, sell, cut, n);
    
    pair<string, int> res = cutting(n, cut);

    cout << sell[n] << endl;
    cout << res.second << endl;
    cout << res.first << endl;

    return 0;
}