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

    //inicializa se a 0 porque a primeira vez que se obtem o resultado da peca e preciso buscar o 0
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < n; i++) {
        for (int l = 1; l <= spaceLength; l++) {
            for (int w = 1; w <= spaceWidth; w++) {
            
                if (l >= items[i].length && items[i].width <= w) {
                    
                    //algoritmo 101 do knapsack para ver se da para por a peca ou nao
                    dp[l][w] = max({dp[l][w], items[i].value + dp[l][w - items[i].width], items[i].value + dp[l - items[i].length][w]});

                    //o corte e feito pensando na juncao de 2 pecas ja feitas com a peca atual
                    //ve se o corte vertical e melhor que o valor que ja la esta
                    dp[l][w] = max({dp[l-items[i].length][w] + dp[items[i].length][w], dp[l][w]});
                    //ve se o corte horizontal e melhor que o valor que ja la esta
                    dp[l][w] = max({dp[l][w - items[i].width] + dp[items[i].width][1], dp[l][w]});

                }   //analogo ao de cima so se roda a peca
                if (w >= items[i].length && items[i].width <= l) {

                    dp[l][w] = max({dp[l][w], items[i].value + dp[l - items[i].width][w], items[i].value + dp[l][w - items[i].length]});
                    dp[l][w] = max({dp[l - items[i].width][w] + dp[items[i].width][w], dp[l][w]});
                    dp[l][w] = max({dp[l][w - items[i].length] + dp[l][items[i].length], dp[l][w]});

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
