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
    BitArray cypher = BitArray(v);
    int keySize = cypher.probableKeySize();
    std::cout << cypher.toBase64() << "\n";
}