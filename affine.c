// author : Siddharth Mani Tiwari : 201851126
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// this function uses extended euclidean algo to calculate inverse of a number
int gcd(int a, int b, int *x, int *y)
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - y1 * (a / b);
    return d;
}

void encrypt(int a, int b, char msg[], char enc_msg[])
{
    int curr = 0;
    while (msg[curr] != '\0')
    {
        if (msg[curr] >= 'a' && msg[curr] <= 'z')
        {
            int x = msg[curr] - 'a';
            int fox = (a * x + b) % 26;
            enc_msg[curr] = 'a' + fox;
        }
        else
        {
            enc_msg[curr] = msg[curr];
        }
        curr++;
    }
    return;
}

void decrypt(int a, int b, char enc_msg[], char dec_msg[])
{
    int dummy, Inv;
    int curr = 0;
    while (enc_msg[curr] != '\0')
    {
        if (enc_msg[curr] >= 'a' && enc_msg[curr] <= 'z')
        {
            int g = gcd(26, a, &dummy, &Inv);
            int fox = enc_msg[curr] - 'a';
            int x = ((fox - b) * (Inv) + 26 * 26) % 26;
            dec_msg[curr] = 'a' + x;
        }
        else
        {
            dec_msg[curr] = enc_msg[curr];
        }
        curr++;
    }
}

int main()
{
    char msg[200], enc_msg[200], dec_msg[200];for (int i = 0; i < 200; i++){msg[i]='\0';enc_msg[i]='\0';dec_msg[i]='\0';}
    int a, b, Dummy1, Dummy2;
    printf("Input a and b : ");
    scanf("%d %d", &a, &b);
    getchar();
    printf("input text: ");
    scanf("%[^\n]%*c", msg);
    
    if (gcd(26, a, &Dummy1, &Dummy2) != 1 || a > 25 || b > 25)
    {
        printf("Inverse does not exist, Try Again!\n");
        return 0;
    }
    encrypt(a, b, msg, enc_msg);
    printf("Encrypted Text: %s\n", enc_msg);
    decrypt(a, b, enc_msg, dec_msg);
    printf("Decrypted Text: %s\n", dec_msg);
    return 0;
}