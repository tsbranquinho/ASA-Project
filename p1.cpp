#include <iostream>
#include <vector>
#include <algorithm>

//O(C x L x min (L e C)

int knapsack(std::vector<std::vector<int>>& dp, int spaceLength, int spaceWidth) {

   
    for (int l = 1; l <= spaceLength; l++) {
        for (int w = 1; w <= spaceWidth; w++) {

            // Vertical cuts
            for (int i = 0; l - i >= 0; i++) {
                dp[l][w] = std::max({
                    dp[l - i][w] + dp[i][w],
                    dp[l][w]                             // If there is an item already there with a bigger value than the combination of cuts
                });
            }

            // Horizontal cuts
            for (int i = 0; w - i >= 0; i++) {
                dp[l][w] = std::max({
                    dp[l][w - i] + dp[l][i],
                    dp[l][w]                             // If there is an item already there with a bigger value than the combination of cuts
                });
            }
        }
    }
    return dp[spaceLength][spaceWidth];
}

int main() {
    int spaceLength, spaceWidth, n, length, width, value;

    scanf("%d %d", &spaceLength, &spaceWidth);

    // Initialize the dynamic programming table
    std::vector<std::vector<int>> dp(spaceLength + 1, std::vector<int>(spaceWidth + 1, 0));

    scanf("%d", &n);

    for (; n > 0; n--) {
        scanf("%d %d %d", &length, &width, &value);

        if (length <= spaceLength && width <= spaceWidth) {
                    dp[length][width] = std::max(value, dp[length][width]);
        }
        if (width <= spaceLength && length <= spaceWidth) {
                    dp[width][length] = std::max(value, dp[width][length]);
        }
    }

    int result = knapsack(dp, spaceLength, spaceWidth);

    printf("%d\n", result);

    return 0;
}

