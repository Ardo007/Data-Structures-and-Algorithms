#include <iostream>
#include <vector>

using namespace std;


// if the number at index i is smaller than the number before it, aka i - 1, swap them to put them in a sorted order 
// then keep repeating until we reach index 0 to make sure it is all sorted.
void insertOne(vector<int>& vec, size_t i) {
    while(i >= 1 && vec[i] < vec[i-1]) {
        swap(vec[i], vec[i-1]);
        i--;
    }
}

void insertionSort(vector<int>& vec) {
    // start at index 1 to compare the number in index 1 with 0
    for(size_t i = 1; i < vec.size(); i++) {
        insertOne(vec, i);
    }
}



int main() {

    vector<int> nums {4, 13, 5, 6, 8, 1, 2, 3};

    for(size_t x : nums) {
        cout << x << " ";
    }

    cout << endl;

    insertionSort(nums);

    for(size_t x : nums) {
        cout << x << " ";
    }




    return 0;
}

