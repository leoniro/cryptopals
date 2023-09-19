#include <iostream>
#include <fstream>
#include <unordered_map>

int main() {
    std::ifstream inFile;
    inFile.open("8.txt");
    std::string line, bestLine;
    int bestCount = 0;
    while ( std::getline(inFile, line) ) {
        std::unordered_map<std::string, int> chunkFrequency = {};
        for (int i=0; line[i]; i += 4) {
            std::string key = std::string(1,line[i]) + line[i+1] + line[i+2] + line[i+3];
            chunkFrequency[key];
            chunkFrequency[key]++;
        }
        int sumOfTopRepetitions = 0;
        for (int i=0; i<3; i++) {
            std::string maxKey;
            int maxRepetitions = 0;
            std::unordered_map<std::string, int>::iterator it;
            for (it = chunkFrequency.begin(); it != chunkFrequency.end(); ++it) {
                std::string k = it -> first;
                int v = it -> second;
                if (v > maxRepetitions) {
                    maxRepetitions = v;
                    maxKey = k;
                }
            }
            sumOfTopRepetitions += maxRepetitions;
            chunkFrequency[maxKey] = 0;
        }
        if (sumOfTopRepetitions > bestCount) {
            bestCount = sumOfTopRepetitions;
            bestLine = line;
        }
    }
    std::cout << "Desafio 8: A linha encriptada com ECB provavelmente é:" << "\n";
    std::cout << bestLine << "\n\n";
}