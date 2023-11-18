#include <iostream>
#include <cstring>

using namespace std;

struct Item {
    int length;
    int width;
    int value;
};

int knapsack(Item items[], int n, int spaceLength, int spaceWidth) {
    
    int dp[n + 1][spaceLength + 1][spaceWidth + 1];
    memset(dp, 0, sizeof(dp));

   
    for (int i = 1; i <= n; ++i) {

        for (int l = 0; l <= spaceLength; ++l) {

            for (int w = 0; w <= spaceWidth; ++w) {
                
                if (items[i - 1].length <= l && items[i - 1].width <= w) {

                    dp[i][l][w] = max(dp[i - 1][l][w], items[i - 1].value + dp[i][l - items[i - 1].length][w - items[i - 1].width]);
                } else {
                    
                    dp[i][l][w] = dp[i - 1][l][w];
                }
            }
        }
    }

    return dp[n][spaceLength][spaceWidth];
}

int main() {
   
    Item items[] = {{1, 3, 1}, {2, 2, 2}};
    int n = sizeof(items) / sizeof(items[0]);
    int spaceLength = 4;
    int spaceWidth = 4;

    
    int result = knapsack(items, n, spaceLength, spaceWidth);

    cout << result << endl;

    return 0;
}


