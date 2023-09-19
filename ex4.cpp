#include "auxFuncs.h"

int main() {
    std::string line;
    float bestScore = -100;
    BitArray bestKey;
    BitArray bestLine;
    std::ifstream inputFile;
    inputFile.open("4.txt");
    while ( std::getline(inputFile, line) ) {
        BitArray cypherText = BitArray(line,"base16");
        BitArray key = cypherText.breakSingleCharXor();
        BitArray plainText = cypherText ^ key;
        float score = plainText.englishScore();
        if (score > bestScore) {
            bestScore = score;
            bestKey = key; 
            bestLine = cypherText;
        }
    }
    inputFile.close();

    std::cout << "Desafio 4: Encontrar e quebrar xor de 1 char:\n";
    std::cout << "Texto cifrado: " << bestLine.toBase16() << "\n";
    std::cout << "Chave: " << bestKey.toPlainText() << "\n";
    std::cout << "Pontuação: " << bestScore << "\n";
    std::cout << "Texto decifrado: " << (bestLine ^ bestKey).toPlainText() << "\n\n";
}