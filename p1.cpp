#include <iostream>
#include <cstring>

using namespace std;

struct Item {
    int length;
    int width;
    int value;
};

int knapsack(Item items[], int n, int spaceLength, int spaceWidth) {
    
    int dp[spaceLength+1][spaceWidth+1];
    memset(dp, 0, sizeof(dp));

   
    for (int w = 0; w <= spaceWidth; ++w) {

        for (int l = 0; l <= spaceLength; ++l) {

            for (int i = 0; i < 2; i++) {
                
                if (items[i].length <= l && items[i].width <= w) {

                   dp[l][w] = max(dp[l][w], items[i].value + dp[l][w - items[i].width]);
                   dp[l][w] = max(dp[l][w], items[i].value + dp[l-items[i].length][w]);
                   //dp[i][l][w] = max(dp[i][l][w], items[i - 1].value + dp[i][l - items[i - 1].length][w]);
                   //dp[w] = max(dp[w], values[i] + dp[w - weights[i]]);
                }
            }
        }
    }
    
    return dp[spaceLength][spaceWidth];
}

int main() {
   
    Item items[] = {{1, 3, 2}, {2, 2, 1}};
    int n = 2;
    int spaceLength = 2;
    int spaceWidth = 6;

    
    int result = knapsack(items, n, spaceLength, spaceWidth);

    cout << result << endl;

    return 0;
}


