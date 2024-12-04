#include <iostream>
#include <vector>

using namespace std;

class MergeSort {
    public:
        int comparison_count = 0;
        int divide_count = 0;
        int length = 0;
        vector<int> vec;
        void load();
        void sort(vector<int>&);
        void print();
};

void MergeSort::load(){
    cin >> this->length;
    this->vec.resize(this->length);
    for(int i = 0; i < this->length; i++){
        cin >> this->vec[i];
    }
}

void print_vec(vector<int> vec){
    for(int i = 0; i < vec.size(); i++){
        cout << vec[i] << ' ';
    }
    cout << endl;
}


void MergeSort::sort(vector<int>& vec){
    if(vec.size() > 1){
        int mid = vec.size() / 2;
        vector<int> left_vec(vec.begin(), vec.begin() + mid);
        vector<int> right_vec(vec.begin() + mid, vec.end());
        this->divide_count++; 

        this->sort(left_vec);
        this->sort(right_vec);

        int left_index = 0;
        int right_index = 0;
        int merged_index = 0;

        while(left_index < left_vec.size() && right_index < right_vec.size()){
            if(left_vec[left_index] > right_vec[right_index]){
                vec[merged_index] = right_vec[right_index];
                right_index++;
            } else {
                vec[merged_index] = left_vec[left_index];
                left_index++;
            }
            this->comparison_count++;
            merged_index++;
        }
        while(left_index < left_vec.size()){
            vec[merged_index] = left_vec[left_index];
            merged_index++;
            left_index++;
        }
        while(right_index < right_vec.size()){
            vec[merged_index] = right_vec[right_index];
            merged_index++;
            right_index++;
        }
    }
}

void MergeSort::print(){
    for(int i = 0; i < this->length; i++){
        if(i == this->length - 1){
            cout << this->vec[i];
        } else {
            cout << this->vec[i] << ' ';
        }
    }
    cout << endl;
    cout << this->divide_count << endl;
    cout << this->comparison_count << endl;
}

int main(){
    MergeSort solution;
    solution.load();
    solution.sort(solution.vec);
    solution.print();
}