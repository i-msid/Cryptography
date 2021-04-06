/*
    @Siddharth Mani Tiwari 201851126
*/
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check(unsigned long long int x);
int SBox[4][16][8];
int perm[8][4];
unsigned long long int expansion(unsigned long long int R0)
{
    unsigned long long int R0_34bit = 0;
    R0_34bit = ((R0 & 1) << 32) | R0;              // adding first bit of R0 to the last
    R0_34bit = (R0_34bit << 1) | ((R0 >> 31) & 1); // adding last bit of R0 to the first
    unsigned long long E_48bit = 0;
    for (int i = 0; i < 8; i++)
    {
        E_48bit <<= 6;
        E_48bit |= (R0_34bit & (63ULL << 28ULL)) >> 28ULL;
        R0_34bit <<= 4;
    }
    return E_48bit;
}

bool Reader()
{
    FILE *fptr = fopen("sbox.txt", "r");
    if (fptr == NULL)
    {
        return false;
    }
    for (int z = 0; z < 8; z++)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                fscanf(fptr, "%d", &SBox[i][j][z]);
            }
        }
    }
    fclose(fptr);
    return true;
}

void check(unsigned long long int x)
{
    int count = 0;
    while (x != 0)
    {
        printf("%d", x % 2);
        x = x >> 1;
        count++;
    }
    printf("\t length = %d\n", count);
}
unsigned long int SBOX(unsigned long long R0)
{
    unsigned long R_sbox = 0;
    Reader();
    for (int x = 0; x < 8; x++)
    {
        R_sbox <<= 4;
        int R_6bit = (int)((R0 & (63ULL << 42)) >> 42);
        int msb = (R_6bit & (1 << 5)) >> 5;
        int lsb = R_6bit % 2;
        int row = 2 * msb + lsb;
        int col = (R_6bit ^ (msb << 5 | lsb)) >> 1;
        int temp = ((int)15 & (SBox[row][col][x]));
        R_sbox |= temp;
        R0 <<= 6;
    }
    return R_sbox;
}

unsigned long int Permutation(unsigned long int n)
{
    FILE *fptr = fopen("perm.txt", "r");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            fscanf(fptr, "%d", &perm[i][j]);
            perm[i][j] += (-1);
        }
    }
    fclose(fptr);
    unsigned long int retme = 0;
    for (int i = 0; i < 32; i++)
    {
        retme <<= 1;
        int row = i / 4;
        int col = i % 4;
        int bit = perm[row][col];
        retme |= ((n & (1UL << (31 - bit))) >> (31 - bit));
    }
    return retme;
}

unsigned long int F(unsigned long int R0, unsigned long long int key)
{
    /* 
        F(R0,k) has three steps:
        step 1: Expansion(R0) xor key
        step 2: Sbox(step1)
        step 3: Permutation(step2)
    */

    unsigned long long int R_48bit = expansion(R0);
    printf("%c\t\t\tExpansion of R0 = %llu\n",178,R_48bit);
    R_48bit ^= key;
    printf("%c\t\t\tExpansion Xor with Key  = %llu\n",178,R_48bit);
    unsigned long int sb_32bit = SBOX(R_48bit);
    printf("%c\t\t\tSbox = %lu\n",178,sb_32bit);
    printf("%c\t\t\tPermutation using matrix P = %lu\n",178,Permutation(sb_32bit));
    return Permutation(sb_32bit);
}
int main()
{
    for (int i = 0; i < 81; i++)
    {
        printf("%c",178);
    }
    printf("\n%c\t\t\tWELCOME TO DES - 1 ROUND IMPLIMENTATION\t\t\t%c\n",178,178);
    unsigned long long int input, plaintext, key, enc_msg = 0, dec_msg;
    printf("%c\t\t\tPlainText: ",178);
    scanf("%llu", &input);
    printf("%c \t\t\tkey: ",178);
    scanf("%llu", &key);
    plaintext = input;
    unsigned long int L0 = 0, R0 = 0, L1 = 0, R1 = 0;
    // dividing input plain text into two parts of
    // 32 bits each!
    R0 = R0 | plaintext;
    L0 = L0 | (plaintext >> 32);
    printf("%c\t\t\tL0 = %lu, R0 = %lu\n",178,L0,R0);
    // L1 = R0
    L1 = R0;

    /*
    R1 = L0 xor F(R0,K)
*/

    R1 = L0 ^ F(R0, key);

    enc_msg |= L1;
    enc_msg <<= 32;
    enc_msg |= R0;
    printf("%c \t\t\tEncrypted message = %llu\n",178, enc_msg);
    for (int i = 0; i < 81; i++)
    {
        printf("%c",178);
    }
    return 0;
}