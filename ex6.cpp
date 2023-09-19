#include "auxFuncs.h"

int main() {
    std::ifstream file;
    file.open("6.txt");
    std::string line;
    std::vector<bool> v = {};
    while ( std::getline(file, line) ) {
        BitArray vLine = BitArray(line,"base64");
        v.insert(v.end(), vLine.bits.begin(), vLine.bits.end());
    }
    file.close();
    BitArray cypherText = BitArray(v);
    int keySize = cypherText.probableKeySize();
    BitArray key = cypherText.breakRepeatingKeyXor(keySize);
    std::cout << "Desafio 6: Quebrar xor com chave repetida:" << "\n";
    std::cout << "Texto:" << "\n";
    std::cout << (cypherText ^ key).toPlainText() << "\n\n";
    std::cout << "Chave: " << key.toPlainText() << "\n\n";
}