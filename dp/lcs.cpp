#include <iostream>
#include <vector>
#include <string>
using namespace std;

class LCS {
private:
    vector<string> seq1, seq2;
    vector<vector<int>> dp;
    
    void buildDP() {
        int m = seq1.size();
        int n = seq2.size();
        dp = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (seq1[i-1] == seq2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
    }
    
    void printLCS(int i, int j, vector<string>& result) {
        if (i == 0 || j == 0) return;
        
        if (seq1[i-1] == seq2[j-1]) {
            printLCS(i-1, j-1, result);
            result.push_back(seq1[i-1]);
        } else if (dp[i-1][j] >= dp[i][j-1]) {
            printLCS(i-1, j, result);
        } else {
            printLCS(i, j-1, result);
        }
    }

public:
    void readInput() {
        string line;
        
        // Skip the symbol set line
        getline(cin, line);
        
        // Read lengths
        int len1, len2;
        cin >> len1 >> len2;
        
        // Read first sequence
        seq1.resize(len1);
        for (int i = 0; i < len1; i++) {
            cin >> seq1[i];
        }
        
        // Read second sequence
        seq2.resize(len2);
        for (int i = 0; i < len2; i++) {
            cin >> seq2[i];
        }
    }
    
    void solve() {
        buildDP();
        
        // Print length of LCS
        cout << dp[seq1.size()][seq2.size()] << endl;
        
        // Print the LCS
        vector<string> result;
        printLCS(seq1.size(), seq2.size(), result);
        
        for (int i = 0; i < result.size(); i++) {
            cout << result[i];
            if (i < result.size() - 1) cout << " ";
        }
        cout << endl;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    LCS lcs;
    lcs.readInput();
    lcs.solve();
    return 0;
}
