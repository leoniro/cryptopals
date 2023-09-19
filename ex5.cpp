#include "auxFuncs.h"

int main() {
    BitArray plainText = BitArray("Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal", "ascii");
    BitArray key = BitArray("ICE", "ascii");
    std::string cypherText = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
    
    std::cout << "Desafio 5: Encriptar com xor de chave repetida\n";
    std::cout << "Esperado: " << cypherText << "\n";
    std::cout << "  Obtido: " << (plainText ^ key).toBase16() << "\n\n";
}