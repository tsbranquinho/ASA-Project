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
    int dp[spaceLength + 1][spaceWidth + 1];
    memset(dp, 0, sizeof(dp));


    for (int l = 1; l <= spaceLength; l++) {
        for (int w = 1; w <= spaceWidth; w++) {
            for (int i = 0; i < n; i++) {
                if (l >= items[i].length && items[i].width <= w) {
                    dp[l][w] = max({dp[l][w], items[i].value + dp[l][w - items[i].width], items[i].value + dp[l - items[i].length][w]});

                    if (l % items[i].length == 0 && w % items[i].width == 0) {
                        dp[l][w] = max(dp[l][w], items[i].value * ((l * w) / (items[i].length * items[i].width)));
                    }

                    dp[l][w] = max({dp[l][w], dp[l][w-1] + dp[l][1], dp[l-1][w] + dp[1][w]});

                }
                if (w >= items[i].length && items[i].width <= l) {

                    dp[l][w] = max({dp[l][w], items[i].value + dp[l - items[i].width][w], items[i].value + dp[l][w - items[i].length]});

                    if (w % items[i].length == 0 && l % items[i].width == 0) {
                        dp[l][w] = max(dp[l][w], items[i].value * ((l * w) / (items[i].length * items[i].width)));
                    }

                    dp[l][w] = max({dp[l][w], dp[l][w-1] + dp[l][1], dp[l-1][w] + dp[1][w]});
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
