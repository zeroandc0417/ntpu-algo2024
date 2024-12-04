#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class LogFib {
public:
    int length = 0;
    int target = 0;
    int power = 0;
    int multi_count = 0;
    vector<int> fib, coefficient;
    vector<vector<int>> fib_matrix;
    void load();
    vector<vector<int>> log_fib(int);
};

vector<vector<int>> matrix_power(vector<vector<int>> m1, vector<vector<int>> m2){
    int l = m1.size();
    vector<vector<int>> result(l, vector<int>(l, 0));
    for(int i = 0; i < l; i++){
        for(int j = 0; j < l; j++){
            for(int k = 0; k < l; k++){
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return result;
}

void LogFib::load(){
    cin >> this->length;
    this->fib.resize(this->length);
    this->coefficient.resize(this->length);
    for(int i = 0; i < this->fib.size(); i++){
        cin >> this->fib[i];
    }
    reverse(this->fib.begin(), this->fib.end());
    for(int i = 0; i < this->coefficient.size(); i++){
        cin >> this->coefficient[i];
    }
    cin >> this->target;
    this->power = this->target - this->length;
    this->fib_matrix.resize(this->length, vector<int>(this->length));
    for(int i = 0; i < this->fib_matrix[0].size(); i++){
        this->fib_matrix[0][i] = this->coefficient[i];
    }
    for(int i = 1; i < this->fib_matrix.size(); i++){
        for(int j = 0; j < this->fib_matrix[0].size(); j++){
            if(j+1 == i){
                this->fib_matrix[i][j] = 1;
            } else {
                this->fib_matrix[i][j] = 0;
            }
        }
    }
}

vector<vector<int>> LogFib::log_fib(int power){
    if(power == 0 || power == 1) return this->fib_matrix;
    if(power % 2 == 0){
        this->multi_count++;
        vector<vector<int>> matrix = this->log_fib(power/2);
        matrix = matrix_power(matrix, matrix);
        return matrix;
    } else {
        this->multi_count += 2;
        vector<vector<int>> matrix = this->log_fib(power/2);
        matrix = matrix_power(matrix, matrix);
        matrix = matrix_power(matrix, this->fib_matrix);
        return matrix;
    }
}

int main(){
    LogFib fib;
    fib.load();
    vector<vector<int>> matrix = fib.log_fib(fib.power);
    int result = 0;
    for(int i = 0; i < fib.length; i++){
        result += matrix[0][i] * fib.fib[i];
    }
    cout << result << endl;
    cout << fib.multi_count << endl;
}