#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    /* Create digest context */
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) {
        printf("Failed to create context\n");
        fclose(file);
        return 1;
    }

    /* Initialize SHA-256 digest */
    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1) {
        printf("Digest initialization failed\n");
        EVP_MD_CTX_free(ctx);
        fclose(file);
        return 1;
    }

    unsigned char buffer[4096];
    size_t bytes;

    /* Read file in chunks and update hash */
    while ((bytes = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        if (EVP_DigestUpdate(ctx, buffer, bytes) != 1) {
            printf("Digest update failed\n");
            EVP_MD_CTX_free(ctx);
            fclose(file);
            return 1;
        }
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    /* Finalize hash calculation */
    if (EVP_DigestFinal_ex(ctx, hash, &hash_len) != 1) {
        printf("Digest finalization failed\n");
        EVP_MD_CTX_free(ctx);
        fclose(file);
        return 1;
    }

    /* Print hash in hexadecimal format */
    printf("SHA256: ");
    for (unsigned int i = 0; i < hash_len; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    EVP_MD_CTX_free(ctx);
    fclose(file);

    return 0;
}