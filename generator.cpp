#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Item {
    int length;
    int width;
    int value;
};

void generateLargeInput(const char* filename, int numItems, int maxDimensions, int maxValue) {
    srand(time(nullptr));

    ofstream outputFile(filename);
    int spaceLength = rand() % maxDimensions + 1;
    int spaceWidth = rand() % maxDimensions + 1;

    outputFile << spaceLength << " " << spaceWidth << "\n" << numItems << endl;

    for (int i = 0; i < numItems; ++i) {
        int length = rand() % maxDimensions + 1;
        int width = rand() % maxDimensions + 1;
        int value = rand() % maxValue + 1;

        outputFile << length << " " << width << " " << value << endl;
    }

    outputFile.close();
}

int main() {
    const char* filename = "large_input.txt";
    int numItems = 1000; 
    int maxDimensions = 100; 
    int maxValue = 50; 

    generateLargeInput(filename, numItems, maxDimensions, maxValue);

    return 0;
}