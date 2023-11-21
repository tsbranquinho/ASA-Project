#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>

using namespace std;

struct Item {
    int length;
    int width;
    int value;
};

int knapsack(Item items[], int n, int spaceLength, int spaceWidth) {
    // Initialize the dynamic programming table import for the start of the algorithm
    int dp[spaceLength + 1][spaceWidth + 1];
    memset(dp, 0, sizeof(dp));

    // Iterate over each item
    for (int i = 0; i < n; i++) {
        // Iterate over possible lengths
        for (int l = 1; l <= spaceLength; l++) {
            // Iterate over possible widths
            for (int w = 1; w <= spaceWidth; w++) {
            
                // Check if the item can fit at the current position
                if (l >= items[i].length && items[i].width <= w) {
                    // Knapsack algorithm to determine the maximum value
                    dp[l][w] = max({
                        dp[l][w],                           // Case 1: Don't use the current item
                        items[i].value + dp[l][w - items[i].width],       // Case 2: Use the current item and gets the left neighbour on the table
                        items[i].value + dp[l - items[i].length][w]        // Case 3: Use the current item vertically the gets the upper neighbour on the table
                    });

                    // Cutting the pieces and considering the combination of two existing pieces with the current one
                    dp[l][w] = max({
                        dp[l - items[i].length][w] + dp[items[i].length][w],  // Vertical cut
                        dp[l][w - items[i].width] + dp[items[i].width][1],    // Horizontal cut
                        dp[l][w]
                    });
                }

                // Similar logic for the case when the item is rotated, if its a square there is no need to rotate
                if (w >= items[i].length && items[i].width <= l && items[i].length != items[i].width) {
                    dp[l][w] = max({
                        dp[l][w],
                        items[i].value + dp[l - items[i].width][w],
                        items[i].value + dp[l][w - items[i].length]
                    });
                    dp[l][w] = max({
                        dp[l - items[i].width][w] + dp[items[i].width][w],
                        dp[l][w - items[i].length] + dp[l][items[i].length],
                        dp[l][w]
                    });
                }
            }
        }
    }
    return dp[spaceLength][spaceWidth];
}

int main() {

    ifstream inputFile("large_input.txt");

    int spaceLength, spaceWidth, n;
    inputFile >> spaceLength >> spaceWidth >> n;

    Item items[n];
    for (int i = 0; i < n; ++i) {
        inputFile >> items[i].length >> items[i].width >> items[i].value;
    }

    inputFile.close();

    int result = knapsack(items, n, spaceLength, spaceWidth);

    printf("%d\n", result);

    return 0;
}
