#include <iostream>
#include <vector>

class InsertionSort {
    public:
        int comparison_count = 0;
        int length = 0;
        std::vector<int> vec;
        void load();
        void sort();
        void print();
};

void InsertionSort::load(){
    std::cin >> this->length;
    this->vec.resize(this->length);
    for (int i = 0; i < this->length; i++){
        std::cin >> this->vec[i];
    }
}

void printArray(std::vector<int> vec){
    for(int i = 0; i < vec.size(); i++){
        std::cout << vec[i] << ' ';
    }
    std::cout << std::endl;
}

void InsertionSort::sort() {
    for(int i = 1; i < this->length; i++){
        int target = this->vec[i];
        for(int j = i-1; j >= 0; j--){
            this->comparison_count++;
            if(target > this->vec[j]){
                this->vec[j+1] = target;
                break;
            } else {
                this->vec[j+1] = this->vec[j];
            }
            this->vec[j] = target;
        }
    }
}

void InsertionSort::print() {
    for (int i = 0; i < length; i++) {
        if (i == length - 1) {
            std::cout << vec[i];
        } else {
            std::cout << vec[i] << " ";
        }
    }
    std::cout << std::endl;
    std::cout << comparison_count << std::endl;
}

int main() {
    InsertionSort solution;
    solution.load();
    solution.sort();
    solution.print();
    return 0;
}

