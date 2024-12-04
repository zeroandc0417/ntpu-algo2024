#include <iostream>
#include <vector>

using namespace std;

class LogPower {
    public:
        int multi_count = 0;
        int base = 0;
        int power = 0;
        void load();
        int pow(int);
};

void LogPower::load(){
    cin >> this->base;
    cin >> this->power;
}

int LogPower::pow(int power){
    if(power == 0) return 1;
    if(power == 1) return this->base;
    if(power % 2 == 0){
        int num = this->pow(power/2);
        this->multi_count++;
        return num * num;
    } else {
        int num = this->pow(power/2);
        this->multi_count += 2;
        return num * num * this->base;
    }
}

int main(){
    LogPower pow;
    pow.load();
    cout << pow.pow(pow.power) << endl;
    cout << pow.multi_count << endl;
}