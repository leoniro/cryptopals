#include "auxFuncs.h"

int main() {
    int errors = 0;
    std::string x64 = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    std::string x16 = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    BitArray v16 = BitArray(x16,"base16");
    BitArray v64 = BitArray(x64,"base64");

    std::cout << "Desafio 1: Convertendo base16 para base64:" << "\n";
    std::cout << "Esperado: " << x64 << "\n";
    std::cout << "  Obtido: " << v16.toBase64() << "\n\n";
    std::cout << "Convertendo base64 para base16:" << "\n";
    std::cout << "Esperado: " << x16 << "\n";
    std::cout << "  Obtido: " << v64.toBase16() << "\n\n";
}