#include <iostream>
#include <set>
#include <vector>

/*
 * Tabulation method - Calculate max profit for each capacity from 
 * 0 -> capacity. At each step, check all weights. For all weights under
 * current capacity, calculate its profit by taking that weight's profit
 * and also the max profit previously calculated for capacity - weight.
 */
int knapsack(std::vector<int> weights, std::vector<int> profits, int capacity) {
    // Keep track of max profit at each capacity from 0 -> capacity 
    std::vector<int> dp(capacity + 1);
    std::vector<std::set<int>> dpWeights(capacity + 1);

    // Calculate max profit for capacity from 0 -> capacity
    for (unsigned c = 0; c <= capacity; c++) {
         int maxProfit = 0;
         std::set<int> maxProfitWeights;

         // Take all weights that are less than capacity. 
         // Calculate max profit including that weight and check if it 
         // maximizes total max profit for current capacity
         for (unsigned j = 0; j < weights.size(); j++) {
            if (weights[j] <= c) {
                int currWeight = weights[j];
                
                // If weight was not used earlier
                if (dpWeights[c - currWeight].find(currWeight) == dpWeights[c - currWeight].end()) {
                    
                    // Calculate profit 
                    int currProfit = profits[j] + dp[c - currWeight];
                    
                    // Add current weight and weights from dp into set
                    std::set<int> currWeights;
                    currWeights.insert(currWeight);
                    currWeights.insert(dpWeights[c - currWeight].begin(),
                        dpWeights[c - currWeight].end());
                    
                    // If profit is maximal, update max vars
                    if (currProfit > maxProfit) {
                        maxProfit = currProfit;
                        maxProfitWeights = currWeights;
                    }
                }
            }
         }
        
         // Store calculated max profit for current capacity
         dp[c] = maxProfit;
         dpWeights[c] = maxProfitWeights;
    }

    // Return calculated max profit for requested capacity
    return dp[capacity];
}

int main() {
    std::vector<int> profits= {1, 6, 10, 16};
    std::vector<int> weights = {1, 2, 3, 5};
    
    for (unsigned i = 5; i < 10; i++) {
        int res = knapsack(weights, profits, i);
        std::cout << "Max profits for capacity " << i << " is " << res << ".\n";
    }
}
