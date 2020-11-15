// Equal Subset Sum Partition
#include <iostream>
#include <vector>

bool partition(std::vector<int> nums) {
    
    // Sum up numbers
    int sum = 0;
    for (auto& n : nums) {
        sum += n;
    }

    // If sum can't be split in half evenly
    if (sum % 2 == 1) {
        return false;
    }

    int half = sum / 2;
    
    // Check each sum from 0 -> half, and see if there is a subset
    // of numbers that sums to that sum
    std::vector<bool> canSplit(half + 1);
    canSplit[0] = true;  // Sum of 0 is always true

    // Keep track of the numbers used to create each sum
    std::vector<std::vector<bool>> numsUsed(half + 1, std::vector<bool>(nums.size()));
   
    // Check each sum from 1 -> half
    for (unsigned currSum = 1; currSum <= half; currSum++) {
        // Check each number in the list
        for (unsigned i = 0; i < nums.size(); i++) {
            int n = nums[i];
            if (n <= currSum) {
                // If it was not used in the set to build sum - n, and 
                // there is a valid subset to build sum - n, then there
                // is a valid solution for the current sum
                if (canSplit[currSum - n] && !numsUsed[currSum - n][i]) {
                    canSplit[currSum] = true;
                    // Copy numbers used in sum - n
                    numsUsed[currSum] = numsUsed[currSum - n];
                    // Mark n as used
                    numsUsed[currSum][i] = true;
                    break;
                }
            }
        }
    }
    
    // Print out numsUsed
    for (unsigned i = 0; i < half + 1; i++) {
        for (unsigned j = 0; j < nums.size(); j++) {
            std::cout << numsUsed[i][j] << " ";
        }
        std::cout << "\n";
    }

    return canSplit[canSplit.size() - 1];
}

int main() {
    
    std::vector<std::vector<int>> cases = {
        {1, 2, 3, 4},
        {1, 1, 3, 4, 7},
        {2, 3, 4, 6},
        {0},
        {4},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {5, 12, 3, 7, 9}
    };

    std::vector<bool> expected = {
        true,
        true,
        false,
        false,
        false,
        true,
        false
    };
    
    for (unsigned i = 0; i < cases.size(); i++) {
        bool res = partition(cases[i]);
        if (res == expected[i]) {
            std::cout << "Passed" << "\n";
        }
        else {
            std::cout << res << " expected " << expected[i] << "\n";
        }
    }
}
