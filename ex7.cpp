#include "auxFuncs.h"
#include <openssl/evp.h>

int do_crypt(FILE *in, FILE *out, int do_encrypt)
{   
    // This code is adapted from the OpenSSL manual:
    // https://www.openssl.org/docs/man3.1/man3/EVP_CipherInit_ex2.html
    /* Allow enough space in output buffer for additional block */
    unsigned char inbuf[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
    int inlen, outlen;
    EVP_CIPHER_CTX *ctx;
    /*
     * Bogus key and IV: we'd normally set these from
     * another source.
     */
    unsigned char key[] = "YELLOW SUBMARINE";
    //unsigned char iv[] = "1234567887654321";


    /* Don't set key or IV right away; we want to check lengths */
    ctx = EVP_CIPHER_CTX_new();
    if (!EVP_CipherInit_ex2(ctx, EVP_aes_128_ecb(), NULL, NULL,
                            do_encrypt, NULL)) {
        /* Error */
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }
    OPENSSL_assert(EVP_CIPHER_CTX_get_key_length(ctx) == 16);

    /* Now we can set key and IV */
    if (!EVP_CipherInit_ex2(ctx, NULL, key, NULL, do_encrypt, NULL)) {
        /* Error */
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }

    for (;;) {
        inlen = fread(inbuf, 1, 1024, in);
        if (inlen <= 0)
            break;
        if (!EVP_CipherUpdate(ctx, outbuf, &outlen, inbuf, inlen)) {
            /* Error */
            EVP_CIPHER_CTX_free(ctx);
            return 0;
        }
        fwrite(outbuf, 1, outlen, out);
    }
    if (!EVP_CipherFinal_ex(ctx, outbuf, &outlen)) {
        /* Error */
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }
    fwrite(outbuf, 1, outlen, out);

    EVP_CIPHER_CTX_free(ctx);
    return 1;
}

int main() {
    // convert base64 to ascii:
    std::ifstream f1;
    std::ofstream f2;
    f1.open("7.txt");
    f2.open("7p.txt");
    std::string line;
    while (std::getline(f1,line)) {
        f2 << BitArray(line,"base64").toPlainText();
    }
    f1.close();
    f2.close();

    FILE * inFile;
    FILE * outFile;
    inFile = fopen("7p.txt", "r");
    outFile = fopen("7d.txt", "w");
    do_crypt(inFile, outFile, 1);
    fclose(inFile);
    fclose(outFile);
}