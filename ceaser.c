// author : Siddharth Mani Tiwari : 201851126
#include <stdio.h>
#include <stdlib.h>

void encrypt(int offset, char msg[], char enc_msg[])
{
    int curr = 0;
    while (msg[curr] != '\0')
    {
        if (msg[curr] >= 'a' && msg[curr] <= 'z')
        {
            enc_msg[curr] = 'a' + (((msg[curr] - 'a') + offset) % 26);
        }
        else
        {
            enc_msg[curr] = msg[curr];
        }
        curr++;
    }
}

void decrypt(int offset, char enc_msg[], char dec_msg[])
{
    int curr = 0;
    while (enc_msg[curr] != '\0')
    {
        if (enc_msg[curr] >= 'a' && enc_msg[curr] <= 'z')
        {
            dec_msg[curr] = 'a' + (((enc_msg[curr] - 'a') - offset + 26) % 26);
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
    int offset;
    char msg[200], enc_msg[200], dec_msg[200];for (int i = 0; i < 200; i++){msg[i]='\0';enc_msg[i]='\0';dec_msg[i]='\0';}
    printf("offset: ");
    scanf("%d", &offset);
    getchar();
    printf("input text: ");
    scanf("%[^\n]%*c", msg);
    encrypt(offset, msg, enc_msg);
    decrypt(offset, enc_msg, dec_msg);
    for(char i='a';i<='z';i++){printf("%c:%d\n",i,(i-'a'));}
    printf("Encrypted Text: %s\n", enc_msg);
    printf("Decrypted Text: %s\n", dec_msg);
    return 0;
}