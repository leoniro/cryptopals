#include "auxFuncs.h"

int main() {
    BitArray cypherText = BitArray("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736","base16");
    BitArray key = cypherText.breakSingleCharXor();
    BitArray plainText = cypherText ^ key;
    std::cout << "Quebrar xor de 1 char:\n";
    std::cout << "Pontuação: " << plainText.englishScore() << "\n";
    std::cout << "Chave: " << key.toPlainText() << "\n";
    std::cout << "Texto: " << plainText.toPlainText() << "\n\n";
}