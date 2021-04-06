// author : Siddharth Mani Tiwari : 201851126

// code was written assuming j and i to be same
// if there is repetition, 'x' has been replaced

#include <stdio.h>
#include <string.h>


struct pair
{
    int first;
    int second;
};

void matrixgen(char mat[5][5], char key[])
{
    int visited[30];
    memset(visited, 0, 30 * sizeof(int));
    visited['j' - 'a'] = 1;
    int _size = 0, trace = 0;
    // char tempkey[200];
    while (key[_size] != '\0')
    {
        if (visited[key[_size] - 'a'] == 0)
        {
            int row = trace / 5;
            int col = trace % 5;
            mat[row][col] = key[_size];
            visited[key[_size] - 'a'] = 1;
            trace++;
        }
        _size++;
    }
}

void encrypt(char msg[], char mat[5][5], struct pair lookup[30], char enc_msg[])
{
    int curr = 0;
    while (msg[curr] != '\0')
    {
        if (msg[curr + 1] == '\0')
        {
            msg[curr + 1] = 'x';
        }
        if (msg[curr] == msg[curr + 1])
        {
            msg[curr + 1] = 'x';
        }
        struct pair C1 = lookup[msg[curr] - 'a'];
        struct pair C2 = lookup[msg[curr + 1] - 'a'];
        if (C1.first == C2.first)
        {
            enc_msg[curr] = mat[C1.first][(C1.second + 1) % 5];
            enc_msg[curr + 1] = mat[C2.first][(C2.second + 1) % 5];
        }
        else if (C1.second == C2.second)
        {
            enc_msg[curr] = mat[(C1.first + 1) % 5][C1.second];
            enc_msg[curr + 1] = mat[(C2.first + 1) % 5][C2.second];
        }
        else
        {
            enc_msg[curr] = mat[C1.first][C2.second];
            enc_msg[curr + 1] = mat[C2.first][C1.second];
        }
        curr += 2;
    }
    return;
}

void decrypt(char enc_msg[], char mat[5][5], struct pair lookup[30], char dec_msg[])
{
    int curr = 0;
    while (enc_msg[curr] != '\0')
    {
        struct pair C1 = lookup[enc_msg[curr] - 'a'];
        struct pair C2 = lookup[enc_msg[curr + 1] - 'a'];
        if (C1.first == C2.first)
        {
            dec_msg[curr] = mat[C1.first][(C1.second + 4) % 5];
            dec_msg[curr + 1] = mat[C2.first][(C2.second + 4) % 5];
        }
        else if (C1.second == C2.second)
        {
            dec_msg[curr] = mat[(C1.first + 4) % 5][C1.second];
            dec_msg[curr + 1] = mat[(C2.first + 4) % 5][C2.second];
        }
        else
        {
            dec_msg[curr] = mat[C1.first][C2.second];
            dec_msg[curr + 1] = mat[C2.first][C1.second];
        }
        curr += 2;
    }
    return;
}

int main()
{
    char key[200], msg[200], enc_msg[200], dec_msg[200];
    for (int i = 0; i < 200; i++)
    {
        key[i] = '\0';
        msg[i] = '\0';
        enc_msg[i] = '\0';
        dec_msg[i] = '\0';
    }
    printf("Key: ");
    scanf("%[^\n]%*c", key);
    strcat(key, "abcdefghijklmnopqrstuvwxyz");
    char mat[5][5];
    matrixgen(mat, key);
    for(int i=0;i<=5;i++){
        for(int j=0;j<5;j++){
            printf("%c ",mat[i][j]);
        }
        printf("\n");
    }
    struct pair lookup[30];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            lookup[mat[i][j] - 'a'].first = i;
            lookup[mat[i][j] - 'a'].second = j;
        }
    }
    lookup['j' - 'a'] = lookup['i' - 'a'];
    // take input'
    printf("Input text: ");
    scanf("%[^\n]%*c", msg);

    encrypt(msg, mat, lookup, enc_msg);
    printf("Encrypted Text: %s\n", enc_msg);
    decrypt(enc_msg, mat, lookup, dec_msg);
    printf("Decrypted Text: %s\n", dec_msg);
    return 0;
}
