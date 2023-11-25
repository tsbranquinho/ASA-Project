#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int knapsack(vector<vector<int>>& dp, int spaceLength, int spaceWidth) {

   
    for (int l = 1; l <= spaceLength; l++) {
        for (int w = 1; w <= spaceWidth; w++) {

            // All possible Vertical cuts
            for (int i = 0; l - i >= l/2; i++) {
                dp[l][w] = max({
                    dp[l - i][w] + dp[i][w],
                    dp[l][w]  // If there is an item already there with a bigger value than the combination of cuts
                });
            }

            // All possible Horizontal cuts
            for (int i = 0; w - i >= w/2; i++) {
                dp[l][w] = max({
                    dp[l][w - i] + dp[l][i],
                    dp[l][w]   // If there is an item already there with a bigger value than the combination of cuts
                });
            }
        }
    }
    return dp[spaceLength][spaceWidth]; //best combination of cuts possible
}

int main() {
    int spaceLength, spaceWidth, n, length, width, value;

    scanf("%d %d", &spaceLength, &spaceWidth);

    // Initialize the dynamic programming table
    vector<vector<int>> dp(spaceLength + 1, vector<int>(spaceWidth + 1, 0));

    scanf("%d", &n);

    //put the items in the table
    for (; n > 0; n--) {
        scanf("%d %d %d", &length, &width, &value);

        if (length <= spaceLength && width <= spaceWidth) {
                    dp[length][width] = max(value, dp[length][width]);
        }
        if (width <= spaceLength && length <= spaceWidth) {
                    dp[width][length] = max(value, dp[width][length]);
        }
    }

    int result = knapsack(dp, spaceLength, spaceWidth);

    printf("%d\n", result);

    return 0;
}

