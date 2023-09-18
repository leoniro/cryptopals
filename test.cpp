#include "auxFuncs.h"

int test() {
    // challenge 1: conversion:
    int errors = 0;
    std::string x1_64 = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    std::string x1_16 = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    BitArray v1_16 = BitArray(x1_16,"base16");
    BitArray v1_64 = BitArray(x1_64,"base64");
    if ( x1_16.compare(v1_16.toBase16()) != 0 ) { errors++; }
    if ( x1_16.compare(v1_64.toBase16()) != 0 ) { errors++; }
    if ( x1_64.compare(v1_16.toBase64()) != 0 ) { errors++; }
    if ( x1_64.compare(v1_64.toBase64()) != 0 ) { errors++; }
    std::cout << "Conversão de base64 para base16:\n";
    if (errors == 0) { std::cout << "OK\n\n"; } else { std::cout << "Fail\n\n"; }


    // challenge 2: xor between BitArrays:
    errors = 0;
    std::string s21 = "1c0111001f010100061a024b53535009181c";
    std::string s22 = "686974207468652062756c6c277320657965";
    std::string s23 = "746865206b696420646f6e277420706c6179";
    BitArray v21 = BitArray(s21, "base16");
    BitArray v22 = BitArray(s22, "base16");
    BitArray v23 = v21 ^ v22;
    if ( s23.compare( v23.toBase16() ) != 0 ) { errors++; }
    if ( s22.compare( (v23 ^ v21).toBase16()) != 0) {errors++; }
    if ( s21.compare( (v23 ^ v22).toBase16()) != 0) {errors++; }
    std::cout << "Operação xor:\n";
    if (errors == 0) { std::cout << "OK\n\n"; } else { std::cout << "Fail\n\n"; }

    // challenge 3:
    float score;
    char key;
    std::string text;
    BitArray cypher3 = BitArray("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736","base16");
    std::tie(score, text, key) = cypher3.breakSingleCharXor();
    std::cout << "Quebrar xor de 1 char:\n";
    std::cout << "Pontuação: " << score << "\n";
    std::cout << "Chave: " << key << "\n";
    std::cout << "Texto: " << text << "\n\n";

    // challenge 4:
    std::string line, bestString;
    float bestScore = -100;
    char bestKey;
    std::ifstream inputFile;
    inputFile.open("4.txt");
    int temp = 1;
    while ( std::getline(inputFile, line) ) {
        BitArray v = BitArray(line,"base16");
        std::tie(score, text, key) = v.breakSingleCharXor();
        if (score > bestScore) { bestScore = score; bestString = text; bestKey = key; }
    }
    inputFile.close();
    std::cout << "Encontrar e quebrar xor de 1 char:\n";
    std::cout << "Pontuação: " << bestScore << "\n";
    std::cout << "Chave: " << key << "\n";
    std::cout << "Texto: " << bestString << "\n\n";

    // challenge 5:
    errors = 0;
    std::string plain5 = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    std::string key5 = "ICE";
    std::string cypher5 = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
    BitArray v5 = BitArray(plain5,"ascii");
    BitArray k5 = BitArray(key5, "ascii");
    if ( cypher5.compare( (v5 ^ k5).toBase16() ) ) { errors++; };
    std::cout << "Encriptar com xor de chave repetida\n";
    if (errors == 0) { std::cout << "OK\n\n"; } else { std::cout << "Fail\n\n"; }
    
    // challenge 6:
    errors = 0;
    BitArray v6a = BitArray("this is a test","ascii");
    BitArray v6b = BitArray("wokka wokka!!!","ascii");
    if (hammingDistance(v6a, v6b) != 37) { errors++; }
    std::cout << "Distancia Hamming:\n";
    if (errors == 0) { std::cout << "OK\n\n"; } else { std::cout << "Fail\n\n"; }


    return 0;
}

int main() {
    test();
}
