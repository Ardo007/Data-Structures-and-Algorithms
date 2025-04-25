#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


int MaximumSubarraySum(vector<int>& vec) {
    int result = 0;
    int curMax = vec[0];

    for(int i = 1; i < vec.size(); i++) {
        curMax = max(curMax + vec[i], vec[i]);
        result = max(result, curMax);
    }

    return result;


}


int main() {

    vector<int> nums {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    cout << MaximumSubarraySum(nums) << "\n";

    return 0;
}