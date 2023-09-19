#include "auxFuncs.h"

int main() {
    float score;
    char key;
    std::string text;
    BitArray cypherText = BitArray("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736","base16");
    std::tie(score, text, key) = cypherText.breakSingleCharXor();
    std::cout << "Quebrar xor de 1 char:\n";
    std::cout << "Pontuação: " << score << "\n";
    std::cout << "Chave: " << key << "\n";
    std::cout << "Texto: " << text << "\n\n";
}