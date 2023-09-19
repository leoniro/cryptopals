#include "auxFuncs.h"

int main() {
    std::string s1 = "1c0111001f010100061a024b53535009181c";
    std::string s2 = "686974207468652062756c6c277320657965";
    std::string s3 = "746865206b696420646f6e277420706c6179";
    BitArray v1 = BitArray(s1, "base16");
    BitArray v2 = BitArray(s2, "base16");
    BitArray v3 = v1 ^ v2;
    
    std::cout << "Desafio 2: xor entre dois hexadecimais:" << "\n";
    std::cout << "Esperado: " << s3 << "\n";
    std::cout << "  Obtido: " << v3.toBase16() << "\n\n";

    std::cout << "Recuperando s1 com (v3 ^ v2):" << "\n";
    std::cout << "Esperado: " << s1 << "\n";
    std::cout << "  Obtido: " << (v3 ^ v2).toBase16() << "\n\n";

    std::cout << "Recuperando s2 com (v3 ^ v1):" << "\n";
    std::cout << "Esperado: " << s2 << "\n";
    std::cout << "  Obtido: " << (v3 ^ v1).toBase16() << "\n\n";
}